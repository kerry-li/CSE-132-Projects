#include <Arduino.h>
#include <Wire.h>
#include <ST7036.h>

int count = 0;
int buttonState;
int lastButtonState = 0;
const int buttonPin = 12;
long lastDebounceTime = 0;
long debounceDelay = 50;
ST7036 lcd = ST7036 ( 2, 16, 0x7c );

void setup ()
{
  Serial.begin(9600);
  lcd.init ();
  lcd.setContrast(0);
  pinMode(buttonPin,INPUT_PULLUP);
}

void loop() {
  lcd.clear();
  int reading = (digitalRead(buttonPin)+1)%2;
  if (reading != lastButtonState) {
     // reset the debouncing timer
    lastDebounceTime = millis();
  }
   
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
    }
    if (buttonState == 1) {
      count++;
    }
  }
  lcd.print(count);
  delay(100);
}
