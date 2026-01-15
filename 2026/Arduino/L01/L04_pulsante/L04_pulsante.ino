void setup() {
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  int bt = digitalRead(2);
  if (bt) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
}
