#include <WiFi.h>

void setup() {
  pinMode(15, OUTPUT);

  Serial.begin(115200);
  delay(3000);
  Serial.println("WiFi Connex");

  WiFi.begin("IoT - WIFI", "03GDVBH223");

  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnesso!");

  Serial.print("IP: "); Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    //se la scheda si scollega, cerco di ricollegarmi
    WiFi.disconnect();
    delay(1000);
    WiFi.reconnect();
  }

  digitalWrite(15, !digitalRead(15));
  delay(2000);
}
