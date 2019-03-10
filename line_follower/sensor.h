#include <Arduino.h>

//#define BLACK_LINE
//#define WHITE_LINE

class SENSOR {
private:
  int pins[8];
  int inputArray[8];

public:
  SENSOR(int,int,int,int,int,int,int,int);
  void init();
  int* getInput();

};
