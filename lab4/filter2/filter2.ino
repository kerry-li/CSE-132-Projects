/* filter
 *
 * FIR filter in assembly language
 *
 * the assembly language code goes in the file filter.S, in the libraries directory
 */

#include <filter.h>
#include "fir1.h"
#include "input1.h"

int output[NUM_SAMPS];
int numTimes;

extern "C" {              //function prototypes
 void printRegs(void);
 int q15mpy(int, int);
}


void setup() {
  Serial.begin(9600);
  for(int inputI = 0; inputI < NUM_SAMPS-NUM_TAPS - 1; inputI++) //NUM_SAMPS = input.length
  {
    for(int firI = 0; firI < NUM_TAPS; firI++) //NUM_TAPS = fir1.length
    {
      output[inputI] += q15mpy(input[inputI + firI], fir1[firI]);
    }
  }

  //Serial.print(output[13]);
  for(int i = 0; i < NUM_SAMPS-NUM_TAPS-1; i++)
  {
    //output array
    long mil = millis();
    Serial.write(0x40);
    Serial.write(0x05);
    Serial.write(mil >> 24);
    Serial.write(mil >> 16);
    Serial.write(mil >> 8);
    Serial.write(mil);
    Serial.write((output[i] >> 8) & 0xff);
    Serial.write(output[i] & 0xff);
    Serial.write(0x0d);

    //delay(150);
    //index
    Serial.write(0x40);
    Serial.write(0x07);
    Serial.write(mil >> 24);
    Serial.write(mil >> 16);
    Serial.write(mil >> 8);
    Serial.write(mil);
    Serial.write(i >> 8);
    Serial.write(i);
    Serial.write(0x0d);

    //input
    Serial.write(0x40);
    Serial.write(0x04);
    Serial.write(mil >> 24);
    Serial.write(mil >> 16);
    Serial.write(mil >> 8);
    Serial.write(mil);
    Serial.write(input[i] >> 8);
    Serial.write(input[i]);
    Serial.write(0x0d);
  }
  
  /*for(int i = 0; i < NUM_SAMPS-NUM_TAPS-1; i++)
  {
    //input array
    Serial.write(0x40);
    Serial.write(0x02);
    Serial.write(mil >> 24);
    Serial.write(mil >> 16);
    Serial.write(mil >> 8);
    Serial.write(mil);
    Serial.write(input[i] >> 8);
    Serial.write(input[i]);
    Serial.write(0x0d);
  }*/

  /*for(int i = 0; i < NUM_SAMPS-NUM_TAPS - 1; i++)
  {
    Serial.println(output[i]);
  }*/
  
}

void loop() {
}

/*
 * q15mpy - multiply routine for Q15 data format
 */

extern "C" {
 int q15mpy(int x, int y) {
  return (((long int) x * (long int) y) >> 15);
 }
}
