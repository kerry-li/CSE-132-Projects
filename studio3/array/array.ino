/* array
 *
 * arrays and indexing in assembly language
 *
 * the assembly language code goes in the file array.S, in the libraries directory
 */

#include <array.h>

extern "C" {
 void printRegs(void); //function prototype
}

byte sum = 0;
byte val[8] = {0, 5, 2, 7, 16, 24, 2, 1};

void setup() {
  Serial.begin(9600);

  //invoke the assembly language code
  array();

  //you can put Serial.print() or Serial.println() calls here:
  Serial.print(sum);


}

void loop() {
}
