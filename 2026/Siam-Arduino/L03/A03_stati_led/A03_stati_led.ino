int stato = 0;

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(9, OUTPUT);
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
  }
}

void stato_0(){
  //loop per lo stato 0
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  if (!digitalRead(2)){
    stato = 1;
    delay(300);
  }
}

void stato_1(){
  //loop per lo stato 1
  digitalWrite(9, LOW);
  digitalWrite(10, HIGH);
  if (!digitalRead(2)){
    stato = 2;
    delay(300);
  }
}

void stato_2(){
  //loop per lo stato 2
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  if (!digitalRead(2)){
    stato = 0;
    delay(300);
  }
}