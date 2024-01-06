// Motor A
#define enaA 4
#define motor1In1 16
#define motor1In2 17
#define enbA 21
#define motor2In3 18
#define motor2In4 19

// Motor B
#define enaB 32
#define motor3In1 33
#define motor3In2 25
#define enbB 13
#define motor4In3 26
#define motor4In4 27

// PWM properties
#define freq 30000
#define resolution 8
#define pwmChannelEnaA 0
#define pwmChannelEnbA 1
#define pwmChannelEnaB 2
#define pwmChannelEnbB 3


void motorSetup() {
  pinMode(enaA, OUTPUT);
  pinMode(motor1In1, OUTPUT);
  pinMode(motor1In2, OUTPUT);
  pinMode(enbA, OUTPUT);
  pinMode(motor2In3, OUTPUT);
  pinMode(motor2In4, OUTPUT);

  pinMode(enaB, OUTPUT);
  pinMode(motor3In1, OUTPUT);
  pinMode(motor3In2, OUTPUT);
  pinMode(enbB, OUTPUT);
  pinMode(motor4In3, OUTPUT);
  pinMode(motor4In4, OUTPUT);

  ledcSetup(pwmChannelEnaA, freq, resolution);
  ledcSetup(pwmChannelEnbA, freq, resolution);
  ledcSetup(pwmChannelEnaB, freq, resolution);
  ledcSetup(pwmChannelEnbB, freq, resolution);

  ledcAttachPin(enaA, pwmChannelEnaA);
  ledcAttachPin(enbA, pwmChannelEnbA);
  ledcAttachPin(enaB, pwmChannelEnaB);
  ledcAttachPin(enbB, pwmChannelEnbB);
}

void forward(int motor) {
  ledcWrite(pwmChannelEnaA, motor);
  ledcWrite(pwmChannelEnbA, motor);
  ledcWrite(pwmChannelEnaB, motor);
  ledcWrite(pwmChannelEnbB, motor);

  // Back
  digitalWrite(motor1In1, LOW);
  digitalWrite(motor1In2, HIGH);
  digitalWrite(motor2In3, LOW);
  digitalWrite(motor2In4, HIGH);

  // Front
  digitalWrite(motor3In1, LOW);
  digitalWrite(motor3In2, HIGH);
  digitalWrite(motor4In3, LOW);
  digitalWrite(motor4In4, HIGH);
}

void backward(int motor) {
  ledcWrite(pwmChannelEnaA, motor);
  ledcWrite(pwmChannelEnbA, motor);
  ledcWrite(pwmChannelEnaB, motor);
  ledcWrite(pwmChannelEnbB, motor);

  // Back
  digitalWrite(motor1In1, HIGH);
  digitalWrite(motor1In2, LOW);
  digitalWrite(motor2In3, HIGH);
  digitalWrite(motor2In4, LOW);

  // Front
  digitalWrite(motor3In1, HIGH);
  digitalWrite(motor3In2, LOW);
  digitalWrite(motor4In3, HIGH);
  digitalWrite(motor4In4, LOW);
}

void turn_Right(int motor) {
  ledcWrite(pwmChannelEnaA, motor);
  ledcWrite(pwmChannelEnbA, motor);
  ledcWrite(pwmChannelEnaB, motor);
  ledcWrite(pwmChannelEnbB, motor);

  // Back
  digitalWrite(motor1In1, LOW);
  digitalWrite(motor1In2, HIGH);
  digitalWrite(motor2In3, HIGH);
  digitalWrite(motor2In4, LOW);

  // Front
  digitalWrite(motor3In1, LOW);
  digitalWrite(motor3In2, HIGH);
  digitalWrite(motor4In3, HIGH);
  digitalWrite(motor4In4, LOW);
}

void turn_Left(int motor) {
  ledcWrite(pwmChannelEnaA, motor);
  ledcWrite(pwmChannelEnbA, motor);
  ledcWrite(pwmChannelEnaB, motor);
  ledcWrite(pwmChannelEnbB, motor);

  // Back
  digitalWrite(motor1In1, HIGH);
  digitalWrite(motor1In2, LOW);
  digitalWrite(motor2In3, LOW);
  digitalWrite(motor2In4, HIGH);

  // Front
  digitalWrite(motor3In1, HIGH);
  digitalWrite(motor3In2, LOW);
  digitalWrite(motor4In3, LOW);
  digitalWrite(motor4In4, HIGH);
}

void rotate_Right(int motor) {
  ledcWrite(pwmChannelEnaA, motor);
  ledcWrite(pwmChannelEnbA, motor);
  ledcWrite(pwmChannelEnaB, motor);
  ledcWrite(pwmChannelEnbB, motor);

  // Back
  digitalWrite(motor1In1, HIGH);
  digitalWrite(motor1In2, LOW);
  digitalWrite(motor2In3, LOW);
  digitalWrite(motor2In4, HIGH);

  // Front
  digitalWrite(motor3In1, LOW);
  digitalWrite(motor3In2, HIGH);
  digitalWrite(motor4In3, HIGH);
  digitalWrite(motor4In4, LOW);
}

void rotate_Left(int motor) {
  ledcWrite(pwmChannelEnaA, motor);
  ledcWrite(pwmChannelEnbA, motor);
  ledcWrite(pwmChannelEnaB, motor);
  ledcWrite(pwmChannelEnbB, motor);

  // Back=
  digitalWrite(motor1In1, LOW);
  digitalWrite(motor1In2, HIGH);
  digitalWrite(motor2In3, HIGH);
  digitalWrite(motor2In4, LOW);

  // Front
  digitalWrite(motor3In1, HIGH);
  digitalWrite(motor3In2, LOW);
  digitalWrite(motor4In3, LOW);
  digitalWrite(motor4In4, HIGH);
}

void stops() {
  ledcWrite(pwmChannelEnaA, 0);
  ledcWrite(pwmChannelEnbA, 0);
  ledcWrite(pwmChannelEnaB, 0);
  ledcWrite(pwmChannelEnbB, 0);
  digitalWrite(motor1In1, LOW);
  digitalWrite(motor1In2, LOW);
  digitalWrite(motor2In3, LOW);
  digitalWrite(motor2In4, LOW);
  digitalWrite(motor3In1, LOW);
  digitalWrite(motor3In2, LOW);
  digitalWrite(motor4In3, LOW);
  digitalWrite(motor4In4, LOW);
}