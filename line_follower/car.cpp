#include "car.h"


CAR::CAR() {

}

void CAR::init(Motor motor_left, Motor motor_right) {
    this->motor_left = motor_left;
    this->motor_right = motor_right;
    this->motor_left.init();
    this->motor_right.init();
}

void CAR::stop() {
  this->motor_left.stop();
  this->motor_right.stop();
}

void CAR::fwd() {
  this->motor_left.fwd(speed);
  this->motor_right.fwd(speed);
}

void CAR::fwd(int s) {
  carSpeed(s);
  fwd();
}

void CAR::bkwd() {
  this->motor_left.bkwd(speed);
  this->motor_right.bkwd(speed);
}

void CAR::bkwd(int s) {
  carSpeed(s);
  bkwd();
}

void CAR::turnRight() {
  this->motor_left.fwd(rotate_speed);
  this->motor_right.bkwd(rotate_speed);
}

void CAR::turnRight(int s) {
  carRotationSpeed(s);
  turnRight();
}

void CAR::turnLeft() {
  this->motor_left.bkwd(rotate_speed);
  this->motor_right.fwd(rotate_speed);
}

void CAR::turnLeft(int s) {
  carRotationSpeed(s);
  turnLeft();
}

void CAR::moveRight_fwd(int cs, int s) {
  int tmp = cs - s;
  if (tmp < 0) {
    tmp = 0;
  }

  this->motor_left.fwd(cs);
  this->motor_right.fwd(tmp);
}

void CAR::moveLeft_fwd(int cs, int s) {
  int tmp = cs - s;
  if (tmp < 0) {
    tmp = 0;
  }

  this->motor_left.fwd(tmp);
  this->motor_right.fwd(cs);
}

void CAR::carSpeed(int s) {
  if(s > 255)
    s = 255;
  else if(s < 0)
    s = 0;
  this->speed = s;
}

void CAR::carRotationSpeed(int s) {
  if(s > 255)
    s = 255;
  else if(s < 0)
    s = 0;
  this->rotate_speed = s;
}
