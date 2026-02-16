float temp = 24.0;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A1));
}

void loop() {
  temp = random(100, 300) / 10.0;
  Serial.println(temp);
  delay(4000);
}
