void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT); //G
  pinMode(10, OUTPUT); //B
  pinMode(11, OUTPUT); //R
}

void loop() {
  verde();
  delay(1000);
  
  for (int i = 0; i < 5; i++){
    giallo();
    delay(1000);
    nero();
    delay(1000);
  }

  rosso();
  delay(1000);
}

