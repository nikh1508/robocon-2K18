void loop() {
  if (debug)
  {
    if (update_data()) {
      check_motion();
    }
    print_recv_data();
  }
  else {
    if (update_data()) {
      check_motion();
      updated = true;
      setValue = constrain(setValue, 0, capped_val);
    }
    else updated = false;
    switch (bot_data.motion) {
      case 0:
        if (bot_data.curr_motion != 0 || updated) {
          stop_all();
          bot_data.curr_motion = 0;
        }
        break;
      case 1:
        if (bot_data.curr_motion != 1 || updated) {
          move_fwd();
          bot_data.curr_motion = 1;
        }
        input = get_angle('x');
        pid_obj.myPID.Compute();
        Serial.println("OUT::"+String(output)+"\tSET::"+String(setpoint)+"\tIN:"+String(input));
        pwm_l = setValue + output;
        pwm_l = constrain(pwm_l, -255, 255);
        write_motor(0, pwm_l, pwm_r);
        break;
      case 2:
        if (bot_data.curr_motion != 2 || updated) {
          move_bkwd();
          bot_data.curr_motion = 2;
        }
        input = get_angle('x');
        pid_obj.myPID.Compute();
        Serial.println("OUT::"+String(output)+"\tSET::"+String(setpoint)+"\tIN:"+String(input));
        pwm_l = -setValue + output;
        pwm_l = constrain(pwm_l, -255, 255);
        write_motor(0, pwm_l, pwm_r);
        break;
      case 3:
        if (bot_data.curr_motion != 3 ) {
          move_left();
          bot_data.curr_motion = 3;
        }
        input = get_angle('x');
        pid_obj.myPID.Compute();
        Serial.println("OUT::"+String(output)+"\tSET::"+String(setpoint)+"\tIN:"+String(input));
        pwm_f = -15 + output;
        pwm_f = constrain(pwm_f, -255, 255);
        write_motor(pwm_f, pwm_l, pwm_r);
        Serial.println("--------------------------------------------");
        break;
      case 4:
        if (bot_data.curr_motion != 4 ) {
          move_right();
          bot_data.curr_motion = 4;
        }
        input = get_angle('x');
        pid_obj.myPID.Compute();
        Serial.println("OUT::"+String(output)+"\tSET::"+String(setpoint)+"\tIN:"+String(input));
        pwm_f = 15 + output;
        pwm_f = constrain(pwm_f, -255, 255);
        write_motor(pwm_f, pwm_l, pwm_r);
        Serial.println("--------------------------------------------");
        break;
      case 5:
        if (bot_data.curr_motion != 5 || updated) {
          move_cw();
          bot_data.curr_motion = 5;
        }
        write_motor(pwm_f, pwm_l, pwm_r);
        break;
      case 6:
        if (bot_data.curr_motion != 6 || updated) {
          move_ccw();
          bot_data.curr_motion = 6;
        }
        write_motor(pwm_f, pwm_l, pwm_r);
        break;
      default:
        stop_all();
        break;
    }
  }
}
