#include "car.h"
#include "sensor.h"

// comment if out if the line is not WHITE
//#define WHITE_LINE

#define BLACKLINE
#define FORWORD 1
#define RIGHT90 2
#define LEFT90 3
#define RIGHT_TURN 4
#define LEFT_TURN 5
#define ROTATE_LEFT 6
#define ROTATE_RIGHT 7
#define ACUTE_LEFT 8
#define ACUTE_RIGHT 9
#define ACUTE_NONE 10
#define SPEED_90_DEG 150

int lst_action = FORWORD;


// create a car object
CAR car;  // 0,1; 2,3, pwm 6; 5
SENSOR sensor(A0, A1, A2, A3, A4, A5, 13, 12);  // create a IR sensor class with sensor input pin from left to right
int *sensor_ip; // to store the sensor sensor data

//int speed_factor[] = {0, 50, 150, 255};
int speed_factor[] = {255, 150, 50, 0};
float multiplication_factor = 0;
int max_speed = 200;
uint8_t acute_detect;
int rotatedelay = 180;


bool acute_detect_once;
bool obstrackel_detected;

void setup() {

  car.init(Motor(3,2,5), Motor(1,0,6)); // initilize the motor with wheel
  sensor.init();    // initilize the IR sensor
  multiplication_factor = ((float) max_speed) / 255;
  car.fwd(max_speed);
  delay(200);

}


