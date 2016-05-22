/**************************************************************************
 * Demo of Accelerometer with LCD for CSE132
 * Baud rate is faster than previous value
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
  
  mma.setRange(MMA8451_RANGE_8_G);
  
  Serial.print("Range = "); Serial.print(2 << mma.getRange());  
  Serial.println("G");

  lcd.init ();
  lcd.setContrast(0);  
  lcd.setCursor (0,0);
  lcd.print("Orientation") ;
}

void loop() {
  // Read the 'raw' data in 14-bit counts
  mma.read();

  /* Get a new sensor event */ 
  sensors_event_t event; 
  mma.getEvent(&event);

  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("X: \t"); Serial.print(event.acceleration.x); Serial.print("\t");
  Serial.print("Y: \t"); Serial.print(event.acceleration.y); Serial.print("\t");
  Serial.print("Z: \t"); Serial.print(event.acceleration.z); Serial.print("\t");
  Serial.print("m/s^2 ");
  
  /* Get the orientation of the sensor */
  uint8_t o = mma.getOrientation();
  
  
  
 lcd.setCursor (1,0);
 switch (o) {
    case MMA8451_PL_PUF: 
      Serial.println("Portrait Up Front");
      lcd.print("Pt Up Front     ");
      break;
    case MMA8451_PL_PUB: 
      Serial.println("Portrait Up Back");
      lcd.print("Pt Up Back      ");
      break;    
    case MMA8451_PL_PDF: 
      Serial.println("Portrait Down Front");
      lcd.print("Pt Down Front   ");
      break;
    case MMA8451_PL_PDB: 
      Serial.println("Portrait Down Back");
      lcd.print("Pt Down Back    ");
      break;
    case MMA8451_PL_LRF: 
      Serial.println("Landscape Right Front");
      lcd.print("Lscp Right Front");
      break;
    case MMA8451_PL_LRB: 
      Serial.println("Landscape Right Back");
      lcd.print("Lscp Right Back ");
      break;
    case MMA8451_PL_LLF: 
      Serial.println("Landscape Left Front");
      lcd.print("Lscp Left Front ");
      break;
    case MMA8451_PL_LLB: 
      Serial.println("Landscape Left Back");
      lcd.print("Lscp Left Back  ");
      break;
    }
//  Serial.println();
  delay(10);
  
}
