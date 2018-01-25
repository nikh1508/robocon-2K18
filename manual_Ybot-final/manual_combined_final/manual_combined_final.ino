#define BNO055_SAMPLERATE_DELAY_MS (100)
#define setValue bot_data.slider
#define capped_val 70
#define debug false                                                 //check

#include<PID_v1.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

struct mtr {
  int dir_f1 = 30, pwm_f = 6, dir_f2 = 32;
  int dir_l = 34, pwm_l = 5, pwm_r = 4, dir_r = 36;
} motor;

struct pneumatic {
  int dcv_l_up = 40, dcv_l_down = 38;
  int dcv_r_up = 44, dcv_r_down = 42;
  int belt_l_dir1 = 50, belt_l_dir2 = 52, belt_l_pwm = 2;
  int belt_r_dir1 = 48, belt_r_dir2 = 46, belt_r_pwm = 3;
}pneumatic;
int pwm_f = 0, pwm_l = 0, pwm_r = 0;                                //PWM - values of motors
bool updated = false;

double pid_mat[3][3] = {{25 / 4 , 25 / 4, 23 / 4}, { 39 / 4, 18 / 4, 8 / 4}, { 500 / 4, 5 / 4 , 45 / 4}}; //PID Constants
int pins[] = {30, 32, 6, 36, 4, 34, 5};                             //Output Pins

struct data {
  int fwd, bkd, left, right, cw, ccw;
  int slider = 0;
  int power = 0;
  int motion;
  int curr_motion = 0;
  int pneumatic;
  int dcv_l, dcv_r;
  int belt_l, belt_r;
} bot_data;

double setpoint = 0.0, input = 0.0, output = 0.0;

struct pid_obj {
  PID myPID = PID(&input, &output, &setpoint, 0, 0, 0, DIRECT);
} pid_obj;

Adafruit_BNO055 bno = Adafruit_BNO055();



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(57600);
  for (int pin : pins) {
    pinMode(pin, OUTPUT);
  }
  if (!bno.begin())
  {
    Serial.print("BNO not detected. Check connections or I2C ADDR!(Run I2C Scanner in Debug Mode.)");
    while (1);
  }
  bno.setExtCrystalUse(true);
  delay(1000);
  pid_obj.myPID.SetOutputLimits(-255, 255);
  pid_obj.myPID.SetMode(AUTOMATIC);
}

