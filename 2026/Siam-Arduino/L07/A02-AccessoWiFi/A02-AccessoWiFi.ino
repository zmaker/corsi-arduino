#include <WiFi.h>

void setup() {
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

  delay(5000);
  WiFi.disconnect();
  Serial.println("Disconnesso!");

}

void loop() {
  delay(10);
}
