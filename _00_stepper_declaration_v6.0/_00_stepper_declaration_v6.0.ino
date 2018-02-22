int max_speed = 300;
int least_speed=1500;
int initial_speed = 1720;
double brake_time = 20;
///////////filters//////////////
double nx = initial_speed; //threshold to start from
double ny = nx;
double nm = -0.015; //call in function//increase to increase accelerationn
double nc = ny - nx * nm; //call in function
////////////routines////////////
double di_exception = 2380; //exception//2380
double c15 = 88; //exception//82
double c90 = 460;
double t1 = 1200;
double t3 = 3000;
double straight = 1000; //exception
///////////////////////////////
//////////////////////////////
#include<Wire.h>
#define adr 0x29//0x28 or 0x29
////
byte lsb_yaw;
byte msb_yaw;
double yaw = 0;
double yaw_offset = 0;
////
bool forw[3] = {true, true, true};
bool bac[3] = {true, true, true};
//////////////////////////////
struct step_declarations {
  double stepcount;
  double set_stepcount;
  double brake;
  double set_brake;
  double divisor;
  double multiplier;
} step[3];
double part;
////
bool flag[3] = {true, true, true};
////
char c = '\0'; //q==ccw,e==cw
int i;
////pid/////
double time_i = 0, time_f = 0, time;
double p = 0.00699, d = 1000, ki = 0.0000000007;
double yaw_d = 0, yaw_prev = 0, yaw_i = 0;
//////////
struct actual {
  int tz[20];
  char cc[20];
  double actual_step[20];
} engine[5];
//
int select = 4;
int loco = 0;
//
int feedback_1 = LOW; //tz
int feedback_2 = LOW; //bumpswitch
int feedback_3 = LOW; //photoswitch
///////////////////////////////
int feed1 = 0;
int feed2 = 0;
int feed3 = 0;
///////////////////////////////
bool flag_arena[2] = {true, true};
bool flag_setup[2] = {true, true};
bool flag_drive = true;
////////////////////////////////////
int ping = 0;
