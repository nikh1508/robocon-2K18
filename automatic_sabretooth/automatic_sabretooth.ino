#include <Arduino.h>
#include <PID_v1.h>
#include <Wire.h>
#include <limits.h>

// #include <Adafruit_BNO055.h>
// #include <Adafruit_Sensor.h>
// #include <utility/imumaths.h>

#define CLEAR_INTERRUPTS EIFR |= (1 << INTF0) | (1 << INTF1)
#define STOP while (1);
#define CW 1
#define CCW 0
#define ENCODER_SAMPLE_TIME 30
#define adr 0x29

constexpr int FAST_SPEED = 800, SLOW_SPEED = 140;
void backward_enc(int, int, int, bool fence = false);
void forward_enc(int, int, int, int offset = 1500);

constexpr double kp = 100;
constexpr double kd = 10;
constexpr double ki = 10;
constexpr int BRAKE = INT_MIN;

constexpr double ALPHA = 0.9;
constexpr int LINE_THRES = 95;

// ------------------------------ PINS -------------------

constexpr int MONSTER_PWM = 5;
constexpr int MONSTER_L1 = 4;
constexpr int MONSTER_L2 = 6;

constexpr int TCRT1 = 51;
constexpr int TCRT2 = 53;

constexpr int photo_forw = 11;
constexpr int photo_bac = 9;

constexpr int LAUNCHER_L1 = 2;
constexpr int LAUNCHER_L2 = 4;
constexpr int LAUNCHER_PWM = 3;

// -------------------------------------------------------

double setpoint = 0.0;
double input = 0.0;
double output = 0.0;

long long bno_last_time = -1;
long long bno_last_val = 0;

byte lsb_yaw;
byte msb_yaw;
double yaw = 0;
double yaw_offset = 0;

bool tz = LOW;
bool load = LOW;
int feedback_1, feedback_2;  // TCRT
boolean flag_test = true;
bool flag = true, flag1 = true, flag2 = true;
///////////
///////////tz_led////////////
bool d_led = HIGH;
int tz_led_pin_digital = 50;  // random
int tz_led_pin_analog = 51;   // random
/////////////////////////
int dphoto_forw = 0;
int dphoto_bac = 0;
int dphoto_load = 0;

int fwm[3] = {63, 107, 142};
int bwm[3] = {63, 107, 144};
int del[3] = {1, 17000, 2500};

// Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x29);
PID myPID = PID(&input, &output, &setpoint, kp, ki, kd, DIRECT);

void forward(int speed, int linecount, double target, int ign = 0);
void fwd_sun(int speed, int linecount, double target, int ignore = 0);
void back_sun(int speed, int linecount, double target, int ignore = 0);

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);

  bno_initialize();

  ramp1(0);
  ramp2(0);

  pinMode(MONSTER_L1, OUTPUT);
  pinMode(MONSTER_L2, OUTPUT);
  pinMode(MONSTER_PWM, OUTPUT);

  pinMode(2, INPUT);
  pinMode(3, INPUT);

  Serial.println("before bno...");
  //  while (!bno.begin()) {
  //    Serial.println("BNO not found.");
  //  }
  Serial.println("after bno...");

  //  bno.setExtCrystalUse(true);
  reset_encoder();
  Serial.println("Starting bot...");
}

void loop() {
  if (flag == true) {
    flag = false;
    startup();
  }
  read_feed();
  if (tz == LOW && load == HIGH && flag1 == true) {
    tz1();
  }

  if (tz == HIGH && load == HIGH && flag2 == true) {
    digitalWrite(tz_led_pin_digital, HIGH);
    flag1 = false;
    flag2 = false;
    tz1_to_tz2();
    digitalWrite(tz_led_pin_digital, LOW);
  }

  if (tz == HIGH && load == HIGH && flag2 == false) {
    digitalWrite(tz_led_digital, HIGH);
    tz2();
    digitalWrite(tz_led_pin_digital, LOW);
  }

  if (tz == LOW && load == HIGH && flag1 == true) {
    tz3();
  }
}
