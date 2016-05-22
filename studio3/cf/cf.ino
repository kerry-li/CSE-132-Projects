/* cf
 *
 * control flow in assembly language
 *
 * the assembly language code goes in the file cf.S, in the libraries directory
 */

#include <cf.h>

extern "C" {
 void printRegs(void); //function prototype
}

byte a = 0;
byte b = 1;
byte c = 0;
byte d = 0;

void setup() {
  Serial.begin(9600);

  //invoke the assembly language code
  cf();

  //you can put Serial.print() or Serial.println() calls here:


}

void loop() {
}
