/* Kerry Li
 * Lab Section B
 * kerryli@wustl.edu
 * CSE 132 Lab 2
 *  
 * temperature
 *
 * read temperature from TMP36 sensor every second using better timing method
 *
 */
const int analogInPin = A0;  // Analog input pin
const int filterSize = 20;
int loopEndTime = 0;

void setup() {
  analogReference(INTERNAL);
  Serial.begin(9600);
}

/*void loop() {
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

  Serial.print(millis());
  Serial.print(", ");
  Serial.print(lastCount);
  Serial.print(", ");
  Serial.print(lastTemp);
  Serial.print(", ");
  Serial.print(avgTemp);

  Serial.println();

  delay(1000);
}*/

void loop() {
  if(millis() >= loopEndTime) {
    loopEndTime += 1000;

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
  
    Serial.print(millis());
    Serial.print(", ");
    Serial.print(lastCount);
    Serial.print(", ");
    Serial.print(lastTemp);
    Serial.print(", ");
    Serial.print(avgTemp);
  
    Serial.println();
      
  }
}

