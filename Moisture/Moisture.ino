#define moisture 14

void setup() {
  Serial.begin(115200);
  pinMode(moisture, INPUT);
}

void loop() {
  int moistureValue = analogRead(moisture);
  Serial.print("Moisture value: ");
  Serial.println(moistureValue);
  delay(500);
}
