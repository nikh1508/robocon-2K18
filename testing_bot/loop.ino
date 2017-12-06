void loop() {
  if (debug) call_debug();
  else {
    if (!ini) {
      Setpoint = get_angle('x');
      ini = !ini;
    }
    Input = get_angle('x');
    pid.Compute();
    while (bt.available()) {
      char ch = bt.read();
      if (!(ch == '0' || ch == '1' || ch == '2' || ch == '7' || ch == '9'))
        continue;
      Serial.println(ch);
      if (ch == '0' && last_func != 0) {
        zc++;
        if (zc == 5) {
          stop_motors(3);
          //Serial.println("Stopping Motors...");
          zc = 0;
          last_func = 0;
        }
      }
      else
      {
        zc = 0;
        op = int(Output);
        if (ch == '1' && last_func != 1) {
          move_motors(pwm1, 1);
          move_motors(pwm2 + op, 2);
          //Serial.println("Moving Forward...");
        }
        else if (ch == '2') {
          move_motors(-1 * pwm1, 1);
          move_motors(-1 * pwm2 + op, 2);
          //Serial.println("Moving Backward...");
          last_func = 1;
        }

      }
    }
  Serial.println("Error="+String(error));
  Serial.println("Input="+String(Input));
  Serial.println("PWM1= "+String(pwm1)+"/tPWM2="+String(pwm2));
  }

}



