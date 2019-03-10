#include <Arduino.h>

//#define BLACK_LINE
//#define WHITE_LINE

class SENSOR {
private:
  int pins[8];    // sensor pins array
  int inputArray[8];  // input array

public:
  SENSOR(int,int,int,int,int,int,int,int);  // constructor
  void init();
  int* getInput();

};
