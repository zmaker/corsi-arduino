#include <WiFi.h>
#include <HTTPClient.h>

void setup() {
  pinMode(15, OUTPUT);

  Serial.begin(115200);
  delay(3000);
  Serial.println("WiFi Client");

  WiFi.begin("IoT - WIFI", "03GDVBH223");

  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    digitalWrite(15, !digitalRead(15));
    Serial.print(".");
  }
  digitalWrite(15, LOW);
  Serial.println("\nConnesso!");

  Serial.print("IP: "); Serial.println(WiFi.localIP());

  HTTPClient http;
  //http.begin("http://www.google.com");
  http.begin("https://jsonplaceholder.typicode.com/posts/3");
  int httpcode = http.GET();
  if (httpcode > 0) {
    Serial.print("HTTP code: ");Serial.println(httpcode);
    String page = http.getString();
    Serial.println(page);
  }
  http.end();
  WiFi.disconnect();

}

void loop() {
  delay(100);
}
