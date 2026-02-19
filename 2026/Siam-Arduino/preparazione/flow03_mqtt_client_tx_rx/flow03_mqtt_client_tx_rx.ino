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

      // Iscrizione al topic dei comandi
      client.subscribe("sensori/comandi"); 

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

  pinMode(2, OUTPUT);

  //imposta la funzone da cahiamare quando ricevo
  client.setCallback(callback);
}

unsigned long t1;

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if ((millis() - t1) >= 10000) {
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

    t1 = millis();
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Copia il payload in una stringa
  String msg;
  for (unsigned int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }
  Serial.print("Messaggio ricevuto su topic ");
  Serial.print(topic);
  Serial.print(": ");
  Serial.println(msg);

  // Converti JSON in oggetto
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, msg);
  if (error) {
    Serial.println("Errore deserializzazione JSON");
    return;
  }

  //String id = doc["id"];
  int id = doc["id"];
  int valore = doc["valore"];

  // Esempio di azione in base al valore
  if (id == 123) {
    if (valore == 1) {
      Serial.println("Accendo LED");
      digitalWrite(2, HIGH);
    } else {
      Serial.println("Spengo LED");
      digitalWrite(2, LOW);
    }
  }
}
