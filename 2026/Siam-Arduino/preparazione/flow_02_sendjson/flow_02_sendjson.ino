#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// ====== CONFIG ======
const char* ssid     = "www.reelco.it";
const char* password = "*1000balene";
const char* serverUrl = "http://192.168.0.109:1880/sensore";  // Cambialo con il tuo server

// ====== SENSORE (ESEMPIO) ======
const int sensorPin = 34; // pin analogico
float readSensor() {
  int raw = analogRead(sensorPin);
  return (raw / 4095.0) * 100.0; // esempio di scalatura
}

void setup() {
  Serial.begin(115200);

  // Connetti Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connesso!");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {

    // Leggi sensore
    float value = readSensor();

    // Serializza JSON
    StaticJsonDocument<200> jsonDoc;
    jsonDoc["sensorId"] = "sensore1";
    jsonDoc["value"]    = value;
    jsonDoc["timestamp"] = millis();

    String payload;
    serializeJson(jsonDoc, payload);

    // HTTP POST
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(payload);

    if (httpResponseCode > 0) {
      Serial.printf("POST Response Code: %d\n", httpResponseCode);
      String resp = http.getString();
      Serial.println(resp);
    } else {
      Serial.printf("POST error: %s\n", http.errorToString(httpResponseCode).c_str());
    }

    http.end();
  }

  delay(10000); // invia ogni 5 secondi
}
