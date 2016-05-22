  int red = 10;
  int blue = 6;
  int green = 5;
  float segment = 1000;
  
void setup() {
  Serial.begin(9600);
  pinMode(5,OUTPUT);  //green
  pinMode(6,OUTPUT);  //blue
  pinMode(10,OUTPUT); //red

}

void loop() {
  digitalWrite(red,HIGH);
  while(millis() < segment)
  {
    analogWrite(green, millis() * 255/segment);
  }
  while(millis() < 2*segment)
  {
    analogWrite(red, HIGH - millis() * 255/segment);
  }
  while(millis() < 3*segment)
  {
    analogWrite(blue, millis() * 255/segment);
  }
  while(millis() < 4*segment)
  {
    analogWrite(green, HIGH - millis() * 255/segment);
  }
  while(millis() < 5*segment)
  {
    analogWrite(red, millis() * 255/segment);
  }
  while(millis() < 6*segment)
  {
    analogWrite(blue, HIGH - millis() * 255/segment);
  }
  digitalWrite(red,LOW);
  digitalWrite(blue,LOW);
  digitalWrite(green,LOW);
  segment += 6*segment;

}
