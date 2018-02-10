#define debug false
#include <PS2X_lib.h>
PS2X ps2x;
int error = 0;
///////////////
#include<Wire.h>
#define adr 0x28
////
byte lsb_yaw;
byte msb_yaw;
double yaw = 0;
double yaw_offset = 0;
////
bool forw[3] = {true, true, true};
bool bac[3] = {true, true, true};
////
struct filters {
  double initial; //initial (actual target)//
  double initial_a; //initial (actual target)
  double alpha_a;//increment
  double alpha_b;//decrement
  double target; //also =OCR1A//actual initial
  double rev = target + initial_a; //reverse
  double output;
} filter[3];
////
struct step_declarations {
  double stepcount;
  double set_stepcount;
  double brake;
  double set_brake;
  double divisor;
  double multiplier;
} step[3];
////
bool flag[3] = {true, true, true};
////
char c = '\0'; //q==ccw,e==cw
int i;
////pid/////
double time_i = 0, time_f = 0, time;
double p = 0.00699, d = 1000, ki = 0.0000000007;
double yaw_d = 0, yaw_prev = 0, yaw_i = 0;
/////////
bool flag_func[30] = {true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true};
bool fake[15] = {true, false, false, false, false, false, false, false, false, false, false, false, false, false, false};
bool code_flag[5] = {true, false, false, false, false};
