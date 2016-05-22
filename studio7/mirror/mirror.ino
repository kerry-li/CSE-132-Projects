/*
 * mirror
 */

#include <Arduino.h>
#include <Wire.h>
#include <ST7036.h>

int count = 0;
int last = 0;
const int pin = 12;
ST7036 lcd = ST7036 ( 2, 16, 0x7c );

void setup ()
{
  Serial.begin(9600);
  lcd.init();
  lcd.setContrast(0);
  pinMode(pin,INPUT_PULLUP);
}

void loop ()
{
  lcd.clear ();
  int inputVal = (digitalRead(pin)+1)%2;
  Serial.println(inputVal);
  if(last == 0 && inputVal == 1) 
  {
    count++;
  }
  last = inputVal;
  lcd.print(count);
  delay(50);
}
