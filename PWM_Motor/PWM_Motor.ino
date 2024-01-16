//----MOTOR---//
#define pin_MOTOR_DIRR 22
#define pin_MOTOR_PWMR 23

#define pin_MOTOR_DIRL 32
#define pin_MOTOR_PWML 33

#define PWM_FREQUENCY   1000
#define PWM_RESOLUTION  8
#define M1A_PWM_CHANNEL 6
#define M1B_PWM_CHANNEL 7
#define M2A_PWM_CHANNEL 8
#define M2B_PWM_CHANNEL 9
//-----------//

void setup() {
  //motor
  ledcSetup(M1A_PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcSetup(M1B_PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcSetup(M2A_PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcSetup(M2B_PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);

  ledcAttachPin(pin_MOTOR_DIRL, M1A_PWM_CHANNEL);
  ledcAttachPin(pin_MOTOR_PWML, M1B_PWM_CHANNEL);
  ledcAttachPin(pin_MOTOR_DIRR, M2A_PWM_CHANNEL);
  ledcAttachPin(pin_MOTOR_PWMR, M2B_PWM_CHANNEL);
}

void loop() { 
  setMotor(100, 100); 
}

//------------------FUNGSI MOTOR Penggerak---------------------//
void setMotor(int speedLeft, int speedRight)
{
  speedLeft = constrain(speedLeft, -255, 255);
  speedRight = constrain(speedRight, -255, 255);

  if (speedLeft > 0) {
    int speedL = map(speedLeft, 0, 255, 255, 0);  
    ledcWrite(M1A_PWM_CHANNEL, speedL);
    ledcWrite(M1B_PWM_CHANNEL, 255);
  }
  else {
    int speedL = map(speedLeft, -255, 0, 0, 255);
    ledcWrite(M1A_PWM_CHANNEL, 255);
    ledcWrite(M1B_PWM_CHANNEL, speedL);
  }

  if (speedRight > 0) {
    int speedR = map(speedRight, 0, 255, 255, 0);
    ledcWrite(M2A_PWM_CHANNEL, speedR);
    ledcWrite(M2B_PWM_CHANNEL, 255);
  }
  else {
    int speedR = map(speedRight, -255, 0, 0, 255);
    ledcWrite(M2A_PWM_CHANNEL, 255);
    ledcWrite(M2B_PWM_CHANNEL, speedR);
  }
}
