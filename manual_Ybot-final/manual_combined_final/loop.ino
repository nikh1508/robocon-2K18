/*
  Bot Motion:
  1-FWD
  2-BKWD
  3-LEFT
  4-RIGHT
  5-CW Rotation
  6-CCW Rotation
  7-DCV
  8-BELT Left
  9-BELT Right
  ----------------------------------
  PNEUMATIC:
  1-DCV
  2-BELT
*/
void loop() {
  if (debug)
  {

    if (update_data()) {
      check_motion();
      check_pneumatic();
    }
    print_recv_data();
  }
  else {
    if (update_data()) {
      check_motion();
      check_pneumatic();
      updated = true;
      setValue = constrain(setValue, 0, capped_val);
    }
    else updated = false;
    switch (bot_data.motion) {
      case 0:
        if (bot_data.curr_motion != 0 || updated) {
          stop_all(bot_data.curr_motion);
          bot_data.curr_motion = 0;
        }
        break;
      case 1:
        if (bot_data.curr_motion != 1 || updated) {
          move_fwd();
          if (bot_data.curr_motion != 1)
            start_time = millis();
          bot_data.curr_motion = 1;
        }
        input = get_angle('x');
        pid_obj.myPID.Compute();
        //        Serial.println("OUT::" + String(output) + "\tSET::" + String(setpoint) + "\tIN:" + String(input));
        set_l = setValue + output;
        set_l = constrain(set_l, -180, 180);
        write_motor(0, set_l, set_r);
        if (yellow_area && !picked_up)
          ysr();
        break;
      case 2:
        if (bot_data.curr_motion != 2 || updated) {
          move_bkwd();
          if (bot_data.curr_motion != 2)
            start_time = millis();
          bot_data.curr_motion = 2;
        }
        input = get_angle('x');
        pid_obj.myPID.Compute();
        //        Serial.println("OUT::" + String(output) + "\tSET::" + String(setpoint) + "\tIN:" + String(input));
        set_l = -setValue + output;
        set_l = constrain(set_l, -180, 180);
        write_motor(0, set_l, set_r);
        break;
      case 3:
        if (bot_data.curr_motion != 3 ) {
          move_left();
          bot_data.curr_motion = 3;
        }
        input = get_angle('x');
        pid_obj.myPID.Compute();
        Serial.println("OUT::" + String(output) + "\tSET::" + String(setpoint) + "\tIN:" + String(input));
        set_f = -15 + output;
        set_f = constrain(set_f, -120, 120);
        write_motor(set_f, set_l, set_r);
        Serial.println("--------------------------------------------");
        break;
      case 4:
        if (bot_data.curr_motion != 4 ) {
          move_right();
          bot_data.curr_motion = 4;
        }
        input = get_angle('x');
        pid_obj.myPID.Compute();
        //        Serial.println("OUT::" + String(output) + "\tSET::" + String(setpoint) + "\tIN:" + String(input));
        set_f = 15 + output;
        set_f = constrain(set_f, -120, 120);
        write_motor(set_f, set_l, set_r);
        //        Serial.println("--------------------------------------------");
        break;
      case 5:
        if (bot_data.curr_motion != 5 || updated) {
          move_cw();
          bot_data.curr_motion = 5;
        }
        write_motor(set_f, set_l, set_r);
        break;
      case 6:
        if (bot_data.curr_motion != 6 || updated) {
          move_ccw();
          bot_data.curr_motion = 6;
        }
        write_motor(set_f, set_l, set_r);
        break;
      default:
        stop_all(0);
        break;
    }
    switch (bot_data.pneumatic) {
      case 0:
        stop_pneumatic();
        break;
      case 1:
        dcv();
        break;
      case 2:
        belt();
        break;
    }
  }
}
