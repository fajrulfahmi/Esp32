//----MOTOR---//

/*
FR : FRONT RIGHT 
FL : FRONT LEFT
BR : BACK RIGHT 
BL : BACK LEFT
M1 : MOTOR 1 dst
*/

#define pin_MOTOR_BL 25
#define pin_MOTOR_PWMBL 26
#define pin_MOTOR_BR 17
#define pin_MOTOR_PWMBR 16
#define pin_MOTOR_FL 32
#define pin_MOTOR_PWMFL 33
#define pin_MOTOR_FR 23
#define pin_MOTOR_PWMFR 22

#define pin_MOTOR_KICK 18

#define PWM_FREQUENCY 700
#define PWM_RESOLUTION 8
#define M1A_PWM_CHANNEL 0
#define M1B_PWM_CHANNEL 1
#define M2A_PWM_CHANNEL 2
#define M2B_PWM_CHANNEL 3
#define M3A_PWM_CHANNEL 4
#define M3B_PWM_CHANNEL 5
#define M4A_PWM_CHANNEL 6
#define M4B_PWM_CHANNEL 7

#define potensio 4
//-----------//

void setup() {
  //motor
  ledcSetup(M1A_PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcSetup(M1B_PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcSetup(M2A_PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcSetup(M2B_PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcSetup(M3A_PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcSetup(M3B_PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcSetup(M4A_PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcSetup(M4B_PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);

  ledcAttachPin(pin_MOTOR_FL, M1A_PWM_CHANNEL);
  ledcAttachPin(pin_MOTOR_PWMFL, M1B_PWM_CHANNEL);
  ledcAttachPin(pin_MOTOR_BL, M2A_PWM_CHANNEL);
  ledcAttachPin(pin_MOTOR_PWMBL, M2B_PWM_CHANNEL);
  ledcAttachPin(pin_MOTOR_FR, M3A_PWM_CHANNEL);
  ledcAttachPin(pin_MOTOR_PWMFR, M3B_PWM_CHANNEL);
  ledcAttachPin(pin_MOTOR_BR, M4A_PWM_CHANNEL);
  ledcAttachPin(pin_MOTOR_PWMBR, M4B_PWM_CHANNEL);

  pinMode(potensio, INPUT);
  pinMode(pin_MOTOR_KICK, OUTPUT);
}

void loop() {
  tendang(1);
  // int v = analogRead(potensio);
  // int mv = map(v, 0, 4095, 0, 255);
  // setMotor(mv, mv, mv, mv);  //front
  // setMotor(-70, -70, -70, -70);   //back
  // setMotor(70, -70, -70, 70);     //move right
  // setMotor(-70, 70, 70, -70);     //move left
  // setMotor(70, 0, 0, 70);         //diagonal kanan depan
  // setMotor(0, 70, 70, 0);         //diagonal kiri depan
  // setMotor(0, -70, -70, 0);       //diagonal kanan belakang
  // setMotor(-70, 0, 0, -70);       //diagonal kiri belakang
  // setMotor(-70, -70, 70, 70);       //rotate left
  setMotor(70, 70, -70, -70);       //rotate right
}

//------------------FUNGSI MOTOR Penggerak---------------------//
void setMotor(int speedFL, int speedFR, int speedBL, int speedBR) {
  speedFR = constrain(speedFR, -255, 255);
  speedFL = constrain(speedFL, -255, 255);
  speedBR = constrain(speedBR, -255, 255);
  speedBL = constrain(speedBL, -255, 255);


  if (speedFR > 0) {
    int speedM1 = map(speedFR, 0, 255, 255, 0);
    ledcWrite(M1A_PWM_CHANNEL, speedM1);
    ledcWrite(M1B_PWM_CHANNEL, 255);
  } else {
    int speedM1 = map(speedFR, -255, 0, 0, 255);
    ledcWrite(M1A_PWM_CHANNEL, 255);
    ledcWrite(M1B_PWM_CHANNEL, speedM1);
  }

  if (speedFL > 0) {
    int speedM2 = map(speedFL, 0, 255, 255, 0);
    ledcWrite(M2A_PWM_CHANNEL, speedM2);
    ledcWrite(M2B_PWM_CHANNEL, 255);
  } else {
    int speedM2 = map(speedFL, -255, 0, 0, 255);
    ledcWrite(M2A_PWM_CHANNEL, 255);
    ledcWrite(M2B_PWM_CHANNEL, speedM2);
  }

  if (speedBR > 0) {
    int speedM3 = map(speedBR, 0, 255, 255, 0);
    ledcWrite(M3A_PWM_CHANNEL, speedM3);
    ledcWrite(M3B_PWM_CHANNEL, 255);
  } else {
    int speedM3 = map(speedBR, -255, 0, 0, 255);
    ledcWrite(M3A_PWM_CHANNEL, 255);
    ledcWrite(M3B_PWM_CHANNEL, speedM3);
  }

  if (speedBL > 0) {
    int speedM4 = map(speedBL, 0, 255, 255, 0);
    ledcWrite(M4A_PWM_CHANNEL, speedM4);
    ledcWrite(M4B_PWM_CHANNEL, 255);
  } else {
    int speedM4 = map(speedBL, -255, 0, 0, 255);
    ledcWrite(M4A_PWM_CHANNEL, 255);
    ledcWrite(M4B_PWM_CHANNEL, speedM4);
  }
}

void tendang(bool ya) {
  if (ya == 1) {
    digitalWrite(pin_MOTOR_KICK, HIGH);
  } else if (ya == 0) {
    digitalWrite(pin_MOTOR_KICK, LOW);
  }
}
