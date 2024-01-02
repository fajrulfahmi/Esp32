#include "DHT.h"            // Inisiasi library DHT11
#define DHTPIN 23           // Buat variabel DHTPIN, mengarah pada pin
#define DHTTYPE DHT11       // Tentukan tipe DHT menjadi DHT11
DHT dht(DHTPIN, DHTTYPE);   // Buat objek dht

void setup() {
  Serial.begin(9600);      // Buka komunikasi serial pada baudrate 9600
  dht.begin();             // Inisiasi objek dht
}

void loop() {
  float hum = dht.readHumidity();      // Baca kelembapan
  float temp = dht.readTemperature();  // Baca temperatur
  if (isnan(hum) || isnan(temp)) {     // Cek jika sensor error
      Serial.println("Gagal Membaca DHT sensor!");
      return;
  }
  Serial.println("Humidity: " + (String)hum + " %");       // Print kelembapan (%)
  Serial.println("Temperature: " + (String)temp + " " + (char)223 +"C");  // Print temperatur (*C)
  delay(1000);
}
