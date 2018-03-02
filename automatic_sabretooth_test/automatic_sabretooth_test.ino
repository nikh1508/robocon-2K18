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
#define adr 0x29


constexpr int FAST_SPEED = 800, SLOW_SPEED=140;
void backward_enc(int, int, int, bool fence = false);
void forward_enc(int, int, int, int offset = 1500);

constexpr double kp = 100;
constexpr double kd = 10;
constexpr double ki = 10;
constexpr int BRAKE = INT_MIN;

constexpr double ALPHA = 0.9;

constexpr int MONSTER_PWM = 5;
constexpr int MONSTER_L1 = 4;
constexpr int MONSTER_L2 = 6;

constexpr int TCRT1 = 51;
constexpr int TCRT2 = 53;

constexpr int LINE_THRES = 95;

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

byte lsb_yaw;
byte msb_yaw;
double yaw = 0;
double yaw_offset = 0;
int i;


inline double D2R(double deg) {
  return deg * PI / 180.0;
}

struct motors {
  int m1 = BRAKE, m2 = BRAKE, m3 = BRAKE;
} motors;

//Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x29);
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
  attachInterrupt(digitalPinToInterrupt(3), isr2, RISING);
  reset_encoder();
  Serial.println("Starting bot...");
}

void loop() {

  
  while (Serial.available()) {
    char ch = Serial.read();
    reset_encoder();
    delay(200);
  }

  Serial.println(encoder());


//   write_motors(+27, +300, -300); // sideways
//  delay(700);
//  stop_all();
//  delay(200);
//  forward_enc(FAST_SPEED, 14172, 0); // A
//  delay(200);
//  rotate_to_angle(90, CW);
//  delay(300);
//  backward(200, 50, 90); // Sunfounder Offset
//  delay(1000);
//  backward_enc(FAST_SPEED, -3254, 90); // BLUE
//  delay(1000);
//  Serial.println("IN TZ1");
//  tz1(); delay(1000);
//  Serial.println("FRM TZ1 2 TZ2");
//  tz1_to_tz2(); delay(1000);
//  Serial.println("IN TZ3");
//  tz3(); delay(1000);
//  STOP
  
}
