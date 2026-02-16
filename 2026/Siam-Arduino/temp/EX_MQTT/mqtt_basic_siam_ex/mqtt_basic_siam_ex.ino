#include <WiFi.h>
#include <PubSubClient.h>

// Configurazione WiFi
const char* ssid = "www.reelco.it";
const char* password = "*1000balene";

// Configurazione MQTT
const char* mqtt_server = "broker.hivemq.com";  // IP o hostname del broker
const int mqtt_port = 1883;                 // Porta MQTT (default 1883)
const char* mqtt_user = "";         // se necessario
const char* mqtt_password = "";     // se necessario

WiFiClient espClient;
PubSubClient client(espClient);

// Funzione per connettersi al WiFi
void setup_wifi() {
  delay(10);
  Serial.println("Connettendo al WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connesso, IP: ");
  Serial.println(WiFi.localIP());
}

// Funzione di callback MQTT (ricezione messaggi)
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Messaggio ricevuto [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Converte payload in String
  String messageTemp;
  for (unsigned int i = 0; i < length; i++) {
    messageTemp += (char)payload[i];
  }
  int value = messageTemp.toInt();

  digitalWrite(15, (value == 0? LOW : HIGH));
}

// Riconnessione al broker MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.print("Connessione al broker MQTT...");
    if (client.connect("LolinS2MiniClient", mqtt_user, mqtt_password)) {
      Serial.println("Connesso");
      // Sottoscrizione a topic (se vuoi ricevere messaggi)
      client.subscribe("siam/led15");
    } else {
      Serial.print("Fallito, rc=");
      Serial.print(client.state());
      Serial.println(" ritento in 5 secondi");
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

  // Invio dati esempio
  String payload = "Ciao dal Lolin S2 Mini!";
  client.publish("siam/topic", payload.c_str());
  String str = String(42+random(0,10));
  client.publish("siam/temp", str.c_str());
  delay(5000);  // invia ogni 5 secondi
}
