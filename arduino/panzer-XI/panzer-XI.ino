#include <AFMotor.h>

const int LINE_SENSOR_LEFT = A0;
const int LINE_SENSOR_RIGHT = A1;
const int WALL_SENSOR_LEFT_UP = A2;
const int WALL_SENSOR_LEFT_DN = A3;
const int WALL_SENSOR_RIGHT_DN = A4;
const int WALL_SENSOR_RIGHT_UP = A5;

AF_DCMotor motor_left(3);
AF_DCMotor motor_right(4);

unsigned long leftWallTime = 0;
unsigned long rightWallTime = 0;
const unsigned long PULSE_DURATION = 60;

void setup() {
  // put your setup code here, to run once:
  pinMode(WALL_SENSOR_LEFT_UP, INPUT);
  pinMode(WALL_SENSOR_LEFT_DN, INPUT);
  pinMode(WALL_SENSOR_RIGHT_UP, INPUT);
  pinMode(WALL_SENSOR_RIGHT_DN, INPUT);

  motor_left.setSpeed(120);
  motor_right.setSpeed(120);
  motor_left.run(FORWARD);
  motor_right.run(FORWARD);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned int currentTime = millis();
  bool leftWallSensor = digitalRead(WALL_SENSOR_LEFT_UP) && digitalRead(WALL_SENSOR_LEFT_DN);
  bool rightWallSensor = digitalRead(WALL_SENSOR_RIGHT_UP) && digitalRead(WALL_SENSOR_RIGHT_DN);

  if (LOW == leftWallSensor) { // active low
    leftWallTime = currentTime;
  }

  if (LOW == rightWallSensor) { // active low
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
