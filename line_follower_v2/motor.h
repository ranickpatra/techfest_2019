#include <Arduino.h>

class Motor {
  private:
    int pin1, pin2;   // 2 pins of motor
    int enable;       // enable pin to controll motor speed
    int speed;        // motor speed
  public:
    Motor();    // default constructor
    Motor(int p1, int p2, int en);    // motor constructor
    void init();
    void start();
    void stop();
    void fwd();
    void fwd(int);
    void bkwd();
    void bkwd(int);
    void MSpeed(int);
};
