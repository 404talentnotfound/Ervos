int solenoidPin = 2;
bool currentState = false;

void setup() {
  Serial.begin(1000000);
  pinMode(solenoidPin, OUTPUT);
}

void loop() {
  // Flush any stray data before reading new data
  while (Serial.available() > 1) {
    Serial.read();  // Clear buffer of unintended data
  }

  if (Serial.available() > 0) {
    char incomingByte = Serial.read();

    switch (incomingByte) {
      case '1':
        digitalWrite(solenoidPin, !currentState);
        currentState = !currentState;
        break;
      case '2':
        digitalWrite(solenoidPin, !currentState);
        currentState = !currentState;
        delayMicroseconds(3000);
        digitalWrite(solenoidPin, !currentState);
        currentState = !currentState;
        break;
      case '6':
        currentState = false;
        digitalWrite(solenoidPin, currentState);
        break;
    }
  }
}
