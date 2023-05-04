#include <AFMotor.h>

const int LINE_SENSOR_LEFT = A0;
const int LINE_SENSOR_MID = A1;
const int LINE_SENSOR_RIGHT = A2;
const int WALL_SENSOR_LEFT = A3;
const int WALL_SENSOR_RIGHT = A4;

AF_DCMotor motor_left(3);
AF_DCMotor motor_right(4);
void setup() {
  // put your setup code here, to run once:
  motor_left.setSpeed(208);
  motor_right.setSpeed(208);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
