#define trig 16
#define echo 17

float durasi, jarak;

void setup() {
  Serial.begin (9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  durasi = pulseIn(echo, HIGH);
  jarak = 0.017 * durasi;

  Serial.print("distance: ");
  Serial.print(jarak);
  Serial.println(" cm");

}
