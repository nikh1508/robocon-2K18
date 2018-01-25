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

void stop_all() {
  write_motor(0, 0, 0);
}

void move_fwd() {
  if (bot_data.curr_motion != 1) {
    bno.begin();
    delay(50);
    setpoint = get_angle('x');
    output = 0.0;
    redeclare_pid(pid_mat[0][0], pid_mat[0][1], pid_mat[0][2]);
  }
  pwm_l = pwm_r = setValue;
}

void move_bkwd() {
  if (bot_data.curr_motion != 2) {
    bno.begin();
    delay(50);
    setpoint = get_angle('x');
    output = 0.0;
    redeclare_pid(pid_mat[0][0], pid_mat[0][1], pid_mat[0][2]);
    //myPID.SetZero();
    Serial.println("here..");
  }
  pwm_l = pwm_r = -setValue;
}

void move_left() {
  bno.begin();
  delay(50);
  setpoint = get_angle('x');
  output = 0.0;
  redeclare_pid(pid_mat[1][0], pid_mat[1][1], pid_mat[1][2]);
  Serial.println("here..");
  pwm_l = 15;
  pwm_r = -15;
  pwm_f = -15;
}

void move_right() {
  bno.begin();
  delay(50);
  setpoint = get_angle('x');
  output = 0.0;
  redeclare_pid(pid_mat[2][0], pid_mat[2][1], pid_mat[2][2]);
  pwm_l = -15;
  pwm_r = 15;
  pwm_f = 15;
}

void move_cw() {
  pwm_l = setValue;
  pwm_r = -setValue;
  pwm_f = setValue;
}

void move_ccw() {
  if (bot_data.curr_motion != 6) {}
  pwm_l = -setValue;
  pwm_r = setValue;
  pwm_f = -setValue;
}

void write_motor(int f, int x, int y) {
  //Power Controls-----------------------------------------------
  if (bot_data.power == 0)
    f = x = y = 0;
  //-------------------------------------------------------------

  Serial.print("F_PWM::"); Serial.print(f); Serial.print("\t");
  Serial.print("L_PWM::"); Serial.print(x); Serial.print("\t");
  Serial.print("R_PWM::"); Serial.println(y);

  digitalWrite(motor.dir_l, x < 0);
  digitalWrite(motor.dir_r, y < 0);
  if (f == 0)
  {
    digitalWrite(motor.dir_f1, 1);
    digitalWrite(motor.dir_f2, 1);
  }
  else if (f < 0)
  {
    digitalWrite(motor.dir_f1, 0);
    digitalWrite(motor.dir_f2, 1);

  }
  else
  {
    digitalWrite(motor.dir_f1, 1);
    digitalWrite(motor.dir_f2, 0);
  }
  analogWrite(motor.pwm_f, abs(f));
  analogWrite(motor.pwm_l, abs(x));
  analogWrite(motor.pwm_r, abs(y));
}

//--------------------------------------------------------------------------------Pneumatic Functions---------------------------------------------------------------------------------------
void stop_pneumatic() {
  digitalWrite(pneumatic.dcv_l_up, LOW);
  digitalWrite(pneumatic.dcv_l_down, LOW);
  digitalWrite(pneumatic.dcv_r_up, LOW);
  digitalWrite(pneumatic.dcv_r_down, LOW);
  digitalWrite(pneumatic.belt_l_pwm, LOW);
  digitalWrite(pneumatic.belt_r_pwm, LOW);
}

void dcv() {
  if (bot_data.dcv_l == 1) {
    digitalWrite(pneumatic.dcv_l_up, HIGH);
    digitalWrite(pneumatic.dcv_l_down, LOW);
  }
  else if (bot_data.dcv_l == 2) {
    digitalWrite(pneumatic.dcv_l_up, LOW);
    digitalWrite(pneumatic.dcv_l_down, HIGH);
  }

  if (bot_data.dcv_r == 1) {
    digitalWrite(pneumatic.dcv_r_up, HIGH);
    digitalWrite(pneumatic.dcv_r_down, LOW);
  }
  else if (bot_data.dcv_r == 2) {
    digitalWrite(pneumatic.dcv_r_up, LOW);
    digitalWrite(pneumatic.dcv_r_down, HIGH);
  }
}

void belt() {
  if (bot_data.belt_l == 1)
  {
    analogWrite(pneumatic.belt_l_pwm, 80);
    digitalWrite(pneumatic.belt_l_dir1, HIGH);
    digitalWrite(pneumatic.belt_l_dir2, LOW);
  }
  else if (bot_data.belt_l == 2) {
    analogWrite(pneumatic.belt_l_pwm, 80);
    digitalWrite(pneumatic.belt_l_dir1, LOW);
    digitalWrite(pneumatic.belt_l_dir2, HIGH);
  }
  else if (bot_data.belt_r == 1) {
    analogWrite(pneumatic.belt_r_pwm, 120);
    digitalWrite(pneumatic.belt_r_dir1, HIGH);
    digitalWrite(pneumatic.belt_r_dir2, LOW);
  }

  else if (bot_data.belt_r == 2) {
    analogWrite(pneumatic.belt_r_pwm, 120);
    digitalWrite(pneumatic.belt_r_dir1, LOW);
    digitalWrite(pneumatic.belt_r_dir2, HIGH);
  }
}