void loop() {

  sensor_ip = sensor.getInput();    // get data from the ir sensor


  uint8_t array_sensor = 0;

  for (int i = 0; i < 8; i++) {
    array_sensor |= sensor_ip[i] << (7-i);
  }

  switch (array_sensor) {
    case B0000000: // no line detected. Continue previous action.
      no_lineDetected();
      break;

    case B10000000: // turn sharply to the left.
      car.moveLeft_fwd(max_speed, (int)(speed_factor[0]*multiplication_factor));
      lst_action = LEFT_TURN;
      break;
    case B01000000: // turn to the left.
      car.moveLeft_fwd(max_speed, (int)(speed_factor[1]*multiplication_factor));
      lst_action = LEFT_TURN;
      break;
    case B00100000: // turn to the left.
      car.moveLeft_fwd(max_speed, (int)(speed_factor[2]*multiplication_factor));
      lst_action = LEFT_TURN;
      break;
    case B00010000: // turn to the left.
      car.moveLeft_fwd(max_speed, (int)(speed_factor[3]*multiplication_factor));
      lst_action = LEFT_TURN;
      break;
    case B00001000: // turn to the right.
      car.moveRight_fwd(max_speed, (int)(speed_factor[3]*multiplication_factor));
      lst_action = RIGHT_TURN;
      break;
    case B00000100: // turn to the right.
      car.moveRight_fwd(max_speed, (int)(speed_factor[2]*multiplication_factor));
      lst_action = RIGHT_TURN;
      break;
    case B00000010: // turn to the right.
      car.moveRight_fwd(max_speed, (int)(speed_factor[1]*multiplication_factor));
      lst_action = RIGHT_TURN;
      break;
    case B00000001: // turn sharply to the right.
      car.moveRight_fwd(max_speed, (int)(speed_factor[0]*multiplication_factor));
      lst_action = RIGHT_TURN;
      break;

    case B11000000: // turn left
      car.moveLeft_fwd(max_speed, (int)(speed_factor[0]*multiplication_factor));
      lst_action = LEFT_TURN;
      break;
    case B01100000: // turn left
      car.moveLeft_fwd(max_speed, (int)(speed_factor[1]*multiplication_factor));
      lst_action = LEFT_TURN;
      break;
    case B00110000: // turn left
      car.moveLeft_fwd(max_speed, (int)(speed_factor[3]*multiplication_factor));
      lst_action = LEFT_TURN;
      break;
    case B00011000: // move straight forward at full speed
      car.fwd(max_speed);
      lst_action = FORWORD;
      break;
    case B00001100: // turn right
      car.moveRight_fwd(max_speed, (int)(speed_factor[3]*multiplication_factor));
      lst_action = RIGHT_TURN;
      break;
    case B00000110: // turn right
      car.moveRight_fwd(max_speed, (int)(speed_factor[1]*multiplication_factor));
      lst_action = RIGHT_TURN;
      break;
    case B00000011: // turn right
      car.moveRight_fwd(max_speed, (int)(speed_factor[0]*multiplication_factor));
      lst_action = RIGHT_TURN;
      break;

    case B11100000: // turn left
      car.turnLeft(SPEED_90_DEG);
      lst_action = ROTATE_LEFT;
      delay(rotatedelay);
      break;
    case B01110000: // turn left
      car.turnLeft(SPEED_90_DEG);
      lst_action = ROTATE_LEFT;
      delay(rotatedelay);
      break;
    case B00111000: // turn left
      car.moveLeft_fwd(max_speed, (int)(speed_factor[3]*multiplication_factor));
      lst_action = LEFT_TURN;
      break;
    case B00011100: // turn right
      car.moveRight_fwd(max_speed, (int)(speed_factor[3]*multiplication_factor));
      lst_action = RIGHT_TURN;
      break;
    case B00001110: // turn right
      car.turnRight(SPEED_90_DEG);
      lst_action = ROTATE_RIGHT;
      delay(rotatedelay);
      break;
    case B00000111: // turn right
      car.turnRight(SPEED_90_DEG);
      lst_action = ROTATE_RIGHT;
      delay(rotatedelay);
      break;
    case B10011000: // acute angle turn towards left
      acute_detect = ACUTE_LEFT;
      acute_detect_once = true;
      break;
    case B00011001: // acute angle turn towards right
      acute_detect = ACUTE_RIGHT;
      acute_detect_once = true;
      break;

    case B11110000: // 90 degree turn towards left
      car.turnLeft(SPEED_90_DEG);
      lst_action = ROTATE_LEFT;
      delay(rotatedelay);
      break;
    case B00001111: // 90 degree turn towards right
      car.turnRight(SPEED_90_DEG);
      lst_action = ROTATE_RIGHT;
      delay(rotatedelay);
      break;
    case B11001100: // acute angle turn towards left
      acute_detect = ACUTE_LEFT;
      acute_detect_once = true;
      break;
    case B11011000: // acute angle turn towards left
      acute_detect = ACUTE_LEFT;
      acute_detect_once = true;
      break;
    case B00110011: // acute angle turn towards right
      acute_detect = ACUTE_RIGHT;
      acute_detect_once = true;
      break;
    case B00011011: // acute angle turn towards right
      acute_detect = ACUTE_RIGHT;
      acute_detect_once = true;
      break;
    case B11111000: // 90 degree turn towards left
      car.turnLeft(SPEED_90_DEG);
      lst_action = ROTATE_LEFT;
      delay(rotatedelay);
      break;
    case B00011111: // 90 degree turn towards right
      car.turnRight(SPEED_90_DEG);
      lst_action = ROTATE_RIGHT;
      delay(rotatedelay);
      break;
    case B11011100: // acute angle turn towards left
      acute_detect = ACUTE_LEFT;
      acute_detect_once = true;
      break;
    case B00111011: // acute angle turn towards right
      acute_detect = ACUTE_RIGHT;
      acute_detect_once = true;
      break;
    case B10010000: // ACUTE_LEFT
      acute_detect = ACUTE_LEFT;
      acute_detect_once = true;
      break;
    case B10001000: // ACUTE_LEFT
      acute_detect = ACUTE_LEFT;
      acute_detect_once = true;
      break;
    case B01010000: // ACUTE_LEFT
      acute_detect = ACUTE_LEFT;
      acute_detect_once = true;
      break;
    case B01001000: //ACUTE_LEFT
      acute_detect = ACUTE_LEFT;
      acute_detect_once = true;
      break;
    case B00101000: // ACUTE_LEFT
      acute_detect = ACUTE_LEFT;
      acute_detect_once = true;
      break;
    case B00001001: // ACUTE_RIGHT
      acute_detect = ACUTE_RIGHT;
      acute_detect_once = true;
      break;
    case B00010001: //ACUTE_RIGHT
      acute_detect = ACUTE_RIGHT;
      acute_detect_once = true;
      break;
    case B00001010: //ACUTE_RIGHT
      acute_detect = ACUTE_RIGHT;
      acute_detect_once = true;
      break;
    case B00010010: //ACUTE_RIGHT
      acute_detect = ACUTE_RIGHT;
      acute_detect_once = true;
      break;
    case B00010100: //ACUTE_RIGHT
      acute_detect = ACUTE_RIGHT;
      acute_detect_once = true;
      break;

    case B11111100: // 90 degree turn towards left
      car.turnLeft(SPEED_90_DEG);
      lst_action = ROTATE_LEFT;
      delay(rotatedelay);
      break;
    case B00111111: // 90 degree turn towards right
      car.turnRight(SPEED_90_DEG);
      lst_action = ROTATE_RIGHT;
      delay(rotatedelay);
      break;
    case B11111111:
      obstrackel_detected = true;
      car.fwd(max_speed);
      lst_action = FORWORD;
      delay(100);
      break;
    default:
      car.fwd(max_speed);
      lst_action = FORWORD;

  }

  delay(10);    // delay to derevative value work properly

}


void no_lineDetected() {
  switch (lst_action) {
    case FORWORD:
      car.stop();
      break;
    case RIGHT_TURN:
      car.moveLeft_fwd(max_speed, (int)(speed_factor[3]*multiplication_factor));
      break;
    case LEFT_TURN:
      car.moveRight_fwd(max_speed, (int)(speed_factor[3]*multiplication_factor));
      break;
    case ROTATE_RIGHT:
      car.turnRight(SPEED_90_DEG);
      delay(rotatedelay);
      break;
    case ROTATE_LEFT:
      car.turnLeft(SPEED_90_DEG);
      delay(rotatedelay);
      break;
    default:
      car.stop();
  }
}
