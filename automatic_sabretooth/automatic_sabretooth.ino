#include <Arduino.h>
#include <PID_v1.h>
#include <limits.h>

#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <utility/imumaths.h>

#define BNO055_SAMPLERATE_DELAY_MS (100)

constexpr double kp = 68;
constexpr double kd = 10;
constexpr double ki = 10;
constexpr int BRAKE = INT_MIN;

constexpr int ENABLE = A8;
constexpr int MONSTER_PWM = 5;
constexpr int MONSTER_L1 = 7;
constexpr int MONSTER_L2 = 8;

constexpr int PHOTO = A3;

double setpoint = 0.0;
double input = 0.0;
double output = 0.0;

volatile int flag = 1;
volatile int flag2 = 1;

struct motors {
  int m1 = BRAKE, m2 = BRAKE, m3 = BRAKE;
} motors;

Adafruit_BNO055 bno = Adafruit_BNO055(55);
PID myPID = PID(&input, &output, &setpoint, kp, ki, kd, DIRECT);

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);

  

  pinMode(ENABLE, OUTPUT);
  pinMode(MONSTER_L1, OUTPUT);
  pinMode(MONSTER_L2, OUTPUT);
  pinMode(MONSTER_PWM, OUTPUT);

  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  

  digitalWrite(ENABLE, HIGH);

  if (!bno.begin()) {
    Serial.println("BNO not found.");
    while (1)
      ;
  }


 bno.setExtCrystalUse(true);


 write_motors(BRAKE, BRAKE, BRAKE);

 pinMode(13, OUTPUT);
  

 int cur = HIGH;
 for (int i = 0; i < 5; i++) {
 digitalWrite(13, cur);
 delay(1000);
 cur = cur ^ 1;
 }
 
}

void loop() {

digitalWrite(13, HIGH);
forward(500, 2000);
stop_all();
digitalWrite(13, LOW);



  while (1)
    ;
}
