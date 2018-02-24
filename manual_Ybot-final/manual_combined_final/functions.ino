
double get_angle(char axis) {
  sensors_event_t event;
  bno.getEvent(&event);
  double x = event.orientation.x; // taking X readings
  double y = event.orientation.y;
  double z = event.orientation.z;
  if (x > 180)                  //to get negative angles in CCW direction
    x = (360 - x) * -1;
  switch (axis) {
    case 'x':
      return x;
      break;
    case 'y':
      return y;
      break;
    case 'z':
      return z;
      break;
    default:
      return 0;
  }
}

void check_motion() {
  if (!(bot_data.fwd || bot_data.bkd || bot_data.left || bot_data.right || bot_data.cw || bot_data.ccw ))
    bot_data.motion = 0;
}

void check_pneumatic() {
  if (!(bot_data.belt_l || bot_data.belt_r || bot_data.dcv_l || bot_data.dcv_r))
    bot_data.pneumatic = 0;
}

void redeclare_pid(double Kp, double Ki, double Kd) {
  pid_obj.myPID = PID(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);
  pid_obj.myPID.SetOutputLimits(-255, 255);
  pid_obj.myPID.SetMode(AUTOMATIC);
}
//----------------------------------------------------------------------Motor Functions--------------------------------------------------------------------------

void stop_all(int x) {

  unsigned long curr_time = millis() - start_time;
  switch (x) {
    case 0:
      write_motor(0, 0, 0);
      break;
    case 1:
      for (int i = 0; i <= setValue; i++) {
        write_motor(0, -i - (i / 2), -i);
        delay(4);
      }
      if (curr_time > 800)
        delay(400);
      write_motor(0, 0, 0);
      //      while(set_l>0 || set_r>0){
      //        set_l-=set_l*deacc;
      //        set_l=constrain(set_l,0,255);
      //        set_r-=set_r*deacc;
      //        set_r=constrain(set_r,0,255);
      //        write_motor(0,set_l,set_r);
      //        }
      //      Serial.print(start_time);
      //      Serial.print("\t");
      //      Serial.print(millis());
      //      Serial.print("\t");
      //      Serial.println(curr_time);
      write_motor(0, 0, 0);
      break;
    case 2:
      for (int i = 0; i <= setValue; i++) {
        write_motor(0, i + (i / 2), i);
        delay(4);
      }
      //      Serial.print(start_time);
      //      Serial.print("\t");
      //      Serial.print(millis());
      //      Serial.print("\t");
      //      Serial.println(curr_time);
      if (curr_time > 800)
        delay(400);
      write_motor(0, 0, 0);
      break;
    case 3:
      write_motor(5, -7, 4);
      delay(400);
      write_motor(0, 0, 0);
      break;
    case 4:
      write_motor(-5, 7, -4);
      delay(400);
      write_motor(0, 0, 0);
      break;
    default:
      write_motor(0, 0, 0);
      break;
  }
}

void move_fwd() {
  if (bot_data.curr_motion != 1) {
    bno.begin();
    delay(50);
    start_time = millis();
    setpoint = get_angle('x');
    output = 0.0;
    redeclare_pid(pid_mat[0][0], pid_mat[0][1], pid_mat[0][2]);
  }
  set_l = set_r = setValue;
}

void move_bkwd() {
  if (bot_data.curr_motion != 2) {
    bno.begin();
    delay(50);
    start_time = millis();
    setpoint = get_angle('x');
    output = 0.0;
    redeclare_pid(pid_mat[0][0], pid_mat[0][1], pid_mat[0][2]);
    //myPID.SetZero();
    //    Serial.println("here..");
  }
  set_l = set_r = -setValue;
}

void move_left() {
  bno.begin();
  delay(50);
  setpoint = get_angle('x');
  output = 0.0;
  redeclare_pid(pid_mat[1][0], pid_mat[1][1], pid_mat[1][2]);
  //  Serial.println("here..");
  set_l = 25;
  set_r = -15;
  set_f = 0;
}

void move_right() {
  bno.begin();
  delay(50);
  setpoint = get_angle('x');
  output = 0.0;
  redeclare_pid(pid_mat[2][0], pid_mat[2][1], pid_mat[2][2]);
  set_l = -25;
  set_r = 20;
  set_f = 0;
}

