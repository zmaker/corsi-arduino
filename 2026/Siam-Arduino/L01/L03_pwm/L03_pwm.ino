int lum = 127;

void setup() {
  pinMode(10, OUTPUT);
}

void loop() {
  for (lum = 0; lum < 256; lum++){
    analogWrite(10, lum);
    delay(10);
  }
  for ( lum = 255 ; lum >= 0 ; lum-- ){
    analogWrite(10, lum);
    delay(10);
  }
}
