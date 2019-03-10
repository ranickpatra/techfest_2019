#include "motor.h"

Motor::Motor() {

}

// constructor of motor
Motor::Motor(int p1, int p2, int en) {
  this->pin1 = p1;
  this->pin2 = p2;
  this->enable = en;
}


// initilize the motor
void Motor::init() {
  // set the outpins
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(enable, OUTPUT);
  // set all the pins low
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  // set motor enable pin 0 pwm
  analogWrite(enable, 0);
  speed = 0;
}

// start motor
void Motor::start() {
  analogWrite(enable, speed);
}

// stop motor
void Motor::stop() {
  analogWrite(enable, 0);
}

// rotate fwd direction
void Motor::fwd() {
  start();
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
}

// rotate fwd directon with a speed
void Motor::fwd(int s) {
  MSpeed(s);
  fwd();
}

// motor rotate backword direction
void Motor::bkwd() {
  start();
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
}

// motor rotate backword direction with speed
void Motor::bkwd(int s) {
  MSpeed(s);
  bkwd();
}

// set motor speed
void Motor::MSpeed(int s) {
  if (s > 255)
    s = 255;
  else if (s < 0)
    s = 0;
  this->speed = s;
}
