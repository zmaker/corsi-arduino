#include <OneButton.h>

OneButton btn = OneButton(
  2,  // Input pin for the button
  true,        // Button is active LOW
  true         // Enable internal pull-up resistor
);

void setup() {
  Serial.begin(9600);
  Serial.println("test one button");
  btn.attachClick(hello);
  btn.attachDoubleClick(hello2);
}

void loop() {
  btn.tick();
}

static void hello() {
  Serial.println("CLICK!!!!");
}

static void hello2() {
  Serial.println("DOPPIO CLICK!!!!");
}
