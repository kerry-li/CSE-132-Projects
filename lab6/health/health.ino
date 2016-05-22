/* health
 *
 * Arudino side of a health monitor
 *
 */
#include <Arduino.h>
#include <Wire.h>
#include <ST7036.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

Adafruit_MMA8451 mma = Adafruit_MMA8451();
ST7036 lcd = ST7036 ( 2, 16, 0x7c );
unsigned long steps;
const int filterSize = 20;
float temp;
byte tempSig;
byte tempDec;
const int analogInPin = A0;
const int SW1 = 12;
const int SW2 = 13;
const int SW3 = 16;
const int SW4 = 15;
const int debounceDelay = 10;

void setup() {
  Serial.begin(115200);
  analogReference(INTERNAL);
  mma.begin();
  mma.setRange(MMA8451_RANGE_8_G);
  Serial.println("Hold the arduino still");
  pinMode(SW1,INPUT_PULLUP);
  pinMode(SW2,INPUT_PULLUP);
  pinMode(SW3,INPUT_PULLUP);
  pinMode(SW4,INPUT_PULLUP);
  //ensuring correct orientation
  while(true)
  {
    mma.read();
    sensors_event_t event;
    mma.getEvent(&event);
    if(abs(event.acceleration.z - 1.0) > 0.05)
    {
      Serial.println("Hold the arduino so that the screen is facing upwards");
    }
    else
    {
      break;
    }
  }
}

int lastSW1 = 1;
int lastSW2 = 1;
int lastSW3 = 1;
int lastSW4 = 1;
int SW1state = 1;
int SW2state = 1;
int SW3state = 1;
int SW4state = 1;
int lastDebounceTime1;
int lastDebounceTime2;
int lastDebounceTime3;
int lastDebounceTime4;

void loop() 
{
  double lastAccel = 0;
  double currentAccel = 0;
  double nextAccel = 0;
  double lastSum = 0;
  double currentSum = 0;
  double nextSum = 0;

  for(int i = 0; i < filterSize; i++)
  {
    mma.read();
    sensors_event_t event;
    mma.getEvent(&event);
    lastSum += event.acceleration.z;
  }

  lastAccel = lastSum/filterSize;

  for(int i = 0; i < filterSize; i++)
  {
    mma.read();
    sensors_event_t event;
    mma.getEvent(&event);
    currentSum += event.acceleration.z;
  }

  currentAccel = currentSum/filterSize;

  for(int i = 0; i < filterSize; i++)
  {
    mma.read();
    sensors_event_t event;
    mma.getEvent(&event);
    nextAccel += event.acceleration.z;
  }

  nextAccel = nextSum/filterSize;
  
  if((currentAccel - lastAccel > 0.2) && (currentAccel - nextAccel > 0.2))
  {
    steps++;
  }

  /*Serial.print("Steps: ");
  Serial.println(steps);*/
  
  Serial.write(0x40);
  Serial.write(steps >> 24);
  Serial.write(steps >> 16);
  Serial.write(steps >> 8);
  Serial.write(steps);

  //read the temp
  int totalCounts = 0;
  int avgCounts = 0;
  
  for(int i = 0; i < filterSize; i++) 
  {
    totalCounts += analogRead(analogInPin);
  }
  avgCounts = totalCounts/filterSize;
  temp = (float)avgCounts*100*1.1/1023 - 50;
  tempSig = (byte)temp;
  tempDec = (temp-tempSig)*(100);

  /*Serial.print("temp: ");
  Serial.println(temp);
  Serial.print("tempSig: " );
  Serial.println(tempSig);
  Serial.print("tempDec: ");
  Serial.println(tempDec);*/
  
  Serial.write(tempSig);
  Serial.write(tempDec);

  //pressing any of the switches will reset the steps 
  int readSW1 = digitalRead(SW1);
  int readSW2 = digitalRead(SW2);
  int readSW3 = digitalRead(SW3);
  int readSW4 = digitalRead(SW4);

  if(readSW1 != lastSW1)
  {
    lastDebounceTime1 = millis();
  }
  else if(readSW2 != lastSW2)
  {
    lastDebounceTime2 = millis();
  }
  else if(readSW3 != lastSW3)
  {
    lastDebounceTime3 = millis();
  }
  else if(readSW4 != lastSW4)
  {
    lastDebounceTime4 = millis();
  }

  if((millis() - lastDebounceTime1) > debounceDelay)
  {
    if(readSW1 != SW1state)
    {
      SW1state = readSW1;
      if(SW1state == 0)
      {
        steps = 0;
      }
    }
  }
  if((millis() - lastDebounceTime2) > debounceDelay)
  {
    if(readSW2 != SW2state)
    {
      SW2state = readSW2;
      if(SW2state == 0)
      {
        steps = 0;
      }
    }
  }
  if((millis() - lastDebounceTime3) > debounceDelay)
  {
    if(readSW3 != SW3state)
    {
      SW3state = readSW3;
      if(SW3state == 0)
      {
        steps = 0;
      }
    }
  }
  if((millis() - lastDebounceTime4) > debounceDelay)
  {
    if(readSW4 != SW4state)
    {
      SW4state = readSW4;
      if(SW4state == 0)
      {
        steps = 0;
      }
    }
  }

  lastSW1 = readSW1;
  lastSW2 = readSW2;
  lastSW3 = readSW3;
  lastSW4 = readSW4;

  Serial.write(millis() >> 24);
  Serial.write(millis() >> 16);
  Serial.write(millis() >> 8);
  Serial.write(millis());
  Serial.write(0x0d);

  delay(10);

}
