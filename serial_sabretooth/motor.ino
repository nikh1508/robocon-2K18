void motorA(int t)
{s2.motor(2,map(constrain(pwmA,-lim,lim), 100, -100, -127,127)); 
}
void motorB(int t)
{
s1.motor(1,map(constrain(pwmB,-lim,lim), 100, -100, -127,127)); 
}
void motorD(int t)
{ 
  s1.motor(2,map(constrain(pwmD,-lim,lim), 100, -100, -127,127));
}
void motorC(int t)
{
  s2.motor(1,map(constrain(pwmC,-lim,lim), 100, -100, 127,-127));
}//5 6 7 pwm 6
