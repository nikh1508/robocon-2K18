#define bno_rst_pin 8
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

constexpr double kp = 100;
constexpr double kd = 0;
constexpr double ki = 0;
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
  pinMode(bno_rst_pin, OUTPUT);
  digitalWrite(bno_rst_pin, HIGH);

  //delay(2000);                                                  //INITIAL DELAY
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

  write_motors(10, 300, 300);


  Serial.println("before");
  if (!bno.begin()) {
    Serial.println("BNO not found.");
    while (1);
  }

  Serial.println("after");

  bno.setExtCrystalUse(true);

//  write_motors(BRAKE, BRAKE, BRAKE);


  attachInterrupt(digitalPinToInterrupt(2), isr, RISING);
  attachInterrupt(digitalPinToInterrupt(3), isr2, RISING);

}

void loop() {

  write_motors(10, 300, 300);
  STOP
  
//  forward(600, 1, 0);
  rotate_to_angle(300, 270, CCW);

  STOP
  forward_time(600, 270, 1000);


  STOP
  forward(800, 2, 270);
  rotate_to_angle(100, 180, CCW);
  delay(1000);
  rotate_to_angle(100, 90, CCW);
  forward(800, 2, 90);
  rotate_to_angle(100, 0, CCW);
  forward(800, 1, 0);
  rotate_to_angle(100, 270, CCW);
  forward(800, 2, 270);
  
  rotate_to_angle(100, 180, CCW);
  delay(1000);
  rotate_to_angle(100, 90, CCW);
  forward(800, 2, 90);

  delay(1000);

  rotate_to_angle(100, 270, CCW);

  forward(800, 5, 270);
  rotate_to_angle(100, 180, CCW);
  delay(1000);
  rotate_to_angle(100, 90, CCW);

  forward(800, 5, 90);
  
  
  
  
  
  STOP
}
