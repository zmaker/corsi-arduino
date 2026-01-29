int conteggio = 0;
int pv_bt;
unsigned long t1, t2;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  Serial.println("conta pezzi");
}

void loop() {
  int bt = !digitalRead(2);

  //fronte di salita
  if (bt && !pv_bt) {
    conteggio++;
    Serial.println("FDS");
    t1 = millis();
  }

  //fronte di discesa
  if (!bt && pv_bt) {
    Serial.println("FDD");
    t2 = millis();
    Serial.print("t: ");Serial.println(t2-t1);
    if ((t2-t1) < 1000) {
      Serial.println("CLICK");
    } else {
      Serial.println("LONG CLICK");
    }
  }

  pv_bt = bt;
}
