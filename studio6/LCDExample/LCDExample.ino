/***************************************************************************************************************/
// Created from example code from Arduino Playground ( http://playground.arduino.cc/Code/LCD )
//    LCD_ST7036_v1.2.0.zip ( https://bitbucket.org/fmalpartida/st7036-display-driver/wiki/Home )
// Extract .zip file to the arduinosketchfolder/libraries/ folder. You may need to create the libraries subfolder
// if its your first library. Restart the IDE. You can set the arduinosketchfolder under File -> Preferences
// Changed ST7036 object instantiation to (2,16,0x7c) for our display (2x16 with I2C address = 0x7c)
/***************************************************************************************************************/
#include <Arduino.h>
#include <Wire.h>
#include <ST7036.h>

ST7036 lcd = ST7036 ( 2, 16, 0x7c );
int i = 0;

void setup ()
{
  Serial.begin(9600);
  lcd.init ();
  lcd.setContrast(0);
  lcd.setCursor(0,0);
}

void loop ()
{
  if(Serial.available())
  {
    while(Serial.available())
    {
      lcd.write(Serial.read());
      delay(200);
    }
    i++;
    lcd.setCursor(i%2,0);
  }
}



