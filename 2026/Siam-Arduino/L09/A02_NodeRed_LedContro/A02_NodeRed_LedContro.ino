void setup() {
  Serial.begin(9600);
  //collego un led sul pin 3
  pinMode(3, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    //se ci sono dati in arrivo dalla seriale
    //li posso leggere qui
    char ch = Serial.read();
    if (ch == 'a') {
      //accendo il led
      digitalWrite(3, HIGH);  
    }
    if (ch == 's') {
      //spengo il led
      digitalWrite(3, LOW);  
    }
  }
}
