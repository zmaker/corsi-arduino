#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// ===== CONFIG WIFI =====
const char* ssid     = "www.reelco.it";
const char* password = "*1000balene";

// ===== CONFIG BROKER MQTT =====
const char* mqtt_server = "broker.hivemq.com"; // IP broker
const int mqtt_port = 1883;
const char* mqtt_user = "";   // se richiesto
const char* mqtt_password = "";

// ===== VAR =====
WiFiClient espClient;
PubSubClient client(espClient);

// ===== SENSOR =====
const int sensorPin = 3;

float readSensor() {
  //int raw = analogRead(sensorPin);
  int raw = random(0, 10);
  return raw; // esempio: scala 0-100
}

// ===== FUNZIONI =====
void setup_wifi() {
  delay(10);
  Serial.println("Connettendo WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connesso");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connessione MQTT...");
    if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
      Serial.println("Connesso");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" ritento in 5s");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Leggi sensore
  float value = readSensor();

  // Crea JSON
  StaticJsonDocument<200> doc;
  doc["sensorId"] = "sensore1";
  doc["value"] = value;
  doc["timestamp"] = millis();

  char buffer[256];
  serializeJson(doc, buffer);

  // Pubblica MQTT
  client.publish("sensori/dati", buffer);

  Serial.println("Dati inviati: ");
  Serial.println(buffer);

  delay(5000); // invia ogni 5 secondi
}