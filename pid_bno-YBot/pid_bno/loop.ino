bool prev_off = false;
void loop() {
  //   put your main code here, to run repeatedly:
  if (update_data()) {
    setValue = constrain(setValue, 0, 70);
    pwm_l = pwm_r = setValue;
  }
  if (bot_data.power == 0)
  {
    pwm_l = 0;
    pwm_r = 0;
    prev_off = true;
  }

  else {
    if (prev_off) {
      bno.begin();
      //      setpoint = get_angle('x');
      prev_off = false;
    }
    input = get_angle('x');
    myPID.Compute();
    //dir-fwd
    //    if (setpoint - input > 0) {
    //      pwm_l = setValue + output;
    //      pwm_l = constrain(pwm_l, -255, 255);
    //    }
    //    else {
    //      pwm_l = setValue + output;
    //      pwm_l = constrain(pwm_l, 0, 255);
    //    }
    //dir-rev
    if (setpoint - input > 0) {
      pwm_l = setValue - output;
      pwm_l = constrain(pwm_l, 0, 255);
    }
    else {
      pwm_l = setValue - output;
      pwm_l = constrain(pwm_l, 0, 255);
    }
  }
  write_motor(pwm_l, pwm_r);
  Serial.println(get_angle('x'));
  Serial.print("L_PWM::"); Serial.print(pwm_l); Serial.print("\t");
  Serial.print("R_PWM::"); Serial.println(pwm_r);
  Serial.println(String("OUT::") + String(output));
  Serial.println("------------------------------------------------------");

}
