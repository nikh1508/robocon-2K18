#define lim 100
#include <Sabertooth.h>

Sabertooth s1(128,Serial2);
Sabertooth s2(128,Serial3);
struct plus{

};
String ch;
int dir=0;
float pw, fpw;
float a = 0.996;
float ra = 0.450;
  int pwmA=0;
  int pwmB=0;
  int pwmC=0;
  int pwmD=0;
  int magnitude=80;
  int magnitude1=80;
  int magnitude2=80;
  int cmagnitude=100;
  unsigned long cur_t;
    unsigned long pre_t=0;
    int flag=1;
