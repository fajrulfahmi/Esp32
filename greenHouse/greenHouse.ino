#include "library.h"  
#include <BlynkSimpleEsp32.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

#define BLYNK_PRINT Serial

char auth[] = BLYNK_AUTH_TOKEN;
BlynkTimer timer;

void setup() {
  Serial.begin(115200);
    //pinMode
  pinMode(moistureA, INPUT);
  pinMode(moistureB, INPUT);
  pinMode(pompa, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(led, OUTPUT);
  
  Blynk.begin(auth, ssid, password, "blynk.cloud", 80);
  dht.begin();
  ntpBegin();

  lcd.init();
  lcd.backlight();

  //interval Blynk
  timer.setInterval(100L, sensorDHT11);
  timer.setInterval(100L, sensorMoisture);
}

void loop() {
  Blynk.run();
  timer.run();
  NTP_Server();
  lcdVisual();
}
