#include <Servo.h>

Servo s1;

void setup() {
  s1.attach(9);
}

void loop() {
  int val = analogRead(A0); //0 - 1023
  int pos = map(val, 0, 1023, 0, 180 );
  s1.write(pos);
  delay(10);
}
