#include "motor.h"

class CAR {
private:
  int speed = 150;
  int rotate_speed = 150;
  Motor motor_left, motor_right;
public:
  CAR();
  void init(Motor, Motor);
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
