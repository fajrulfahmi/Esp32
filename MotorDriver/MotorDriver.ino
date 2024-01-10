#include <analogWrite.h>

#define ENA 27
#define ENB 16
#define IN1 26
#define IN2 14
#define IN3 17
#define IN4 18

#define ENA_B 25
#define ENB_B 13
#define IN1_B 33
#define IN2_B 32
#define IN3_B 4
#define IN4_B 19

void setup() {
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA_B, OUTPUT);
  pinMode(ENB_B, OUTPUT);
  pinMode(IN1_B, OUTPUT);
  pinMode(IN2_B, OUTPUT);
  pinMode(IN3_B, OUTPUT);
  pinMode(IN4_B, OUTPUT);
}

void loop() {
  frontA(200);
  frontB(200);
}


void frontA(int ena) {
  analogWrite(ENA, ena);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENB, ena);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void frontB(int ena) {
  analogWrite(ENA_B, ena);
  digitalWrite(IN1_B, LOW);
  digitalWrite(IN2_B, HIGH);
  analogWrite(ENB_B, ena);
  digitalWrite(IN3_B, LOW);
  digitalWrite(IN4_B, HIGH);
}
