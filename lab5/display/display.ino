/*
 * display
 */

#include <Arduino.h>
#include <Wire.h>
#include <ST7036.h>
#include "font.h"

ST7036 lcd = ST7036 ( 2, 16, 0x7c );
const int SW1 = 12;
const int SW2 = 13;
const int SW3 = 16;
const int SW4 = 15;
const int debounceDelay = 10;

//control rows and columns with digital pins

void setup ()
{
  lcd.init ();
  lcd.setContrast(0);
  
  //sets all pins to output mode
  //rows
  pinMode(0,OUTPUT);
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  //columns
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  //buttons
  pinMode(SW1,INPUT_PULLUP);
  pinMode(SW2,INPUT_PULLUP);
  pinMode(SW3,INPUT_PULLUP);
  pinMode(SW4,INPUT_PULLUP);
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
unsigned char asciiChar = ' '; //default start char

void loop ()
{
  displayChar(asciiChar);
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
        asciiChar--;
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
        asciiChar+=10;
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
        asciiChar-=10;
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
        asciiChar++;
      }
    }
  }

  //attempting to go beyond the bounds of the array just goes back to the last char
  if(asciiChar < 0x20)
  {
    asciiChar = 0x20;
  }
  else if(asciiChar > 0x7f)
  {
    asciiChar = 0x7f;
  }
  lcd.clear ();

  lastSW1 = readSW1;
  lastSW2 = readSW2;
  lastSW3 = readSW3;
  lastSW4 = readSW4;
}

void displayChar(char letter)
{
  for(int c = 1; c <= 5; c++)
  {
    digitalWrite(c + 6, HIGH);
    for(int i = 1; i <= 7; i++)
    {
      if((font_5x7[letter - 0x20][c - 1] >> i) & 0x01)
      {
        digitalWrite(7 - i, LOW);
      }
    }
    resetCol();
    resetRow();
    //delay(3);
  }
  
}

//other functions
//sets column pins to low voltage
void resetCol()
{
  for(int i = 7; i <= 11; i++)
  {
    digitalWrite(i,LOW);
  }
}

//sets row pins to high voltage
void resetRow()
{
  for(int i = 0; i <= 6; i++)
  {
    digitalWrite(i,HIGH);
  }
}

