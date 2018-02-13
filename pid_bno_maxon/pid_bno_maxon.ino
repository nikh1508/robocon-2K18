#define BNO055_SAMPLERATE_DELAY_MS (100)
#define Kp bot_data.kp
#define Ki bot_data.ki
#define Kd bot_data.kd
#define setValue bot_data.slider
#define alpha 0.1
#define saber Serial1

#include<PID_v1.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

struct mtr {
  int dir_l = 34, pwm_l = 5, pwm_r = 4, dir_r = 36;
  int set_l = 0, set_r = 0;
} motor;

void write_motor(int x, int y, boolean ramp=false, double cnst=alpha);
int pins[] = {11, 12, 13};

double setpoint, input, output = 0.0;

struct data {
  double kp = 0, ki = 0, kd = 0;
  int slider = 0;
  int power = 0;
} bot_data;

PID myPID(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);
Adafruit_BNO055 bno = Adafruit_BNO055(55);

double get_angle(char axis) {
  sensors_event_t event;
  bno.getEvent(&event);
  double x = event.orientation.x; // taking X readings
  double y = event.orientation.y;
  double z = event.orientation.z;
  if (x > 180)                  //to get negative angles in CCW direction
    x = (360 - x) * -1;
  if (x == 0.0625 || x == -0.0625)              //observed junk values
    x = 0.0;
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
double cur_l = 0, cur_r = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  saber.begin(9600);
  Serial3.begin(57600);
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
  //setpoint = get_angle('x');
  last = setpoint;
  myPID.SetOutputLimits(-500, 500);
  myPID.SetMode(AUTOMATIC);
  digitalWrite(11, 0);
  digitalWrite(13, 0);
  digitalWrite(12, 0);
  saber.print("R1:0\r\n");
  saber.print("R2:0\r\n");
  //last_time = millis();
}

