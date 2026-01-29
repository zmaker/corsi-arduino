int conteggio = 0;
int pv_bt;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  Serial.println("conta pezzi");
}

void loop() {
  int bt = !digitalRead(2);

  if (bt && !pv_bt) {
    conteggio++;
    Serial.println(conteggio);
  }

  pv_bt = bt;
}
