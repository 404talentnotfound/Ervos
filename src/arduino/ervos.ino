#include <Servo.h>
#include <Wire.h>

// define servo pins
#define LeftServoPin 9
#define MiddleServoPin 10
#define RightServoPin 11

// create servo objects
Servo left_servo;
Servo middle_servo;
Servo right_servo;

void setup() {
  // initialise serial communication
  Serial.begin(115200);

  // attach servos
  left_servo.attach(LeftServoPin);
  middle_servo.attach(MiddleServoPin);
  right_servo.attach(RightServoPin);

  // move servos in place
  left_servo.write(120);
  middle_servo.write(120);
  right_servo.write(120);
}

void loop() {
  // check if serial port can be read
  if (Serial.available()) {
    // read a single byte from serial
    int incomingByte = Serial.read();

    // check what byte was sent
    switch (incomingByte) {
      case '0':
        left_servo.write(110);
        delay(20);
        break;
      case '1':
        left_servo.write(95);
        delay(20);
        break;

      case '2':
        middle_servo.write(105);
        delay(30);
        break;
      case '3':
        middle_servo.write(85);
        delay(30);
        break;

      case '4':
        right_servo.write(125);
        delay(20);
        break;
      case '5':
        right_servo.write(140);
        delay(20);
        break;

      // reset all servos to initial position
      case '6':
        left_servo.attach(LeftServoPin);
        middle_servo.attach(MiddleServoPin);
        right_servo.attach(RightServoPin);

        left_servo.write(110);
        middle_servo.write(105);
        right_servo.write(125);

        delay(35);
        
        break;
    }
  }
}

