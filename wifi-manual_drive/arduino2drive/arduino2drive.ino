#include <SoftwareSerial.h>

#define accel bot_data.y
#define turn bot_data.x

SoftwareSerial bot(A0, A1); //RX,TX

constexpr int M1_PWM = 11;
constexpr int M1_DIR = 13;
constexpr int M2_PWM = 10;
constexpr int M2_DIR = 12;

int nodata_count = 0;

struct data {
  int x, y, slider, power, t;
} bot_data;

struct motors {
  int pwm1, pwm2, dir1, dir2;
} motor_data;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  bot.begin(9600);
}

byte read() {
  while (!bot.available()) {}
  return bot.read();
}

void disp() {
  Serial.print("X="); Serial.print(bot_data.x); Serial.print(",");
  Serial.print("Y="); Serial.print(bot_data.y); Serial.print(",");
  Serial.print("L="); Serial.print(bot_data.slider); Serial.print(",");
  Serial.print("P="); Serial.print(bot_data.power); Serial.print(",");
  Serial.print("T="); Serial.print(bot_data.t); Serial.println();
}

bool update_data() {
  bool didchange = false;
  if (read() == 's') {

    byte type = read();
    if (!(type == 'x' || type == 'y' || type == 'l' || type == 'p' || type == 't')) return didchange;
    byte val = read();

    switch (type) {
      case 'x':
        if (bot_data.x != val) didchange = true;
        bot_data.x = val;
        break;
      case 'y':
        if (bot_data.y != val) didchange = true;
        bot_data.y = val;
        break;
      case 'l':
        if (bot_data.slider != val) didchange = true;
        bot_data.slider = val;
        break;
      case 'p':
        if (bot_data.power != val) didchange = true;
        bot_data.power = val;
        break;
      case 't':
        if (bot_data.t != val) didchange = true;
        bot_data.t = val;
        break;
    }
    return didchange;
  }
  return didchange;
}

void calc() {
  int L, R;



  L = map(bot_data.y, 0, 255, -bot_data.slider, +bot_data.slider);
  R = L;

  if (bot_data.y == 128) {
    L = R = 0;
  }

  //  Serial.print("L="); Serial.print(L); Serial.print(" ");
  //  Serial.print("R="); Serial.println(R);
  //

  if (bot_data.t < 127) {
    int percent = map(bot_data.t, 0, 128, 0, 100);
    L = (percent * L) / 100.0;
  } else if (bot_data.t > 127) {
    int percent = map(bot_data.t, 128, 255, 100, 0);
    R = (percent * R) / 100.0;
  }

  if (bot_data.x <= 64) {
    L = map(turn, 0, 64, -L, 0);
  } else if (turn <= 128) {
    L = map(turn, 64, 128, 0, L);
  } else if (turn <= 192) {
    R = map(turn, 128, 192, R, 0);
  } else {
    R = map(turn, 192, 255, 0, -R);
  }




  //    Serial.print("L="); Serial.print(L); Serial.print(" ");
  //  Serial.print("R="); Serial.println(R);

  update_L(L);
  update_R(R);
}

void update_L(int pwm) {
  int dir = (pwm < 0) ? LOW : HIGH;
  pwm = abs(pwm);

  digitalWrite(M1_DIR, dir);
  analogWrite(M1_PWM, abs(pwm));
  motor_data.pwm1 = pwm;
  motor_data.dir1 = dir;

}

void disp_motor() {
  int pwm1 = motor_data.pwm1;
  if (motor_data.dir1 == LOW) pwm1 = -pwm1;
  int pwm2 = motor_data.pwm2;
  if (motor_data.dir2 == LOW) pwm2 = -pwm2;
  Serial.print(pwm1);
  Serial.print(" ");
  Serial.print(pwm2);
  Serial.println();
}

void update_R(int pwm) {
  int dir = (pwm > 0) ? LOW : HIGH;                       
  pwm = abs(pwm);

  digitalWrite(M2_DIR, dir);
  analogWrite(M2_PWM, abs(pwm));
  motor_data.pwm2 = pwm;
  motor_data.dir2 = dir;

}
void motors_shutdown() {
  update_L(0);
  update_R(0);
}
void loop() {

  if (nodata_count > 5000)
  {
    bot_data.power = 0;
    motors_shutdown();
    Serial.println("Arduino is disconnected via Serial. Check Connection");
    while (!bot.available());
  }

  update_data();
  if (bot_data.power)calc();
  else motors_shutdown();
  //disp_motor();
}


