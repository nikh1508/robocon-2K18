#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include<PID_v1.h>

#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 bno = Adafruit_BNO055();

double Setpoint, Input, Output;
double kp = 12, ki = 3, kd = 4;
PID myPID(&Input, &Output, &Setpoint, kp, ki, kd, DIRECT);


int ini = 0;
float ang;
void loop() {
  // put your main code here, to run repeatedly:
  sensors_event_t event;
  bno.getEvent(&event);
  ang = event.orientation.x; // taking X readings
  if(ang>180)
  ang=-1*(360-ang);
  //  control(ang);  // goto the pwm control function
  if (!ini)
  {
    Setpoint = ang;
    Serial.println("Setting Setpoint="+String(Setpoint));
    ini = 1;
  }
  Input=ang;
  Serial.print(ang);
myPID.Compute();
Serial.print(" ");
Serial.println(Output);
}
