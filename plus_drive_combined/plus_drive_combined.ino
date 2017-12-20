/*
   Made by SRM Team Robocon
   Robocon-2018
   -----------------------------------------------------------------------------------------------------
   This drive is a plus drive consisting of two perpendicular axes.
   There are total 4-wheels which are controlled by a single Sabertooth Motor Driver.
   2 Relays have been used to switch between motors of X & Y axes.
   Both relays at HIGH will control the motor on X-axis and both LOW will control the motors on Y-axis.
   The launcher motor is controlled by Hercules Motor Driver.
   3 Photoswitches have been used to properly position the rotating arm.
   1 bump-switch acts as a maximum limit for the arm in CCW direction.
   ------------------------------------------------------------------------------------------------------
*/

#define limit 0                                                               //****Check this limit before uploading the Code****
#define debug false
#define BNO055_SAMPLERATE_DELAY_MS (100)

#include <Sabertooth.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>


Adafruit_BNO055 bno = Adafruit_BNO055();
Sabertooth saber(128, Serial3);

int i, j;

struct plus {
  int photo[3] = {53, 51, 49};                                                  //pins for 3 photoswitches
  int relay[2] = {29, 27};                                                      //pins for 2 relays used in switching motors
  int launcher[3] = {13, 12, 11};                                               //pins for hercules used for driving the launcher motor
  int b_switch;                                                                 //****Please update it as soon as anyone comes to know about it****
} bot;

void declare_pins() {
  for (i = 0; i < 3; i++) {
    if (i != 2)
      pinMode(bot.relay[i], OUTPUT);
    pinMode(bot.photo[i], INPUT);
    pinMode(bot.launcher[i], OUTPUT);
  }
}

float get_angle(char axis, bool negative_angles = true) {
  sensors_event_t event;
  bno.getEvent(&event);
  float x = event.orientation.x; // taking X readings
  float y = event.orientation.y;
  float z = event.orientation.z;
  if (negative_angles)
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
