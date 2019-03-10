#include "sensor.h"

// set ping left to right
SENSOR::SENSOR(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7) {
  // set pins of sensor
  pins[0] = p0;
  pins[1] = p1;
  pins[2] = p2;
  pins[3] = p3;
  pins[4] = p4;
  pins[5] = p5;
  pins[6] = p6;
  pins[7] = p7;
}

// initilize sensor
void SENSOR::init() {
  for (int i = 0; i < 8;  i++) {
    pinMode(pins[i], INPUT);    // set pins as input
    inputArray[i] = 0;          // initilize input array with 0
  }
}

// return the data from sensor array
int* SENSOR::getInput() {

  // read the sensors values
  for (int i = 0; i < 8; i++)
    inputArray[i] = digitalRead(pins[i]);

  // if the line is black then execute
  #ifdef BLACK_LINE
    for (int i = 0; i < 8; i++)
      inputArray[i] = !inputArray[i];   // not operation to invert the value
  #endif

  return inputArray;  // return sensor data
}
