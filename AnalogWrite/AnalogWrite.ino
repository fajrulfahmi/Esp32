#include <analogWrite.h>

#define ENA 27
#define in1 14
//#define in2 27

int vibState = LOW;
unsigned long previousMillis = 0; 
long OnTime = 3000; 
long OffTime = 10000;  

void setup() {
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);  
  pinMode(in1, OUTPUT);  
//  pinMode(in2, OUTPUT);      
}

void loop(){
  analogWrite(ENA, 255);
  
  unsigned long currentMillis = millis();
 
  if((vibState == HIGH) && (currentMillis - previousMillis >= OnTime)){
    vibState = LOW; 
    previousMillis = currentMillis;
    digitalWrite(in1, vibState);
    Serial.println("LED MATI");
  }
  else if ((vibState == LOW) && (currentMillis - previousMillis >= OffTime)){
    vibState = HIGH;
    previousMillis = currentMillis;
    digitalWrite(in1, vibState);
    Serial.println("LED HIDUP");
  }
}
