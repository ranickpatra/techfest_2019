#include "sensor.h"

// set ping left to right
SENSOR::SENSOR(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7) {
  pins[0] = p0;
  pins[1] = p1;
  pins[2] = p2;
  pins[3] = p3;
  pins[4] = p4;
  pins[5] = p5;
  pins[6] = p6;
  pins[7] = p7;
}


void SENSOR::init() {
  for (int i = 0; i < 8;  i++) {
    pinMode(pins[i], INPUT);
    inputArray[i] = 0;
  }
}


int* SENSOR::getInput() {

  for (int i = 0; i < 8; i++)
    inputArray[i] = digitalRead(pins[i]);

  #ifdef BLACK_LINE
    for (int i = 0; i < 8; i++)
      inputArray[i] = !inputArray[i];
  #else
    // leave blank
  #endif

  return inputArray;
}
