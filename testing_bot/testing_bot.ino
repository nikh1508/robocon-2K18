#define bt Serial3
#define debug true
#define BNO055_SAMPLERATE_DELAY_MS (100)

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

Adafruit_BNO055 bno = Adafruit_BNO055();
int i, j, spd;
unsigned long lastTime;
double Input, Output, Setpoint;
double errSum, lastErr, error;
double kp, ki, kd, k = 0.0;
int ini = 0, zc = 0, pwm1 = 30, pwm2 = 30, last_func, op;

void move_motors(int, int);
void stop_motors(int, bool hard_brake = true);
void change_pwm(int, int);
class PID_Control {
  public:
    void Compute()

    {
      /*How long since we last calculated*/
      unsigned long now = millis();
      double timeChange = (double)(now - lastTime);

      /*Compute all the working error variables*/
      error = Setpoint - Input;
      errSum += (error * timeChange);
      double dErr = (error - lastErr) / timeChange;

      /*Compute PID Output*/
      Output = kp * error + ki * errSum + kd * dErr;

      /*Remember some variables for next time*/
      lastErr = error;
      lastTime = now;
      pwm1 = pwm1 + Output;
      change_pwm(2, pwm1);
    }

    void SetTunings(double Kp, double Ki, double Kd)
    {
      kp = Kp;
      ki = Ki;
      kd = Kd;
    }
} pid;

struct testing_bot {
  int m_left[3] = {8, 9, 10}, m_right[3] = {5, 6, 7};
} bot;


void declare_pins() {
  for (i = 0; i < 3; i++)
  {
    pinMode(bot.m_left[i], OUTPUT);
    pinMode(bot.m_right[i], OUTPUT);
  }
}

float get_angle(char axis) {
  sensors_event_t event;
  bno.getEvent(&event);
  float x = event.orientation.x; // taking X readings
  float y = event.orientation.y;
  float z = event.orientation.z;
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


bool dir; String str1, str2;


void startup_tone() {
  tone(2, 800);
  delay(230);
  tone(2, 1000);
  delay(230);
  tone(2, 1400);
  delay(400);
  noTone(2);
}

void i2c_scanner() {
  Serial.println("\nI2C Scanner");
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++ )
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    Serial.println("Current address being tested::" + String(address));

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
}


