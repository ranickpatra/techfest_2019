#include "motor.h"

class CAR {
private:
  int speed = 150;    // set a default car speed
  int rotate_speed = 150; // set a default car rotation speed
  Motor motor_left, motor_right;    // motor variable
public:
  
  CAR();  // constructor of car
  void init(Motor, Motor);  // to initilize the car
  void stop();
  void fwd();
  void fwd(int);
  void bkwd();
  void bkwd(int);
  void turnRight();
  void turnRight(int);
  void turnLeft();
  void turnLeft(int);
  void moveRight_fwd(int, int);
  void moveLeft_fwd(int, int);
  void carSpeed(int);
  void carRotationSpeed(int);
};
