unsigned long interval = 1000;     // the time we need to wait
unsigned long previousMillis = 0;  // millis() returns an unsigned long.

void NTP_Server() {
  struct tm timeinfo;

  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  // Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  lcd.setCursor(0, 0);
  lcd.print(&timeinfo, "--- %H:%M:%S ---");

  //Control auto pompa active HIGH
  if ((timeinfo.tm_hour == 7) && (timeinfo.tm_min == 0) && (timeinfo.tm_sec == 0)) {
    Serial.println("Pompa Menyala Otomatis");
    digitalWrite(pompa, LOW);

  } else if ((timeinfo.tm_hour == 7) && (timeinfo.tm_min == 0) && (timeinfo.tm_sec == 10)) {
    Serial.println("Pompa Mati Otomatis");
    digitalWrite(pompa, HIGH);

  } else if ((timeinfo.tm_hour == 16) && (timeinfo.tm_min == 0) && (timeinfo.tm_sec == 0)) {
    Serial.println("Pompa Menyala Otomatis");
    digitalWrite(pompa, LOW);

  } else if ((timeinfo.tm_hour == 16) && (timeinfo.tm_min == 0) && (timeinfo.tm_sec == 10)) {
    Serial.println("Pompa Mati Otomatis");
    digitalWrite(pompa, HIGH);
  }

  Serial.println();
}

void ntpBegin() {
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" CONNECTED");

  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  NTP_Server();

  //disconnect WiFi as it's no longer needed
  // WiFi.disconnect(true);
  // WiFi.mode(WIFI_OFF);
}

void sensorDHT11() {
  int hum = dht.readHumidity();
  int temp = dht.readTemperature();

  if (isnan(hum) || isnan(temp)) {
    Serial.println("Gagal Membaca DHT sensor!");
    return;
  }
  Serial.println("Humidity: " + (String)hum + " %");
  Serial.println("Temperature: " + (String)temp + " " + (char)223 + "C");

  Blynk.virtualWrite(V0, hum);
  Blynk.virtualWrite(V1, temp);
  temperatur = temp;
  kelembapan = hum;
}

void sensorMoisture() {
  int A = analogRead(moistureA);
  int B = analogRead(moistureB);
  int R = (A + B)/2;

  int moistureValue = map(R, 4095, 0, 0, 100);

  Serial.print("moisture : ");
  Serial.println((String)moistureValue + "%");

  rk = moistureValue;

  Blynk.virtualWrite(V2, moistureValue);
}

BLYNK_WRITE(V4) {
  int btn = param.asInt();
  Serial.print("BUTTON POMPA :");
  Serial.println(btn);
  if (btn == 1) digitalWrite(pompa, LOW);
  if (btn == 0) digitalWrite(pompa, HIGH);
}

BLYNK_WRITE(V5) {
  int btn = param.asInt();
  Serial.print("BUTTON LED  :");
  Serial.println(btn);
  if (btn == 1) digitalWrite(fan, LOW);
  if (btn == 0) digitalWrite(fan, HIGH);
}

BLYNK_WRITE(V6) {
  int btn = param.asInt();
  Serial.print("BUTTON LED  :");
  Serial.println(btn);
  if (btn == 1) digitalWrite(led, LOW);
  if (btn == 0) digitalWrite(led, HIGH);
}

void lcdVisual() {
  lcd.setCursor(0, 1);
  lcd.print("t: " + (String)temperatur + (char)223 + "C");

  lcd.setCursor(9, 1);
  lcd.print("h: " + (String)kelembapan + "%");
  delay(2000);
  lcd.setCursor(0, 1);
  lcd.print("                 ");

  lcd.setCursor(0, 1);
  lcd.print("Kelembapan: " + (String)rk + "%");

  // lcd.setCursor(9, 1);
  // lcd.print("k2: " + (String)k2 + "%");
  delay(2000);
  lcd.setCursor(0, 1);
  lcd.print("                 ");

  // if ((unsigned long)(currentMillis - previousMillis) >= 1000) {
  //   lcd.setCursor(3, 1);
  //   lcd.print("      ");

  //   lcd.setCursor(11, 1);
  //   lcd.print("      ");
  //   previousMillis = millis();
  // }
}
