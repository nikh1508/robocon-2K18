#define BNO055_SAMPLERATE_DELAY_MS (100)
#define setValue bot_data.slider
#define capped_val 100                                               //back motors capped value
#define debug false                                                  //check
#define deacc 0.002
#define acc 0.8
//--------------------------Motor Pins-------------------------------------
#define dir_f1 30
#define dir_f2 32
#define pwm_f 6
#define dir_l 34
#define pwm_l 5
#define dir_r 36
#define pwm_r 4
//--------------------------Pneumatic Pins----------------------------------
#define dcv_r_up 40
#define dcv_r_down 38
#define dcv_l_up 42
#define dcv_l_down 44
#define belt_l_dir1 50
#define belt_l_dir2 52
#define belt_l_pwm 2
#define belt_r_dir1 48
#define belt_r_dir2 46
#define belt_r_pwm 3
#define photo_switch 2
//--------------------------------------------------------------------------

#include<PID_v1.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>


int set_f = 0, set_l = 0, set_r = 0;                                //PWM - values of motors
bool updated = false;

double pid_mat[3][3] = {{50.0 / 4.0 , 50.0 / 4.0, 30.0 / 4.0}, { 45.0 / 4.0, 20.0 / 4.0, 6.0 / 4.0}, { 45.0 / 4.0, 20.0 / 4.0 , 6.0 / 4.0}}; //PID Constants   { 48 / 4, 15 / 4 , 3 / 4}
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

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x29);

unsigned long start_time;
bool picked_up=false;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(57600);
  pinMode(photo_switch, INPUT_PULLUP);
  for (int pin : pins) {
    pinMode(pin, OUTPUT);
  }
  Serial.println("Started");
//  for (int i = 0 ; i < 3; i++)
//    for (int j = 0 ; j < 3; j++)
//      Serial.println(pid_mat[i][j]);
  if (!bno.begin())
  {
    Serial.print("BNO not detected. Check connections or I2C ADDR!(Run I2C Scanner in Debug Mode.)");
    while (1);
  }
  Serial.println("Started2");
  bno.setExtCrystalUse(true);
  delay(1000);
  pid_obj.myPID.SetOutputLimits(-500, 500);
  pid_obj.myPID.SetMode(AUTOMATIC);
attachInterrupt(digitalPinToInterrupt(photo_switch),isr, RISING);
}

