#include <WiFi.h>

const char* ssid = "admin1";
const char* password = "123456789";

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.println("WIFI Connected");

}

void setup() {
  Serial.begin(115200);
  initWiFi();
}

void loop() {
}