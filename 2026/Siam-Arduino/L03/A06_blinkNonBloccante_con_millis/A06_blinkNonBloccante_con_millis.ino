/*
 - blink del led sul pin 10
 - led sul pin 9 controllato dal bt sul pin 2
*/
unsigned long t1;

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  t1 = millis();
}

void loop() {
  if ((millis() - t1) > 1000) {
    digitalWrite(10, !digitalRead(10));
    t1 = millis();
  }
  
  if (!digitalRead(2)) {
    digitalWrite(9, HIGH);
  } else {
    digitalWrite(9, LOW);
  }
}
