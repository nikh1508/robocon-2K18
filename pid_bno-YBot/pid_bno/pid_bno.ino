#define BNO055_SAMPLERATE_DELAY_MS (100)
#define Kp bot_data.kp
#define Ki bot_data.ki
#define Kd bot_data.kd
#define setValue bot_data.slider

#include<PID_v1.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include<SoftwareSerial.h>

SoftwareSerial bot(6, 7);

struct mtr {
  int dir_l = 34, pwm_l = 5, pwm_r = 4, dir_r = 36;
  int set_l = 5, set_r = 0;
} motor;

int pins[] = {30, 32, 6, 36, 4, 34, 5};

double setpoint, input, output;

struct data {
  double kp = 5, ki = 0, kd = 0;
  int slider = 0;
  int power = 0;
} bot_data;

PID myPID(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);
Adafruit_BNO055 bno = Adafruit_BNO055();

double get_angle(char axis) {
  sensors_event_t event;
  bno.getEvent(&event);
  double x = event.orientation.x; // taking X readings
  double y = event.orientation.y;
  double z = event.orientation.z;
  if (x > 180)                  //to get negative angles in CCW direction
    x = (360 - x) * -1;
  switch (axis) {
    case 'x':
      return x;
      break;
    case 'y':
      return y;
      break;
    case 'z':
      return z;
      break;
    default:
      return 0;
  }
}

long last_time;

double last;
int pwm_l = 0, pwm_r = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
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
  delay(1500);
  setpoint = get_angle('x');
  last = setpoint;
  myPID.SetOutputLimits(-255, 255);
  myPID.SetMode(AUTOMATIC);
  digitalWrite(30, 1);
  digitalWrite(32, 1);
  digitalWrite(36, 1);
  //last_time = millis();
}

