#include "car.h"

// default constructor of car
CAR::CAR() {

}

// initilize CAR
void CAR::init(Motor motor_left, Motor motor_right) {
    this->motor_left = motor_left;
    this->motor_right = motor_right;
    this->motor_left.init();
    this->motor_right.init();
}

// stop car
void CAR::stop() {
  this->motor_left.stop();
  this->motor_right.stop();
}

// move forword
void CAR::fwd() {
  this->motor_left.fwd(speed);
  this->motor_right.fwd(speed);
}

// move forword with a  speed given
void CAR::fwd(int s) {
  carSpeed(s);
  fwd();
}

// move backword
void CAR::bkwd() {
  this->motor_left.bkwd(speed);
  this->motor_right.bkwd(speed);
}

// move backword with a speed given
void CAR::bkwd(int s) {
  carSpeed(s);
  bkwd();
}

// turn car right
void CAR::turnRight() {
  this->motor_left.fwd(rotate_speed);
  this->motor_right.bkwd(rotate_speed);
}

// turn car right with a speed given
void CAR::turnRight(int s) {
  carRotationSpeed(s);
  turnRight();
}

// tunt car left
void CAR::turnLeft() {
  this->motor_left.bkwd(rotate_speed);
  this->motor_right.fwd(rotate_speed);
}

// turn the car left with a speed given
void CAR::turnLeft(int s) {
  carRotationSpeed(s);
  turnLeft();
}

// move car forword while turning right
void CAR::moveRight_fwd(int cs, int s) {
  int tmp = cs - s;
  if (tmp < 0) {
    tmp = 0;
  }

  this->motor_left.fwd(cs);
  this->motor_right.fwd(tmp);
}


// move car forword while turning left
void CAR::moveLeft_fwd(int cs, int s) {
  int tmp = cs - s;
  if (tmp < 0) {
    tmp = 0;
  }

  this->motor_left.fwd(tmp);
  this->motor_right.fwd(cs);
}

// set the speed of the car
void CAR::carSpeed(int s) {
  if(s > 255)
    s = 255;
  else if(s < 0)
    s = 0;
  this->speed = s;
}

// set the rotation speed
void CAR::carRotationSpeed(int s) {
  if(s > 255)
    s = 255;
  else if(s < 0)
    s = 0;
  this->rotate_speed = s;
}
