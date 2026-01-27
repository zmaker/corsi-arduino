int stato_led;

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(10, OUTPUT);
  stato_led = LOW;
}

void loop() {
  if (!digitalRead(2)) {
    stato_led = !stato_led;
    delay(300);
  }

  digitalWrite(10, stato_led);
}
