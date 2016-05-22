/**************************************************************************
 * steps
 **************************************************************************/
#include <Arduino.h>
#include <Wire.h>
#include <ST7036.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

Adafruit_MMA8451 mma = Adafruit_MMA8451();
ST7036 lcd = ST7036 ( 2, 16, 0x7c );

void setup(void) {
  Serial.begin(115200);
  
  Serial.println("Adafruit MMA8451 test!");
  

  if (! mma.begin()) {
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("MMA8451 found!");
  
  // You might like this, you might want to change it
  mma.setRange(MMA8451_RANGE_8_G);
  
  Serial.print("Range = "); Serial.print(2 << mma.getRange());  
  Serial.println("G");

  // Feel free to use the LCD as you choose
  lcd.init ();
  lcd.setContrast(0);  
}

void loop() {
  // Put your code here

  
}
