
//-----------------------REMOVE PAIR----------------------------------------------------------------------//
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include"esp_gap_bt_api.h"
#include "esp_err.h"

#include <PS4Controller.h>

#include <HardwareSerial.h>

//HardwareSerial SerialPort(2); // use UART2

//----MOTOR---//
#define pin_MOTOR_DIRR 18
#define pin_MOTOR_PWMR 19

#define pin_MOTOR_DIRL 16
#define pin_MOTOR_PWML 17
//
//#define pin_MOTOR_KICK1 18
//#define pin_MOTOR_KICK2 19

#define PWM_FREQUENCY   1000
#define PWM_RESOLUTION  8
#define M1A_PWM_CHANNEL 6
#define M1B_PWM_CHANNEL 7
#define M2A_PWM_CHANNEL 8
#define M2B_PWM_CHANNEL 9
//-----------//

#include <Servo.h>

#define servo_angkat 12
#define servo_capit 23

//SERVO
Servo servoA;
Servo servoC;

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

#define REMOVE_BONDED_DEVICES 1   // <- Set to 0 to view all bonded devices addresses, set to 1 to remove

#define PAIR_MAX_DEVICES 20
uint8_t pairedDeviceBtAddr[PAIR_MAX_DEVICES][6];
char bda_str[18];

bool initBluetooth()
{
  if (!btStart()) {
    Serial.println("Failed to initialize controller");
    return false;
  }

  if (esp_bluedroid_init() != ESP_OK) {
    Serial.println("Failed to initialize bluedroid");
    return false;
  }

  if (esp_bluedroid_enable() != ESP_OK) {
    Serial.println("Failed to enable bluedroid");
    return false;
  }
  return true;
}

char *bda2str(const uint8_t* bda, char *str, size_t size)
{
  if (bda == NULL || str == NULL || size < 18) {
    return NULL;
  }
  sprintf(str, "%02x:%02x:%02x:%02x:%02x:%02x",
          bda[0], bda[1], bda[2], bda[3], bda[4], bda[5]);
  return str;
}
//-----------------------REMOVE PAIR----------------------------------------------------------------------//

//#define RXp2 16
//#define TXp2 17


