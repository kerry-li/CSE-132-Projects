  int red = 10;
  int blue = 6;
  int green = 5;

void setup() {
  Serial.begin(9600);
  pinMode(5,OUTPUT);  //green
  pinMode(6,OUTPUT);  //blue
  pinMode(10,OUTPUT); //red

  //digitalWrite(10,HIGH);

}

void loop() {
  digitalWrite(red,HIGH); //red off
  delay(500);
  digitalWrite(red,LOW); //red off
  digitalWrite(green,HIGH); //green
  delay(500);
  digitalWrite(green,LOW);  //green off
  digitalWrite(blue,HIGH);  //blue
  delay(500);
  digitalWrite(blue,LOW); //blue off
  digitalWrite(red,HIGH); //yellow
  digitalWrite(green,HIGH);
  delay(500);
  digitalWrite(green,LOW); 
  digitalWrite(blue,HIGH);  //magenta = blue + red
  delay(500);
  digitalWrite(red,LOW);
  digitalWrite(green,HIGH);
  delay(500);
  digitalWrite(red,HIGH);
  delay(500);
  digitalWrite(red,LOW);
  digitalWrite(blue,LOW);
  digitalWrite(green,LOW);
}
