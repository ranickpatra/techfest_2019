#include "car.h"
#include "sensor.h"


#define BLACK_LINE

CAR car;  // 0,1,2,3, pwm 6,5
SENSOR sensor(A0, A1, A2, A3, A4, A5, 13, 12);
int pid;
float pid_p, pid_i, pid_d;
float pid_pc, pid_ic, pid_dc;
int error, prev_error;
int *sensor_ip;

void setup() {

  car.init(Motor(3,2,5), Motor(1,0,6));
  sensor.init();

  pid_pc = 1.0f;
  pid_ic = 0;
  pid_dc = 0.5f;
  error = prev_error = 0;

}


void loop() {

  error = 0;
  sensor_ip = sensor.getInput();
  for (int i = 0; i < 4; i++) {
    error = sensor_ip[i] * (i - 4);
    if (error != 0)
      break;
  }

  for (int i = 7; i > 3; i--) {
    int _tmp = sensor_ip[i] * (i - 3);
    if (_tmp != 0) {
      error += _tmp;
      break;
    }
  }

  pid_p = pid_pc * error;
  pid_d = pid_dc * (error - prev_error);
  pid = (int) (pid_p + pid_i + pid_d);
  prev_error = error;
  pid = map(abs(pid), 0, 255, 150, 255);

  if (error < 0) {
    car.moveLeft_fwd(255, pid);
  } else if (error > 0) {
    car.moveRight_fwd(255, pid);
  } else {
    car.fwd(255);
  }

  delay(10);

}
