//void omni()
//{
//  fLX = fLX * a + LX * (1 - a);
//  fLY = fLY * a + LY * (1 - a);
//
//  theta = atan2(fLX, fLY) * 180 / 3.141592;
//  if (theta < 0) theta = map(theta, -180, 0, 180, 360);
//
//  magnitude = abs(fLX) > abs(fLY)  ? abs(fLX) : abs(fLY);
//  magnitude = map(magnitude, 0, 128, 0, 100);
//  fpw = fpw * ra + pw * (1 - ra); // to control turn CW CCW swooth
//  //  Serial.println(theta);
//}

void control(int angle)
{ pmagnitude = pmagnitude * ra + cmagnitude* (1 - ra);
 
  pwmA = pmagnitude * cos(0.0176 * (0.00 - angle));
  pwmB = pmagnitude * cos(0.0176 * (90.00 - angle));
  pwmC = pmagnitude * cos(0.0176 * (180.00 - angle));
  pwmD = pmagnitude * cos(0.0176 * (90- angle));
  motorA(pwmA - fpw);
  motorB(pwmB - fpw);
  motorC(pwmC - fpw);
  motorD(pwmD - fpw);
}
void motor_off()
{
  motorA(0);
  motorB(0);
  motorC(0);
  motorD(0);
}
void intial_motion()
{       control(270);
        delay(2500);
        control(270+45);
        delay(1000);
        control(0);
        delay(200);
        motor_off();
  }
