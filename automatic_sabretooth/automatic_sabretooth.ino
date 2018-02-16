#define bno_rst_pin 7

#include <Arduino.h>
#include <PID_v1.h>
#include <limits.h>

#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <utility/imumaths.h>

#define BNO055_SAMPLERATE_DELAY_MS (100)
#define CLEAR_INTERRUPTS EIFR |= (1 << INTF0) | ( 1 << INTF1)
#define STOP while (1) ;

constexpr double kp = 68;
constexpr double kd = 10;
constexpr double ki = 10;
constexpr int BRAKE = INT_MIN;

constexpr int ENABLE = A8;
constexpr int MONSTER_PWM = 12;
constexpr int MONSTER_L1 = 11;
constexpr int MONSTER_L2 = 13;


double setpoint = 0.0;
double input = 0.0;
double output = 0.0;
double last_error = 0.0;

volatile int ctr2 = 0;
volatile int ctr = 0;
volatile int ctr3 = 0;
volatile long long last_time = 0;

struct motors {
  int m1 = BRAKE, m2 = BRAKE, m3 = BRAKE;
} motors;

Adafruit_BNO055 bno = Adafruit_BNO055(55);
PID myPID = PID(&input, &output, &setpoint, kp, ki, kd, DIRECT);

void setup() {
  pinMode(bno_rst_pin, OUTPUT);
  digitalWrite(bno_rst_pin, HIGH);
  delay(2000);                                                  //INITIAL DELAY
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
    while (1);
  }
  bno.setExtCrystalUse(true);
  //  write_motors(BRAKE, BRAKE, BRAKE);
  pinMode(13, OUTPUT);
}

void loop() {


  forward(300, 20000);
  print_error();
  rot90(250, 5000);
  print_error();
  ///  STOP

  forward_ig(300, 10000, 3);
  print_error();

  move180(250, 5000);
  print_error();
  forward_ig(300, 10000, 3);
  print_error();
  rot90(250, 5000);
  STOP
  forward_ig(300, 10000, 1);
  rot90(250, 5000);
  forward_ig(300, 10000, 3);
  move180(250, 5000);
  forward_ig(300, 10000, 3);
  //  move180(250,5000);
  //  forward_ig(300,15000,7);
  //  move180(250,5000);
  //  forward_ig(300,15000,7);
  //
  STOP
}
