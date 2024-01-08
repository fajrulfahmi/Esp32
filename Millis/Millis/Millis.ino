unsigned long interval = 1000;     // the time we need to wait
unsigned long previousMillis = 0;  // millis() returns an unsigned long.

bool ledState = false;  // state variable for the LED

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, ledState);
}

void loop() {
  unsigned long currentMillis = millis();  // grab current time

  // check if "interval" time has passed (1000 milliseconds)
  if ((unsigned long)(currentMillis - previousMillis) >= interval) {
    ledState = !ledState;        // "toggles" the state
    digitalWrite(13, ledState);  // sets the LED based on ledState
    // save the "current" time
    previousMillis = millis();
  }
}
