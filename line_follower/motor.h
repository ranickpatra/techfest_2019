#include <Arduino.h>

class Motor {
  private:
    int pin1, pin2;
    int enable;
    int speed;
  public:
    Motor();
    Motor(int p1, int p2, int en);
    void init();
    void start();
    void stop();
    void fwd();
    void fwd(int);
    void bkwd();
    void bkwd(int);
    void MSpeed(int);
};
