void setup() {
  tone(9, 440, 500);
  delay(600);
  tone(9, 523, 500);
  delay(600);
  tone(9, 523, 500);
  delay(600);

}

void loop() {
  int f = random(100, 800);
  int d = 400;
  tone(9, f, d);
  delay(d*1.1);
}
