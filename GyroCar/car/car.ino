#include <esp_now.h>
#include <WiFi.h>

unsigned long interval = 1000;
unsigned long previousMillis = 0;

typedef struct struct_message {
  int x;
  int y;
  int z;
} struct_message;

struct_message myData;

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("x: ");
  Serial.println(myData.x);
  Serial.print("y: ");
  Serial.println(myData.y);
  Serial.print("z: ");
  Serial.println(myData.z);
  Serial.println();

  if (myData.y >= 15) {
    Serial.println("forward");
    forward(180);

  } else if (myData.y <= -50) {
    Serial.println("backward");
    backward(180);

  } else if (myData.x >= 40) {
    Serial.println("turn right");
    turn_Right(180);

  } else if (myData.x <= -40) {
    Serial.println("turn left");
    turn_Left(180);

  } else if (myData.z >= 60) {
    Serial.println("rotate left");
    rotate_Left(180);

  } else if (myData.z <= -60) {
    Serial.println("rotate right");
    rotate_Right(180);

  } else {
    Serial.println("stops");
    stops();
  }
  previousMillis = millis();
}

void setup() {
  Serial.begin(115200);
  motorSetup();
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  unsigned long currentMillis = millis();
  
  if ((unsigned long)(currentMillis - previousMillis) >= interval) {
    stops();
  }
}
