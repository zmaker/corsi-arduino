#include <WiFi.h>
#include <WebServer.h>

WebServer server(81);

void setup() {
  pinMode(15, OUTPUT);

  Serial.begin(115200);
  delay(3000);
  Serial.println("Web Server ESP32");
  //WiFi.begin("IoT - WIFI", "03GDVBH223");
  WiFi.begin("zmaker_mobile", "Vanh5150!");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nConnesso");

  Serial.println(WiFi.localIP());

  //configuro il routing
  server.on("/", pageIndex);
  server.on("/home", pageHome);
  server.on("/ledon", ledOn);
  server.on("/ledoff", ledOff);
  server.on("/sensor", readSensor);
  server.on("/saluta", saluta);
  server.onNotFound(pageError);

  //avvio il server
  server.begin();
}

void loop() {
  server.handleClient();
  delay(2);
}

void pageIndex(){
  String str = "Hello from ESP32 Web Server!";
  server.send(200, "text/plain", str);
}

void pageHome(){
  String str = "<html><body><h1>ESP32 Server</h1></body></html>";
  server.send(200, "text/html", str);
}

void pageError(){
  String str = "<html><body><h1>Not Found!</h1><a href='/'>HOME</a></body></html>";
  server.send(200, "text/html", str);
}

void ledOn() {
  digitalWrite(15, HIGH);
  String str = "<html><body><a href='/ledoff'>OFF</a></body></html>";
  server.send(200, "text/html", str);
}

void ledOff() {
  digitalWrite(15, LOW);
  String str = "<html><body><a href='/ledon'>ON</a></body></html>";
  server.send(200, "text/html", str);
}

void readSensor() {
  int val = analogRead(3);
  String str = "<html><head><meta http-equiv='refresh' content='3'></head><body>Sensor: "+String(val)+"</body></html>";
  server.send(200, "text/html", str);
}

void saluta(){
  String nome = "";
  if (server.hasArg("nome")) {
    nome = server.arg("nome");
  }

  String str = "<html><body>Ciao "+nome+"</body></html>";
  server.send(200, "text/html", str);
}