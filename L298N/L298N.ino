// Motor A
#define motor1In1 16
#define motor1In2 17
#define ENA 4

// Setting PWM properties
#define freq 30000
#define resolution 8
#define pwmChannel 0

int dutyCycle = 200;

void setup() {
  Serial.begin(115200);
  
  // sets the pins as outputs:
  pinMode(motor1In1, OUTPUT);
  pinMode(motor1In2, OUTPUT);
  pinMode(ENA, OUTPUT);

  // configure LED PWM functionalitites
  ledcSetup(pwmChannel, freq, resolution);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ENA, pwmChannel);
}

void loop() {
  // Move the DC motor forward at maximum speed
  Serial.println("Moving Forward");
  ledcWrite(pwmChannel, dutyCycle);
  digitalWrite(motor1In1, HIGH);
  digitalWrite(motor1In2, LOW);
  // delay(2000);

  // // Stop the DC motor
  // Serial.println("Motor stopped");
  // digitalWrite(motor1In1, LOW);
  // digitalWrite(motor1In2, LOW);
  // delay(1000);

  // // Move DC motor backwards at maximum speed
  // Serial.println("Moving Backwards");
  // digitalWrite(motor1In1, HIGH);
  // digitalWrite(motor1In2, LOW);
  // delay(2000);

  // // Stop the DC motor
  // Serial.println("Motor stopped");
  // digitalWrite(motor1In1, LOW);
  // digitalWrite(motor1In2, LOW);
  // delay(1000);

  // Move DC motor forward with increasing speed
  // digitalWrite(motor1In1, HIGH);
  // digitalWrite(motor1In2, LOW);
  // while (dutyCycle <= 255) {
  //   ledcWrite(pwmChannel, dutyCycle);
  //   Serial.print("Forward with duty cycle: ");
  //   Serial.println(dutyCycle);
  //   dutyCycle = dutyCycle + 5;
  //   delay(500);
  // }
  // dutyCycle = 200;
}