#include <AFMotor.h>

const int LINE_SENSOR_LEFT = A0;
const int LINE_SENSOR_MID = A1;
const int LINE_SENSOR_RIGHT = A2;
const int WALL_SENSOR_LEFT = A3;
const int WALL_SENSOR_RIGHT = A4;

AF_DCMotor motor_left(3);
AF_DCMotor motor_right(4);

unsigned long leftWallTime = 0;
unsigned long rightWallTime = 0;
const unsigned long PULSE_DURATION = 500;

void setup() {
  // put your setup code here, to run once:
  pinMode(WALL_SENSOR_LEFT, INPUT);
  pinMode(WALL_SENSOR_RIGHT, INPUT);

  motor_left.setSpeed(208);
  motor_right.setSpeed(208);        
  motor_left.run(FORWARD);
  motor_right.run(FORWARD);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned int currentTime = millis();
  bool leftWallSensor = digitalRead(WALL_SENSOR_LEFT);
  bool rightWallSensor = digitalRead(WALL_SENSOR_RIGHT);

  if(LOW == leftWallSensor) { // active low
    leftWallTime = currentTime;
  }

  if(LOW == rightWallSensor) { // active low
    rightWallTime = currentTime;
  }

  if (currentTime - leftWallTime < PULSE_DURATION) {
      motor_right.run(BACKWARD);
  } else {
      motor_right.run(FORWARD);
  }

  if (currentTime - rightWallTime < PULSE_DURATION) {
      motor_left.run(BACKWARD);
  } else {
      motor_left.run(FORWARD);
  }
}
