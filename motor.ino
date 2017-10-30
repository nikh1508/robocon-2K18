void motorA(int t)
{
  t= constrain(t,-lim, lim);
  int var = map(t, 100, -100, 128, 255);
  Serial3.write(var);
  delay(1); 
}
void motorB(int t)
{
 t= constrain(t,-lim, lim);
 int var = map(t, 100, -100, 1,127);
  Serial2.write(var);
    delay(1); 
}
void motorD(int t)
{
  t= constrain(t,-lim, lim);
  int var = map(t, 100, -100, 128, 255);
  Serial2.write(var);
    delay(1); 
}
void motorC(int t)
{
  t= constrain(t,-lim, lim);
  int var = map(t, 100, -100, 127, 1);
  Serial3.write(var);
    delay(1); 
}//5 6 7 pwm 6
