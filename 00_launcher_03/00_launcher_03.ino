#define Serial_debug  false
#define manual_mode true
#define fw_pwm 85   //TZ1 85     TZ3 148
#define stop_pwm 120 //TZ1 120   TZ3 150
int f_pwm=0,b_pwm=0,del=0;
int a = 13;
int b = 11;
int pwm = 12;
int photo_forw = 43;     // Stopping Switch
int dphoto_forw = 0;
int photo_bac = 47; 
int dphoto_bac=0;//Loading Switch
int dphoto_load = 0;
int dshoot=0,zp1=0,zp2=0;
char qw = 'o';
int shoot=8,zone_pin1=9,zone_pin2=10;
