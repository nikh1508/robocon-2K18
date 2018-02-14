# 1 "/Users/rishav/Documents/Arduino/automatic_sabretooth/automatic_sabretooth.ino"
# 1 "/Users/rishav/Documents/Arduino/automatic_sabretooth/automatic_sabretooth.ino"
# 2 "/Users/rishav/Documents/Arduino/automatic_sabretooth/automatic_sabretooth.ino" 2
# 3 "/Users/rishav/Documents/Arduino/automatic_sabretooth/automatic_sabretooth.ino" 2
# 4 "/Users/rishav/Documents/Arduino/automatic_sabretooth/automatic_sabretooth.ino" 2

# 6 "/Users/rishav/Documents/Arduino/automatic_sabretooth/automatic_sabretooth.ino" 2
# 7 "/Users/rishav/Documents/Arduino/automatic_sabretooth/automatic_sabretooth.ino" 2
# 8 "/Users/rishav/Documents/Arduino/automatic_sabretooth/automatic_sabretooth.ino" 2

constexpr double kp = 50;
constexpr double kd = 0;
constexpr double ki = 0;
constexpr int BRAKE = (-32767 - 1);

double setpoint = 0.0;
double input = 0.0;
double output = 0.0;

struct motors {
  int m1 = BRAKE, m2 = BRAKE, m3 = BRAKE;
} motors;

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x29);
PID myPID = PID(&input, &output, &setpoint,
              kp, ki, kd);

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);

  write_motors(BRAKE, BRAKE, BRAKE);
}

void loop() {

  forward(500, 2000);
  while (1) {};


}
# 1 "/Users/rishav/Documents/Arduino/automatic_sabretooth/drive.ino"
void motor1(int pwm) {
  pwm = ((pwm)<(-2047)?(-2047):((pwm)>(+2047)?(+2047):(pwm)));
  if (motors.m1 == pwm) return; // do nothing

  if (pwm == BRAKE) {
    write_m1("0");
    write_m1("shutdown");
    motors.m1 = BRAKE;
    return;
  }

  if (motors.m1 == BRAKE)
    write_m1("startup");

  write_m1(String(pwm));
  motors.m1 = pwm;
}

void motor1(int pwm) {
  pwm = ((pwm)<(-2047)?(-2047):((pwm)>(+2047)?(+2047):(pwm)));
  if (motors.m2 == pwm) return; // do nothing

  if (pwm == BRAKE) {
    write_m2("0");
    write_m2("shutdown");
    motors.m2 = BRAKE;
    return;
  }

  if (motors.m2 == BRAKE)
    write_m2("startup");

  write_m2(String(pwm));
  motors.m2 = pwm;
}

void motor3(int pwm) {
  pwm = ((pwm)<(-2047)?(-2047):((pwm)>(+2047)?(+2047):(pwm)));
  if (motors.m3 == pwm) return; // do nothing

  if (pwm == BRAKE) {
    write_m3("0");
    write_m3("shutdown");
    motors.m3 = BRAKE;
    return;
  }

  if (motors.m3 == BRAKE)
    write_m3("startup");

  write_m3(String(pwm));
  motors.m3 = pwm;
}

void write_motors(int f, int l, int r) {
  motor3(f);
  motor1(l);
  motor2(r);
}

void stop_all() {
  write_motors(BRAKE, BRAKE, BRAKE)
}
# 1 "/Users/rishav/Documents/Arduino/automatic_sabretooth/misc.ino"
void write_m1(String cmd) {
  Serial1.print("M1: " + cmd + "\r\n");
}

void write_m2(String cmd) {
  Serial2.print("M1: " + cmd + "\r\n");
}

void write_m3(String cmd) {
  Serial1.print("M2: " + cmd + "\r\n");
}

double get_yaw() {
  sensors_event_t event;
  bno.getEvent(&event);
  double x = event.orientation.x; // taking X readings
  if (x > 180) //to get negative angles in CCW direction
    x = (360 - x) * -1;
  return x;
}

void mkpid(double kp, double ki, double kd) {
  myPID = PID(&input, &output, &setpoint,
              kp, ki, kd);
  myPID.SetMode(1);
  myPID.SetOutputLimits(-500, +500);
}
# 1 "/Users/rishav/Documents/Arduino/automatic_sabretooth/movements.ino"
void forward(int speed, int time) {
  bno.begin();
  delay(50);
  setpoint = get_yaw();
  input = setpoint;
  mkpid(kp, ki, kd);
  myPID.setMode(1);
  myPID.SetOutputLimits(-500, +500);

  long long start_time = millis();
  while ((millis() - start_time) <= time) {
    motor3(output);
    motor1(speed);
    motor2(speed);

    input = get_yaw();
    myPID.compute();
  }

  stop_all();
}

void left(int speed, int time) {
    bno.begin();
    delay(50);
    setpoint = get_yaw();
    input = setpoint;
    mkpid(kp, ki, kd);


    long long start_time = millis();
    while ((millis() - start_time) <= time) {
        write_motor(speed + output, +speed, -speed);
        input = get_yaw();
        myPID.compute();
    }

    stop_all();
}

void right(int speed, int time) {
    bno.begin();
    delay(50);
    setpoint = get_yaw();
    input = setpoint;
    mkpid(kp, ki, kd);

    long long start_time = millis();
    while ((millis() - start_time) <= time) {
        write_motor(-(speed + output), -speed, +speed);

        input = get_yaw();
        myPID.compute();
    }

    stop_all();
}

void back(int speed, int time) {

    bno.begin();
    delay(50);
    setpoint = get_yaw();
    input = setpoint;
    mkpid();

    long long start_time = millis();
    while ((millis() - start_time) <= time) {
        write_motor(output, -speed, -speed);
        input = get_yaw();
        myPID.compute();
    }

    stop_all();
}
