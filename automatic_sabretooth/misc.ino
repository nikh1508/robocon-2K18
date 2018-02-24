void write_m1(String cmd) {
  Serial1.print("M1: " + cmd + "\r\n");
  //  Serial.println("M1:" + cmd);
}

void write_m2(String cmd) {
  Serial2.print("M1: " + cmd + "\r\n");
}

void write_m3(String cmd) {
  Serial1.print("M2: " + cmd + "\r\n");
  //  Serial.println("M3:" + cmd);
}

void ramp1(int r) {
  Serial1.print("R1: " + String(r) + "\r\n");
}



void ramp2(int r) {
  Serial1.print("R2: " + String(r) + "\r\n");
}

double get_yaw() {
  long long curt = millis();
  if (bno_last_time == -1 || ((curt - bno_last_time) >= 10)) {
    sensors_event_t event;
    bno.getEvent(&event);
    double x = event.orientation.x;
    //  if (x > 180)
    //    x = (360 - x) * -1;
    if (x == 0.0625 || x == -0.0625)
      x = 0.0;
    bno_last_time = curt;
    bno_last_val = x;
    return x;
  } else {
    return bno_last_val;
  }
}

void mkpid(double kp, double ki, double kd) {
  myPID = PID(&input, &output, &setpoint, kp, ki, kd, DIRECT);
  myPID.SetMode(1);
  myPID.SetOutputLimits(-500, +500);
}



void isr2() {
  if (ctr1flag) {
    long long m = millis();
    if (m - last_time >= 500) {
      ctr1++;
      last_time = m;
    }
  }
}

void print_error() {
//  Serial.println(last_error);
  while (!Serial.available())
    char ch = Serial.read();
}

double angle_diff(double a, double b) {
  double r = fabs(a - b);
  return min(r, 360 - r);
}

double line() {

  unsigned char data[16];
  unsigned char t;
  Wire.requestFrom(9, 16);    // request 16 bytes from slave device #9
  while (Wire.available())   // slave may send less than requested
  {
    data[t] = Wire.read(); // receive a byte as character
    if (t < 15)
      t++;
    else
      t = 0;
  }

  double f = 0;

  for (int i = 0; i <= 14; i += 2)
    f += data[i];

  f /= 8.0;

  Serial.println("[line] " + String(f));
  return f;
}




