#include <Servo.h>

const int sensorPanPin = A0;
const int sensorTiltPin = A1;
const int servoPanPin = 9;
const int servoTiltPin = 10;

int sensorPanValue = 0;
int sensorPanLastValue = 0;
int sensorTiltValue = 0;
int sensorTiltLastValue = 0;
Servo servoPan, servoTilt;

void setup() {
  // put your setup code here, to run once:
  servoPan.attach(servoPanPin);
  //servoTilt.attach(servoTiltPin);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorPanValue = analogRead(sensorPanPin);
  sensorTiltValue = analogRead(sensorTiltPin);
  sensorPanValue = map(sensorPanValue, 0, 1023, 0, 180);
  sensorTiltValue = map(sensorTiltValue, 0, 1023, 0, 180);
  servoPan.write(sensorPanValue);
  //servoTilt.write(sensorTiltValue);
  delay(10);
}
