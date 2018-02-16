void write_m1(String cmd) {
  Serial1.print("M1: " + cmd + "\r\n");
}

void write_m2(String cmd) {
  Serial2.print("M1: " + cmd + "\r\n");
}

void write_m3(String cmd) {
  Serial1.print("M2: " + cmd + "\r\n");
}

void ramp1(int r) {
  Serial1.print("R1: " + String(r) + "\r\n");
}



void ramp3(int r) {
  Serial1.print("R2: " + String(r) + "\r\n");
}

double get_yaw() {
  sensors_event_t event;
  bno.getEvent(&event);
  double x = event.orientation.x;
  if (x > 180)                     // to get negative angles in CCW direction
    x = (360 - x) * -1;
  if (x == 0.0625 || x == -0.0625)
    x = 0.0;
  return x;
}

void mkpid(double kp, double ki, double kd) {
  myPID = PID(&input, &output, &setpoint, kp, ki, kd, DIRECT);
  myPID.SetMode(1);
  myPID.SetOutputLimits(-500, +500);
}

void debug() {
  Serial.print(motors.m1);
  Serial.print(" ");
  Serial.print(motors.m2);
  Serial.print(" ");
  Serial.print(motors.m3);
  Serial.print("\t|\t");
  Serial.print(input);
  Serial.print(" ");
  Serial.print(output);
  Serial.println();
}

void bno_reset() {
  digitalWrite(bno_rst_pin, LOW);
  digitalWrite(bno_rst_pin, HIGH);
  bno.begin();
}
void isr() {
  ctr++;
}

void isr2() {
  long long val = millis();
  if ((val - last_time) >= 300) {
    ctr2++;
    last_time = val;
  }
}


void isr3() {
  ctr3++;
}


double get_yaw2() {
  sensors_event_t event;
  bno.getEvent(&event);
  double x = event.orientation.x;
  // taking X readings
  if (x == 0.0625 || x == 359.9375)
    x = 0.0;
  return x;
}

void print_error() {
  Serial.println(last_error);
  while (!Serial.available())
    char ch = Serial.read();
}
