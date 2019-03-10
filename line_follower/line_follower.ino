#include "car.h"
#include "sensor.h"

// comment if out if the line is not black
#define BLACK_LINE

// create a car object
CAR car;  // 0,1; 2,3, pwm 6; 5
SENSOR sensor(A0, A1, A2, A3, A4, A5, 13, 12);  // create a IR sensor class with sensor input pin from left to right
int pid;  // pid variable
float pid_p, pid_i, pid_d;  // proportional intregal and derevative variable
float pid_pc, pid_ic, pid_dc; // pid constants
int error, prev_error;  // error variables
int *sensor_ip; // to store the sensor sensor data

void setup() {

  car.init(Motor(3,2,5), Motor(1,0,6)); // initilize the motor with wheel
  sensor.init();    // initilize the IR sensor

  pid_pc = 1.0f;    // proportional constant
  pid_ic = 0;       // intregal constant
  pid_dc = 0.5f;    // derevative constant
  error = prev_error = 0;   // set initial error zero

}


void loop() {

  error = 0;      // set error = 0  for every loop
  sensor_ip = sensor.getInput();    // get data from the ir sensor

  // read data from left 4 sensors
  for (int i = 0; i < 4; i++) {
    error = sensor_ip[i] * (i - 4);   // generate -ve error
    // get max -ve error and break
    if (error != 0)
      break;
  }

  // read data from right 4 sensors
  for (int i = 7; i > 3; i--) {
    int _tmp = sensor_ip[i] * (i - 3);   // generate +ve error
    // get max +ve error and break
    if (_tmp != 0) {
      error += _tmp;
      break;
    }
  }

  /****************   calculate pid   ***********************/
  pid_p = pid_pc * error;   // calculate proportional error
  pid_d = pid_dc * (error - prev_error);  // calculate deravative error
  pid = (int) (pid_p + pid_i + pid_d);    // calculate pid value
  prev_error = error;   // set error = previous error to use in next iteration
  pid = map(abs(pid), 0, 255, 150, 255);  // map the pid value to the analog output value to drive motor

  if (error < 0) {
    car.moveLeft_fwd(255, pid); // move left
  } else if (error > 0) {
    car.moveRight_fwd(255, pid);  // move right
  } else {
    car.fwd(255);   // move forword
  }

  delay(10);    // delay to derevative value work properly

}
