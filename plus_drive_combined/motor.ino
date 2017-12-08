void motorA(int t)
{
  saber.motor(1, map(constrain(t, -limit, limit), 100, -100, -127, 127));
}
void motorB(int t)
{
  saber.motor(2, map(constrain(t, -limit, limit), 100, -100, -127, 127));
}


void motor_off()
{
  saber.motor(1, 0);
  saber.motor(2, 0);
}

void freewheel_on()
{
  Serial3.print("Q1:2047\r\n");
  Serial3.print("Q2:2047\r\n");
}
void freewheel_off()
{
  Serial3.print("Q1:-2047\r\n");
  Serial3.print("Q2:-2047\r\n");
}

void ramp(int x)
{
  saber.setRamping(x);
}

void switch_axis(char ch)
{
  switch (ch) {
    case 'x':
      for (int i = 0; i < 2; i++)
        digitalWrite(bot.relay[i], HIGH);
      break;
    case 'y':
      for (int i = 0; i < 2; i++)
        digitalWrite(bot.relay[i], LOW);
  }
}