void setup() {
  Serial.begin(115200);
  //  SerialPort.begin(9600, SERIAL_8N1, RXp2, TXp2);

  //-----------------------REMOVE PAIR----------------------------------------------------------------------//
  initBluetooth();
  Serial.print("ESP32 bluetooth address: "); Serial.println(bda2str(esp_bt_dev_get_address(), bda_str, 18));
  // Get the numbers of bonded/paired devices in the BT module
  int count = esp_bt_gap_get_bond_device_num();
  if (!count) {
    Serial.println("No bonded device found.");
  } else {
    Serial.print("Bonded device count: "); Serial.println(count);
    if (PAIR_MAX_DEVICES < count) {
      count = PAIR_MAX_DEVICES;
      Serial.print("Reset bonded device count: "); Serial.println(count);
    }
    esp_err_t tError =  esp_bt_gap_get_bond_device_list(&count, pairedDeviceBtAddr);
    if (ESP_OK == tError) {
      for (int i = 0; i < count; i++) {
        Serial.print("Found bonded device # "); Serial.print(i); Serial.print(" -> ");
        Serial.println(bda2str(pairedDeviceBtAddr[i], bda_str, 18));
        if (REMOVE_BONDED_DEVICES) {
          esp_err_t tError = esp_bt_gap_remove_bond_device(pairedDeviceBtAddr[i]);
          if (ESP_OK == tError) {
            Serial.print("Removed bonded device # ");
          } else {
            Serial.print("Failed to remove bonded device # ");
          }
          Serial.println(i);
        }
      }
    }
  }
  //-----------------------REMOVE PAIR----------------------------------------------------------------------//

  //motor
  ledcSetup(M1A_PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcSetup(M1B_PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcSetup(M2A_PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
  ledcSetup(M2B_PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);

  ledcAttachPin(pin_MOTOR_DIRL, M1A_PWM_CHANNEL);
  ledcAttachPin(pin_MOTOR_PWML, M1B_PWM_CHANNEL);
  ledcAttachPin(pin_MOTOR_DIRR, M2A_PWM_CHANNEL);
  ledcAttachPin(pin_MOTOR_PWMR, M2B_PWM_CHANNEL);

//  pinMode(pin_MOTOR_KICK1, OUTPUT);
//  pinMode(pin_MOTOR_KICK2, OUTPUT);

//servo
  servoA.attach(servo_angkat);
  servoC.attach(servo_capit);
  
  PS4.begin("c0:49:ef:f8:f1:2a");
  Serial.println("Ready.");

}
bool isHoldRight = false,
     isHoldDown = false,
     isHoldUp = false,
     isHoldLeft = false,
     isHoldSquare = false,
     isHoldCircle = false,
     isHoldCross = false,
     isHoldTriangle = false,
     isHoldL1 = false,
     isHoldR1 = false,
     isHoldL2 = false,
     isHoldR2 = false;

unsigned long lastTimeRight,
         lastTimeDown,
         lastTimeUp,
         lastTimeLeft,
         lastTimeSquare,
         lastTimeCircle,
         lastTimeCross,
         lastTimeTriangle,
         lastTimeL1,
         lastTimeR1,
         lastTimeL2,
         lastTimeR2;

const long timeout = 40;

void loop() {
  int speedx = 100;

  if (PS4.isConnected()) {
    if (PS4.Right()) {
      Serial.println("Right Button");
      //      SerialPort.print('r');
      setMotor(speedx-15, -speedx+15);
      lastTimeRight = millis();
      isHoldRight = true;
    }

    if (PS4.Down()) {
      Serial.println("Down Button");
      //      SerialPort.print('d');
      setMotor(-speedx, -speedx);
      lastTimeDown = millis();
      isHoldDown = true;
    }
    if (PS4.Up()) {
      Serial.println("Up Button");
      //      SerialPort.print('u');
      setMotor(speedx, speedx);
      lastTimeUp = millis();
      isHoldUp = true;
    }
    if (PS4.Left()) {
      Serial.println("Left Button");
      //      SerialPort.print('l');
      setMotor(-speedx+15, speedx-15);
      lastTimeLeft = millis();
      isHoldLeft = true;
    }

    if (PS4.Square()) {
      Serial.println("Square Button");
      //      SerialPort.print('s');
      setMotor(-speedx+15, speedx-15);
      lastTimeSquare = millis();
      isHoldSquare = true;
    }
    if (PS4.Circle()) {
      Serial.println("Circle Button");
      //      SerialPort.print('c');
      setMotor(speedx-15, -speedx+15);
      lastTimeCircle = millis();
      isHoldCircle = true;
    }
    if (PS4.Cross()) {
      Serial.println("Cross Button");
      //      SerialPort.print('x');
      lastTimeCross = millis();
      isHoldCross = true;
    }
    if (PS4.Triangle()) {
      Serial.println("Triangle Button");
      //      SerialPort.print('t');
      lastTimeTriangle = millis();
      isHoldTriangle = true;
    }
    if (PS4.L1()) {
      Serial.println("L1 Button");
      //      SerialPort.print('o');
      buka();
      lastTimeL1 = millis();
      isHoldL1 = true;
    }
    if (PS4.R1()) {
      Serial.println("R1 Button");
      naik();
      //      SerialPort.print('p');
      lastTimeR1 = millis();
      isHoldR1 = true;
    }
    if (PS4.L2()) {
      Serial.println("L2 Button");
      //      SerialPort.print('o');
      tutup();
      lastTimeL1 = millis();
      isHoldL1 = true;
    }
    if (PS4.R2()) {
      Serial.println("R1 Button");
      turun();
      //      SerialPort.print('p');
      lastTimeR1 = millis();
      isHoldR1 = true;
    }

    //RELEASE CNTRL WAHYUUUUUU--------------------------------------------

    if (isHoldRight) {  //Check Timeout Key Hold
      unsigned long nowTime = millis(); //Check Actual Time
      if (nowTime - lastTimeRight >= timeout) { //Check Timeout
        isHoldRight = false;
        //        SerialPort.print('R');
        setMotor(0, 0);
        Serial.println("Right - RELEASE");
      }
    }

    if (isHoldDown) {  //Check Timeout Key Hold
      unsigned long nowTime = millis(); //Check Actual Time
      if (nowTime - lastTimeDown >= timeout) { //Check Timeout
        isHoldDown = false;
        //        SerialPort.print('D');
        setMotor(0, 0);
        Serial.println("Down - RELEASE");
      }
    }

    if (isHoldUp) {  //Check Timeout Key Hold
      unsigned long nowTime = millis(); //Check Actual Time
      if (nowTime - lastTimeUp >= timeout) { //Check Timeout
        isHoldUp = false;
        //        SerialPort.print('U');
        setMotor(0, 0);
        Serial.println("Up - RELEASE");
      }
    }

    if (isHoldLeft) {  //Check Timeout Key Hold
      unsigned long nowTime = millis(); //Check Actual Time
      if (nowTime - lastTimeLeft >= timeout) { //Check Timeout
        isHoldLeft = false;
        //        SerialPort.print('L');
        setMotor(0, 0);
        Serial.println("Left - RELEASE");
      }
    }

    if (isHoldSquare) {  //Check Timeout Key Hold
      unsigned long nowTime = millis(); //Check Actual Time
      if (nowTime - lastTimeSquare >= timeout) { //Check Timeout
        isHoldSquare = false;
        //        SerialPort.print('S');
        setMotor(0, 0);
        Serial.println("Square - RELEASE");
      }
    }

    if (isHoldCircle) {  //Check Timeout Key Hold
      unsigned long nowTime = millis(); //Check Actual Time
      if (nowTime - lastTimeCircle >= timeout) { //Check Timeout
        isHoldCircle = false;
        //        SerialPort.print('C');
        setMotor(0, 0);
        Serial.println("Circle - RELEASE");
      }
    }

    if (isHoldCross) {  //Check Timeout Key Hold
      unsigned long nowTime = millis(); //Check Actual Time
      if (nowTime - lastTimeCross >= timeout) { //Check Timeout
        isHoldCross = false;
        //        SerialPort.print('X');
        //setMotor(0, 0);
        Serial.println("Cross - RELEASE");
      }
    }

    if (isHoldTriangle) {  //Check Timeout Key Hold
      unsigned long nowTime = millis(); //Check Actual Time
      if (nowTime - lastTimeTriangle >= timeout) { //Check Timeout
        isHoldTriangle = false;
        //        SerialPort.print('T');
        Serial.println("Triangle - RELEASE");
      }
    }

    if (isHoldL1) {  //Check Timeout Key Hold
      unsigned long nowTime = millis(); //Check Actual Time
      if (nowTime - lastTimeL1 >= timeout) { //Check Timeout
        isHoldL1 = false;
        //        SerialPort.print('O');
        Serial.println("L1 - RELEASE");
      }
    }

    if (isHoldR1) {  //Check Timeout Key Hold
      unsigned long nowTime = millis(); //Check Actual Time
      if (nowTime - lastTimeR1 >= timeout) { //Check Timeout
        isHoldR1 = false;
        //        SerialPort.print('P');
//        tendang(0);
        Serial.println("R1 - RELEASE");
      }
    }

    if (isHoldL2) {  //Check Timeout Key Hold
      unsigned long nowTime = millis(); //Check Actual Time
      if (nowTime - lastTimeL2 >= timeout) { //Check Timeout
        isHoldL2 = false;
        //        SerialPort.print('O');
        Serial.println("L2 - RELEASE");
      }
    }

    if (isHoldR2) {  //Check Timeout Key Hold
      unsigned long nowTime = millis(); //Check Actual Time
      if (nowTime - lastTimeR2 >= timeout) { //Check Timeout
        isHoldR2 = false;
        //        SerialPort.print('P');
//        tendang(0);
        Serial.println("R2 - RELEASE");
      }
    }

  }
}

void naik(){
  servoA.write(150);
}

void turun(){
  servoA.write(20);
}

void buka(){
  servoC.write(80);
}

void tutup(){
  servoC.write(140);
}
//void tendang(bool ya){
//  if (ya == 1){
//    digitalWrite(pin_MOTOR_KICK1, HIGH);
//  }else if (ya == 0){
//    digitalWrite(pin_MOTOR_KICK1, LOW);
//  }
//}
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
