int max_speed = 300;
int least_speed = 1500;
int initial_speed = 1720;
double brake_time = 30;
/////////////routines/////////////
double nx = initial_speed; //threshold to start from
double ny = nx;
double nm = -0.05; //call in function//increase to increase accelerationn
double nc = ny - nx * nm; //call in function
////////////routines////////////
double di_exception = 2400; //exception//2380
double c15 = 88; //exception//82
double c90 = 465;
double t1 = 1280;
double t3 = 3100;
double straight = 1000; //exception
///////////////////////////////
bool forw[3] = {true, true, true};
bool bac[3] = {true, true, true};
////////////////////////////////
struct step_declarations {
  double stepcount;
  double set_stepcount;
  double brake;
  double set_brake=brake_time;
} step[3];
double part = 0.9;
/////////////////////////
/////////////////////////
char c = '\0'; //q==ccw,e==cw
int i;
///////////////////////////
struct actual {
  int tz[20];
  char cc[20];
  double actual_step[20];
} engine[5];
////////////////////////////
int select = 4;
int loco = 0;
////////////////////////////
int tz = 13;
int redphoto = 12;
int load = 9;
////////////
int data_1 = 14;
int data_2 = 15;
int data_3 = 16;
/////////////////////////////
int led_1=A1;
int led_2=A2;
/////////////////////////////
int feedback_1 = LOW; //tz
int feedback_2 = LOW; //bumpswitch
int feedback_3 = LOW; //photoswitch
//////////////////////////////
bool flag_arena[2] = {true, true};
bool flag_setup[2] = {true, true};
bool flag_drive = true;
