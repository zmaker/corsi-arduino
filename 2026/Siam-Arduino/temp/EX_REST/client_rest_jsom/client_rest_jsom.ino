#include <WiFi.h>
#include <HTTPClient.h>

#include <ArduinoJson.h>

// Configurazione WiFi
const char* ssid = "www.reelco.it";
const char* password = "*1000balene";

// URL del servizio REST
const char* serverName = "http://192.168.0.109:1880/sensore"; // sostituisci con l'IP di Node-RED

void setup() {
  Serial.begin(115200);
  delay(100);

  // Connessione WiFi
  Serial.print("Connessione a WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connesso");
  Serial.println(WiFi.localIP());
}

void loop() {
  if ((WiFi.status() == WL_CONNECTED)) {
    HTTPClient http;

    http.begin(serverName); // Inizializza client HTTP
    int httpResponseCode = http.GET(); // Esegue la GET

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString(); // Riceve la risposta
      Serial.println("Dati ricevuti:");
      Serial.println(payload);

      StaticJsonDocument<200> doc;
      deserializeJson(doc, payload);
      int temperatura = doc["temperatura"];
      int umidita = doc["umidita"];
      Serial.println(temperatura);
      Serial.println(umidita);

    } else {
      Serial.print("Errore nella richiesta: ");
      Serial.println(httpResponseCode);
    }

    http.end(); // Chiude la connessione
  } else {
    Serial.println("WiFi non connesso");
  }

  delay(5000); // Interroga ogni 5 secondi
}
