#include <Arduino.h>
#include <PID_v1.h>
#include <limits.h>

#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <utility/imumaths.h>

#define BNO055_SAMPLERATE_DELAY_MS (100)
#define CLEAR_INTERRUPTS EIFR |= (1 << INTF0) | ( 1 << INTF1)

constexpr double kp = 25;//68;
constexpr double kd = 20;//10;
constexpr double ki = 10;//10;
constexpr int BRAKE = INT_MIN;

constexpr int ENABLE = A8;
constexpr int MONSTER_PWM = 12;
constexpr int MONSTER_L1 = 11;
constexpr int MONSTER_L2 = 13;


double setpoint = 0.0;
double input = 0.0;
double output = 0.0;

volatile int ctr2 = 0;
volatile int ctr = 0;
volatile int ctr3  =0;


struct motors {
  int m1 = BRAKE, m2 = BRAKE, m3 = BRAKE;
} motors;

Adafruit_BNO055 bno = Adafruit_BNO055(55);
PID myPID = PID(&input, &output, &setpoint, kp, ki, kd, DIRECT);

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);

  ramp1(0);
  ramp3(0);


  pinMode(ENABLE, OUTPUT);
  pinMode(MONSTER_L1, OUTPUT);
  pinMode(MONSTER_L2, OUTPUT);
  pinMode(MONSTER_PWM, OUTPUT);

  pinMode(2, INPUT);
  pinMode(3, INPUT);


  digitalWrite(ENABLE, HIGH);

  if (!bno.begin()) {
    Serial.println("BNO not found.");
    while (1)
      ;
  }


  bno.setExtCrystalUse(true);


  //  write_motors(BRAKE, BRAKE, BRAKE);

  pinMode(13, OUTPUT);





}

void loop() {

  forward(300, 10000);
  stop_all();
  rot90(250, 5000);
  stop_all();
  forward_ig(300, 10000, 2);
  stop_all();
  rot90(250, 5000);

  while (1)
    ;
}
