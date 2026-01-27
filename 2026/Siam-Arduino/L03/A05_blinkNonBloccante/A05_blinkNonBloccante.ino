/*
 - blink del led sul pin 10
 - led sul pin 9 controllato dal bt sul pin 2
*/

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop() {
  digitalWrite(10, !digitalRead(10));
  delay(1000);
  
  if (!digitalRead(2)) {
    digitalWrite(9, HIGH);
  } else {
    digitalWrite(9, LOW);
  }
}
