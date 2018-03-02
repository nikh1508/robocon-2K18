void manual()
{
  photos();
  Serial.print(dphoto_forw); Serial.print(dphoto_bac); Serial.print("\n");
  if (Serial.available())
  {
    qw = Serial.read();
    f_pwm = Serial.parseInt();
    b_pwm = Serial.parseInt();
    del = Serial.parseInt();
    f_pwm = constrain(f_pwm, 0, 160);
    b_pwm = constrain(f_pwm, 0, 160);
    del = constrain(f_pwm, 0, 5000000);

  }
  if (qw == 's' && dphoto_bac)
  {
    launch_cw(f_pwm);
    Serial.println("Throwing");
  }
  if (dphoto_forw && qw == 's')
  {
    delayMicroseconds(del);//experimnetal
    for (int i = 0; i < 4 ; i++) { //2
      launch_ccw(b_pwm);                              //IF USING 5S BATTERY DONT GIVE MORE THAN 159 PWM ON ANY POINT.........!!!!!!!!!
      delay(20);
      brake_lock();
      Serial.println("Retracting");
    }
    //
    while (!dphoto_bac)
    {
      launch_ccw(8);
      delay(20);
      brake_lock();
      photos();
    }
    brake_free();

    qw = 'o';
  }
}

