#include <HCSR04.h>

UltraSonicDistanceSensor distanceSensor(13, 12);  //TRG, ECHO

void setup () {
    Serial.begin(9600); 
}

void loop () {
  int dist = distanceSensor.measureDistanceCm();
  Serial.println(dist);
  delay(500);
}
