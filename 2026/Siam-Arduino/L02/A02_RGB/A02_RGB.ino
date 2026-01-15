void setup() {

}

void loop() {
  int r = random(256);
  int g = random(256);
  int b = random(256);
  analogWrite(9, r);
  analogWrite(10, g);
  analogWrite(11, b);
  delay(1000);
}
