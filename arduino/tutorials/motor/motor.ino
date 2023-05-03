#include <AFMotor.h>

AF_DCMotor motor_left(3);
AF_DCMotor motor_right(4);

void setup() {
  // put your setup code here, to run once:
  motor_left.setSpeed(208);
  motor_right.setSpeed(208);
  motor_left.run(FORWARD);
  motor_right.run(FORWARD);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*motor_left.run(FORWARD);
  delay(2000);
  motor_left.run(RELEASE);
  delay(1000);
  motor_right.run(FORWARD);
  delay(2000);
  motor_right.run(RELEASE);
  delay(1000);*/
}
