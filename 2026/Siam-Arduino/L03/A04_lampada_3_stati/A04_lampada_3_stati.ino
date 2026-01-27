int stato = 0;

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(10, OUTPUT);
}

void loop() {
  switch(stato){
    case 0:
      stato_0();
      break;
    case 1:
      stato_1();
      break;
    case 2:
      stato_2();
      break;
    case 3:
      stato_3();
      break;
  }
}

void stato_0(){
  //loop per lo stato 0
  // led spento
  digitalWrite(10, LOW);

  if (!digitalRead(2)){
    stato = 1;
    delay(300);
  }
}

void stato_1(){
  //loop per lo stato 1
  // led al 50%
  analogWrite(10, 127);
  
  if (!digitalRead(2)){
    stato = 2;
    delay(300);
  }
}

void stato_2(){
  //loop per lo stato 2
  // led acceso al 100%
  digitalWrite(10, HIGH);

  if (!digitalRead(2)){
    stato = 3;
    delay(300);
  }
}

void stato_3(){
  //loop per lo stato 3
  digitalWrite(10, LOW);
  delay(500);
  digitalWrite(10, HIGH);
  delay(500);

  if (!digitalRead(2)){
    digitalWrite(10, LOW);
    stato = 0;
    delay(300);
  }
}

