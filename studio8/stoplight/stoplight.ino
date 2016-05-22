/*
 * stoplight
 */

#include <Arduino.h>
#include <Wire.h>
#include <ST7036.h>

ST7036 lcd = ST7036 ( 2, 16, 0x7c );
const int yRed = 2;
const int yYel = 3;
const int yGre = 4;
const int xRed = 5;
const int xYel = 6;
const int xGre = 9;
int greenTime = 5000;
int yelTime = 2500;
void setup ()
{
  Serial.begin(9600);
  pinMode(yRed,OUTPUT);
  pinMode(yYel,OUTPUT);
  pinMode(yGre,OUTPUT);
  pinMode(xRed,OUTPUT);
  pinMode(xYel,OUTPUT);
  pinMode(xGre,OUTPUT);
  digitalWrite(yRed,HIGH);
  digitalWrite(yYel,LOW);
  digitalWrite(yGre,LOW);
  digitalWrite(xRed,HIGH);
  digitalWrite(xYel,LOW);
  digitalWrite(xGre,LOW);
  lcd.init ();
  lcd.setContrast(0);
}

void loop ()
{
  digitalWrite(yRed,LOW);
  digitalWrite(yGre,HIGH);
  if(millis() > greenTime)
  {
    greenTime += 5000;
    digitalWrite(yGre,LOW);
    digitalWrite(yYel,HIGH);
    if(millis() - greenTime > yelTime)
    {
      yelTime += 2500;
      digitalWrite(yYel,LOW);
      digitalWrite(yRed,HIGH);
    }
  }
  

}
