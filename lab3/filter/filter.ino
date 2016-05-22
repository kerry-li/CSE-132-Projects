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

  for(int i = 0; i < NUM_SAMPS-NUM_TAPS - 1; i++)
  {
    Serial.println(output[i]);
  }

  //invoke the assembly language code
  //filter();
  
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
