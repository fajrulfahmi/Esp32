#include <esp_now.h>
#include <WiFi.h>

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
  int id;
  int x;
  int y;
  // int id2;
  // int x2;
  // int y2;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("id : ");
  Serial.println(myData.id);
  Serial.print("x  : ");
  Serial.println(myData.x);
  Serial.print("y  : ");
  Serial.println(myData.y);
  Serial.println();

  // Serial.print("id 2 : ");
  // Serial.println(myData.id2);
  // Serial.print("x2   : ");
  // Serial.println(myData.x2);
  // Serial.print("y2   : ");
  // Serial.println(myData.y2);
  // Serial.println();
  // Serial.println();
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {

}
