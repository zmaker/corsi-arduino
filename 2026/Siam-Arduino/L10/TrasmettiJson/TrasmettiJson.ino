#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define WIFI_SSID "Siam-IoT-Net 2.4"
#define WIFI_PASSWORD "Siam1838"
#define NR_SERVER_URL "http://172.16.206.58:1880/sensori"

void setup() {
  Serial.begin(115200);
  delay(3000);
  Serial.println("IoT Client");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    //se sono collegato provo a mandare i dati
    //leggo il sensore
    int valore = readSensor();
    
    //Creo un pacchetto json
    // 1. Crea l'oggetto JSON (allochiamo 128 byte di memoria)
    StaticJsonDocument<128> doc;
    doc["tipo_sensore"] = "temp";
    doc["valore"] = valore;
    doc["tempomisura"] = millis();
    String pacchettino;
    serializeJson(doc, pacchettino);

    //trasmetto il pacchetto al server con una POST
    HTTPClient http;
    //gli passo l'indirizzo del server node-red
    http.begin(NR_SERVER_URL);
    //specifico che dati invierò (json) 
    http.addHeader("Content-Type", "application/json");
    //invio i dati in POST
    int code = http.POST(pacchettino);
    //chiudo la connessione
    http.end();
  }
  delay(10000);
}
