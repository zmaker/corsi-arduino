void setup() {
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop() {
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  delay(1000);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  delay(1000);  
}
