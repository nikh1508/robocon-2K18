//-------------------------------------------------------------------------Drive Motor Functions------------------------------------------------------------------------------------------

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

//--------------------------------------------------------------------------Launcher Motor & Sensor Functions-----------------------------------------------------------------------------

void laun_ccw(int spd)
{
digitalWrite(bot.launcher[0],1);
digitalWrite(bot.launcher[2],0);
analogWrite(bot.launcher[1],spd);
}

void laun_cw(int spd)
{
digitalWrite(bot.launcher[0],0);
digitalWrite(bot.launcher[2],1);
analogWrite(bot.launcher[1],spd);
}

void laun_brak()
{
digitalWrite(bot.launcher[0],0);
digitalWrite(bot.launcher[2],0);
analogWrite(bot.launcher[1],0);
}

void laun_brakF()
{
digitalWrite(bot.launcher[0],1);
digitalWrite(bot.launcher[2],1);
analogWrite(bot.launcher[1],0);
}

