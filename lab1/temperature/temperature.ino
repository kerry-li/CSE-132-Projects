/* Kerry Li
 * Lab Section B
 * kerryli@wustl.edu
 * CSE 132 Lab 1
 *  
 * temperature
 *
 * read temperature from TMP36 sensor every second
 *
 */
const int analogInPin = A0;  // Analog input pin
const int filterSize = 10;

void setup() {
  analogReference(INTERNAL);
  Serial.begin(115200);
}

void loop() {
  int totalCounts = 0;
  int avgCounts = 0;
  int lastCount = 0;
  float avgTemp = 0;
  float lastTemp = 0;
  
  for(int i = 0; i < filterSize; i++) {
    if(i == filterSize - 1) {
      lastCount = analogRead(analogInPin);
      totalCounts += lastCount;
    }
    else {
      totalCounts += analogRead(analogInPin);
    }
  }

  avgCounts = totalCounts/filterSize;
  avgTemp = (float)avgCounts*100*1.1/1023 - 50;
  lastTemp = (float)lastCount*100*1.1/1023 - 50;
  
  /*Serial.print("Average Counts: ");
  Serial.println(avgCounts);

  Serial.print("Avg Temp: ");
  Serial.println(avgTemp);

  Serial.print("Last read count: ");
  Serial.println(lastCount);
  
  Serial.print("Last read temp: ");
  Serial.println(lastTemp);*/

  Serial.print(lastCount);
  Serial.print(", ");
  Serial.print(lastTemp);
  Serial.print(", ");
  Serial.print(avgTemp);

  Serial.println();

  delay(1000);
}
