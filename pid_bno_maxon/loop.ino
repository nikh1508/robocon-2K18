bool prev_off = false;
void loop() {
  if (white_line)
    wsr();
  Serial.print(get_angle('x'));
  Serial.print("\t");
  //   put your main code here, to run repeatedly:
  if (update_data()) {
    //setValue = constrain(setValue, 0, 255);
    pwm_l = pwm_r = setValue;

  }
  if (bot_data.power == 0)
  {
    pwm_l = 0;
    pwm_r = 0;
    if (!prev_off)
      ramp_brake(0.06);
    prev_off = true;
  }

  else if (bot_data.power == 1) {
    if (prev_off) {
      if (!bno.begin())
      {
        Serial.println("BNO Disconnected!!!");
        while (!bno.begin());
        Serial.println("BNO Connected.");
      }
      setpoint = get_angle('x');
      Serial.println("here...");
      ramp_start(0.07);
      prev_off = false;
    }
    input = get_angle('x');
    //    Serial.print(0);
    //    Serial.print(" ");
    myPID.Compute();
    //dir-fwd
    //if (setpoint - input > 0) {
    pwm_l = setValue + output;
    pwm_l = constrain(pwm_l, -2047, 2047);
    //        }
    //        else {
    //          pwm_l = setValue + output;
    //          pwm_l = constrain(pwm_l, 0, 255);
    //        }
    //dir-rev
    //    if (setpoint - input > 0) {
    //      pwm_l = setValue - output;
    //      pwm_l = constrain(pwm_l, 0, 255);
    //    }
    //    else {
    //      pwm_l = setValue - output;
    //      pwm_l = constrain(pwm_l, 0, 255);
    //    }
  }
  write_motor(pwm_l, pwm_r);
  //Serial.println(get_angle('x'));
  Serial.print(String(Kp) + "\t");
  Serial.print(String("OUT::") + String(output) + "\t");
  //  Serial.println("------------------------------------------------------");

}
