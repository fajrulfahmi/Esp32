  #define led 33

int ledState = LOW;
unsigned long previousMillis = 0;
long OnTime = 3000;
long OffTime = 60000;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if ((ledState == HIGH) && (currentMillis - previousMillis >= OnTime)) {
    ledState = LOW;
    previousMillis = currentMillis;
    digitalWrite(led, ledState);
    Serial.println("LED MATI");
    
  } else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime)) {
    ledState = HIGH;
    previousMillis = currentMillis;
    digitalWrite(led, ledState);
    Serial.println("LED HIDUP");
  }
}
