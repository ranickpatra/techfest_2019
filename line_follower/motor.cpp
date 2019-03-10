#include "motor.h"

Motor::Motor() {
  
}

Motor::Motor(int p1, int p2, int en) {
  this->pin1 = p1;
  this->pin2 = p2;
  this->enable = en;
}

void Motor::init() {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(enable, OUTPUT);
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  analogWrite(enable, 0);
  speed = 0;
}

void Motor::start() {
  analogWrite(enable, speed);
}

void Motor::stop() {
  analogWrite(enable, 0);
}

void Motor::fwd() {
  start();
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
}

void Motor::fwd(int s) {
  MSpeed(s);
  fwd();
}

void Motor::bkwd() {
  start();
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
}

void Motor::bkwd(int s) {
  MSpeed(s);
  bkwd();
}

void Motor::MSpeed(int s) {
  if (s > 255)
    s = 255;
  else if (s < 0)
    s = 0;
  this->speed = s;
}