void move_cw() {
  set_l = 15;
  set_r = -15;
  set_f = 15;
}

void move_ccw() {
  if (bot_data.curr_motion != 6) {}
  set_l = -15;
  set_r = 15;
  set_f = -15;
}

void write_motor(int f, int x, int y) {
  //Power Controls-----------------------------------------------
  if (bot_data.power == 0)
    f = x = y = 0;
  //-------------------------------------------------------------

  Serial.print("F_PWM::"); Serial.print(f); Serial.print("\t");
  Serial.print("L_PWM::"); Serial.print(x); Serial.print("\t");
  Serial.print("R_PWM::"); Serial.println(y);

  digitalWrite(dir_l, x < 0);
  digitalWrite(dir_r, y < 0);
  if (f == 0)
  {
    digitalWrite(dir_f1, 1);
    digitalWrite(dir_f2, 1);
  }
  digitalWrite(dir_f1, f > 0);
  digitalWrite(dir_f2, f < 0);
  //
  analogWrite(pwm_f, abs(f));
  analogWrite(pwm_l, abs(x));
  analogWrite(pwm_r, abs(y));
}

//--------------------------------------------------------------------------------Pneumatic Functions---------------------------------------------------------------------------------------
void stop_pneumatic() {
  digitalWrite(dcv_l_up, LOW);
  digitalWrite(dcv_l_down, LOW);
  digitalWrite(dcv_r_up, LOW);
  digitalWrite(dcv_r_down, LOW);
  digitalWrite(belt_l_pwm, LOW);
  digitalWrite(belt_r_pwm, LOW);
}

void dcv() {
  if (bot_data.dcv_l == 1) {
    digitalWrite(dcv_l_up, HIGH);
    digitalWrite(dcv_l_down, LOW);
  }
  else if (bot_data.dcv_l == 2) {
    digitalWrite(dcv_l_up, LOW);
    digitalWrite(dcv_l_down, HIGH);
  }

  if (bot_data.dcv_r == 1) {
    digitalWrite(dcv_r_up, HIGH);
    digitalWrite(dcv_r_down, LOW);
  }
  else if (bot_data.dcv_r == 2) {
    digitalWrite(dcv_r_up, LOW);
    digitalWrite(dcv_r_down, HIGH);
  }
}

void belt() {
  if (bot_data.belt_l == 1)
  {
    analogWrite(belt_l_pwm, 100);
    digitalWrite(belt_l_dir1, HIGH);
    digitalWrite(belt_l_dir2, LOW);
  }
  else if (bot_data.belt_l == 2) {
    analogWrite(belt_l_pwm, 100);
    digitalWrite(belt_l_dir1, LOW);
    digitalWrite(belt_l_dir2, HIGH);
  }
  else if (bot_data.belt_r == 1) {
    analogWrite(belt_r_pwm, 120);
    digitalWrite(belt_r_dir1, HIGH);
    digitalWrite(belt_r_dir2, LOW);
  }

  else if (bot_data.belt_r == 2) {
    analogWrite(belt_r_pwm, 120);
    digitalWrite(belt_r_dir1, LOW);
    digitalWrite(belt_r_dir2, HIGH);
  }
}

int flag = 0;
bool yellow_area = false;
void isr()
{
  yellow_area = true;
  detachInterrupt(0);
}

void ysr() {
  int ctr = 0;
  for (int i = 0; i < 20; i++)
    if (digitalRead(2))
      ctr++;
  if (ctr == 20)
    flag++;
  if (flag == 2) {
    int ctr = 0;
    for (int i = 0; i <= setValue; i++) {
      write_motor(0, -i , -i);
      delay(5);
    }
    delay(200);
    write_motor(0, 0, 0);
    while (bot_data.fwd != 0) {
      update_data();
      Serial.print("In loop:");
      Serial.println(bot_data.fwd);
    }
    bot_data.motion = 0;
    bot_data.curr_motion = 0;
    yellow_area = false;
    flag = 0;
    picked_up = true;
  }
}

