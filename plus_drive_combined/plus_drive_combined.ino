

/*
 * Made by SRM Team Robocon
 * Robocon-2018
 * -----------------------------------------------------------------------------------------------------
 * This drive is a plus drive consisting of two perpendicular axes.
 * There are total 4-wheels which are controlled by a single Sabertooth Motor Driver.
 * 2 Relays have been used to switch between motors of X & Y axes.
 * Both relays at HIGH will control the motor on X-axis and both LOW will control the motors on Y-axis.
 * The launcher motor is controlled by Hercules Motor Driver.
 * 3 Photoswitches have been used to properly position the rotating arm. 
 * 1 bump-switch acts as a maximum limit for the arm in CCW direction.
 * ------------------------------------------------------------------------------------------------------
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
  int mot_launcher[3] = {13, 12, 11};                                           //pins for hercules used for driving the launcher motor 
}bot;

void declare_pins() {
  for (i = 0; i < 3; i++) {
    if (i != 2)
      pinMode(bot.relay[i], OUTPUT);
    pinMode(bot.photo[i], INPUT);
    pinMode(bot.mot_launcher[i], OUTPUT);
  }
}
