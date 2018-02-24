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

constexpr double kp = 50;
constexpr double kd = 2;
constexpr double ki = 2;
constexpr int BRAKE = INT_MIN;

constexpr int MONSTER_PWM = 10;
constexpr int MONSTER_L1 = 9;
constexpr int MONSTER_L2 = 11;

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

void setup() {

  delay(2000);
  
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);

  ramp1(0);
  ramp2(0);

  pinMode(MONSTER_L1, OUTPUT);
  pinMode(MONSTER_L2, OUTPUT);
  pinMode(MONSTER_PWM, OUTPUT);

  pinMode(2, INPUT);
  pinMode(3, INPUT);

  if (!bno.begin()) {
    Serial.println("BNO not found.");
    while (1);
  }

  bno.setExtCrystalUse(true);

  attachInterrupt(digitalPinToInterrupt(3), isr2, RISING);

  Serial.println("Starting bot...");

}

void loop() {
  // A ->  B
  forward(500, 1, 0);
  rotate_to_angle(270, CCW);

  // B -> TZ1 {
  forward(500, 3, 270);
  rotate_to_angle(180, CCW);
  l2line();
  backward_time(200, 180, 4000 );
  backward(10);
  forward(300, 1, 180);

  // TZ1 -> B
  rotate_to_angle(90, CCW);
  forward(500, 3, 90);

  // B -> C
  rotate_to_angle(0, CCW);
  forward(500, 1, 0);

  // C -> TZ2
  rotate_to_angle(270, CCW);
  forward(500, 3, 270);
  rotate_to_angle(180, CCW);
  l2line();
  backward_time(200, 180, 4000);
  forward(300, 1, 180);

  // TZ2 -> LOAD
  rotate_to_angle(90, CCW);
  forward(500, 2,  90);
  rotate_to_angle(270, CCW);
  l2line();

  // LOAD -> TZ3
  forward(500, 5, 270);
  rotate_to_angle(180, CCW);
  backward_time(200, 180, 4000);
  forward(500, 1, 180);

  // TZ3 -> LOAD
  rotate_to_angle(90, CCW);
  forward(500, 5, 90);

  STOP
}
