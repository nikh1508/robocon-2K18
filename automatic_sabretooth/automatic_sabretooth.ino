#include <Arduino.h>
#include <PID_v1.h>
#include <limits.h>

#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <utility/imumaths.h>

#define CLEAR_INTERRUPTS EIFR |= (1 << INTF0) | ( 1 << INTF1)
#define STOP while (1);
#define CW 1
#define CCW 0
#define ENCODER_SAMPLE_TIME 30

void backward_enc(int,int,int,bool fence=false);
void forward_enc(int, int, int, int offset=1500);

constexpr double kp = 100;
constexpr double kd = 10;
constexpr double ki = 10;
constexpr int BRAKE = INT_MIN;

constexpr double ALPHA = 0.9;

constexpr int MONSTER_PWM = 10;
constexpr int MONSTER_L1 = 9;
constexpr int MONSTER_L2 = 11;

constexpr int TCRT1 = 6;
constexpr int TCRT2 = 5;

constexpr int LINE_THRES = 90;

double setpoint = 0.0;
double input = 0.0;
double output = 0.0;
double last_error = 0.0;

volatile bool ctr1flag = false;
volatile bool ctr2flag = false;
volatile int ctr1 = 0;
volatile int ctr2 = 0;
volatile long long last_time = 0;

long long bno_last_time = -1;
long long bno_last_val = 0;


inline double D2R(double deg) {
  return deg * PI / 180.0;
}

struct motors {
  int m1 = BRAKE, m2 = BRAKE, m3 = BRAKE;
} motors;

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x29);
PID myPID = PID(&input, &output, &setpoint, kp, ki, kd, DIRECT);

void forward(int speed, int linecount, double target, int ign = 0);
void fwd_sun(int speed, int linecount, double target, int ignore = 0);
void back_sun(int speed, int linecount, double target, int ignore = 0);

void setup() {
  delay(2000);

  Serial.begin(9600);
  Serial1.begin(9600);
  Serial3.begin(9600);

  ramp1(0);
  ramp2(0);

  pinMode(MONSTER_L1, OUTPUT);
  pinMode(MONSTER_L2, OUTPUT);
  pinMode(MONSTER_PWM, OUTPUT);

  pinMode(2, INPUT);
  pinMode(3, INPUT);

  Serial.println("before bno...");
  if (!bno.begin()) {
    Serial.println("BNO not found.");
    while (1);
  }
  Serial.println("after bno...");

  bno.setExtCrystalUse(true);
  attachInterrupt(digitalPinToInterrupt(3), isr2, RISING);
  reset_encoder();
  Serial.println("Starting bot...");
}

void loop() {

//while(1){
//  Serial.println(encoder());
//  }
//  forward_enc(500, 3300, 0);
//  STOP
//  delay(500);
//  forward(500, 5000, 0);
//  delay(500);
//
//
forward_enc(1000, 14200, 0, 1500);
STOP
  write_motors(+27, +300, -300);
  delay(1000);
  stop_all();
  delay(500);
//  // ARSZ  -> A
  forward(1000, 14400, 0);
  STOP
  delay(500);
  rotate_to_angle(270, CCW);

  // A -> LOAD
//  backward_enc(1000, -5000, 0);
//  STOP
  forward_enc(1000, 3300, 270);
  delay(1000);
  // LOAD -> TZ1
  forward_enc(1000, 5000, 270);
  delay(500);
  rotate_to_angle(0, CW);
  delay(1000);
  backward_enc(250, -2100, 0, true);
  forward_enc(1000, 2000, 0);
  rotate_to_angle(270, CCW);
  backward_enc(1000, -5000, 270);
  
  STOP
//----------------------------
  // TZ1 -> LOAD
  rotate_to_angle(90, CCW);
  forward_enc(350, 5000, 90);

  delay(1000);

  // LOAD -> A
  forward(350, 3300, 90);

  // A -> B
  rotate_to_angle(0, CCW);
  forward(1000, 6200, 0);
  
}
