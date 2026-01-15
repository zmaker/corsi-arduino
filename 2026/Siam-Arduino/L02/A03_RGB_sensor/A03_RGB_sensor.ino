void setup() {
  Serial.begin(9600);
}

void loop() {
  int v = analogRead(A0);
  Serial.println(v);

  if (v < 100) {
    analogWrite(9, 255);
    analogWrite(10, 0);
    analogWrite(11, 0);
  } else if (v < 250) {
    analogWrite(9, 0);
    analogWrite(10, 255);
    analogWrite(11, 0);
  } else {
    analogWrite(9, 0);
    analogWrite(10, 0);
    analogWrite(11, 255);
  }

  delay(100);
}
