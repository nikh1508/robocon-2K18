void write_m1(String cmd) {
  Serial2.print("M1: " + cmd + "\r\n");
  //  Serial.println("M1:" + cmd);
}


void write_m3(String cmd) {
  Serial2.print("M2: " + cmd + "\r\n");
  //  Serial.println("M3:" + cmd);
}

void ramp1(int r) {
  Serial2.print("R1: " + String(r) + "\r\n");
}

void ramp2(int r) {
  Serial2.print("R2: " + String(r) + "\r\n");
}

//double get_yaw() {
////  long long curt = millis();
////  if (bno_last_time == -1 || ((curt - bno_last_time) >= 10)) {
//    sensors_event_t event;
//    bno.getEvent(&event);
//    double x = event.orientation.x;
//    //  if (x > 180)
//    //    x = (360 - x) * -1;
//    if (x == 0.0625 || x == -0.0625)
//      x = 0.0;
////    bno_last_time = curt;
////    bno_last_val = x;
//    Serial.println(x);
//    return x;
////  } else {
////    return bno_last_val;
////  }
//}

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

//double adiff(double a, double b)
//{
//    double diff = fabs(b - a);
//    double err = min(diff, 360 - diff);
//    double tmp = a + err;
//    if (tmp >= 360) tmp -= 360;
//
//    if (fabs(tmp - b) <= 1e-2) 
//        return +err;
//    else
//        return -err;
//}

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

long long enc_time=millis();
long enc_last=0;

long encoder() {
  if((millis()-enc_time)>ENCODER_SAMPLE_TIME){
  Serial1.print('k');
  long S = 0;
  int neg=-1;
  while (Serial1.available()) {
    int val = Serial1.read();
    if (val=='-'){
      neg=+1;
      continue;
      }
    S += (val - 48) * pow(10, Serial1.available());
  }  
  enc_last= S*neg;
  enc_time=millis();
  return enc_last;
  }
  else return enc_last;
}

void reset_encoder() {
  Serial1.print('u');
  Serial1.flush();
  while(Serial1.available())
  char ch=Serial1.read();
}

void bno_initialize() {
  Wire.beginTransmission(adr);
  Wire.write(0x3D);
  Wire.write(0x0C);
  Wire.endTransmission();
  delay(10);
  ////////////////
  for (int i = 0; i < 50; i++) {
    Wire.beginTransmission(adr);
    Wire.write(0x1A);
    Wire.endTransmission();
    Wire.requestFrom(adr, 2);
    lsb_yaw = Wire.read();
    msb_yaw = Wire.read();
    yaw_offset = yaw_offset + (((((int)msb_yaw) << 8) | lsb_yaw));
  }
  yaw_offset /= 800;
  Serial.println(yaw_offset);
  delay(50);
}

double get_yaw() {
  Wire.beginTransmission(adr);
  Wire.write(0x1A);
  Wire.endTransmission();
  Wire.requestFrom(adr, 2);
  lsb_yaw = Wire.read();
  msb_yaw = Wire.read();
  yaw = (((((int)msb_yaw) << 8) | lsb_yaw));
  yaw /= 16;
  yaw = yaw - yaw_offset;
  if (yaw < 0) yaw += 360;
  Serial.println(yaw);
  return yaw;

  //  Serial.print("yaw=");
  //  Serial.println(yaw);
}






