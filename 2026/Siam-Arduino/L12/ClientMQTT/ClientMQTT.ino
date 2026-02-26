#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// --- Configurazione Rete ---
const char* ssid = "Siam-IoT-Net 2.4";
const char* password = "Siam1838";

// --- Configurazione MQTT ---
const char* mqtt_server = "broker.hivemq.com"; // Esempio di broker pubblico
const int mqtt_port = 1883;
const char* topic = "/aula/temp"; //qui trasmetto/pubblico
const char* topicrx = "/paolo/123/led"; //topic di ricezione/che ascolto

WiFiClient espClient;
PubSubClient client(espClient);

// Funzione per connettersi al WiFi
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connessione a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connesso");
  Serial.print("Indirizzo IP: ");
  Serial.println(WiFi.localIP());
}

// Funzione di callback (eseguita quando arriva un messaggio)
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Messaggio ricevuto sul topic [");
  Serial.print(topic);
  Serial.print("]: ");
  
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);

  int stato = message.toInt();
  digitalWrite(15, stato);
}

// Funzione di riconnessione al Broker
void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentativo di connessione MQTT...");
    // ID Client univoco (puoi personalizzarlo)
    String clientId = "ESP32Client-Aula-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("connesso!");
      // Una volta connesso, ci iscriviamo al topic
      client.subscribe(topicrx);
    } else {
      Serial.print("fallito, rc=");
      Serial.print(client.state());
      Serial.println(" riprovo tra 5 secondi");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  pinMode(15, OUTPUT);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Esempio: Invia un messaggio ogni 10 secondi
  static unsigned long lastMsg = 0;
  unsigned long now = millis();
  if (now - lastMsg > 10000) {
    lastMsg = now;

    StaticJsonDocument<200> doc;
    doc["id"] = 123;
    doc["value"] = random(10, 30);
    doc["ts"] = millis();

    char msg[200];
    serializeJson(doc, msg);
    
    client.publish(topic, msg);
  }
}