int h1=13, h2=11, he=12;

int pwm = 0;
int pwm_herc = 0; 

enum dir { left , right };

void setup()
{
  Serial.begin(9600);     //PC Serial Comm.
  Serial2.begin(9600);    //BT Module
  Serial3.begin(9600);    //Sabertooth
  pinMode(h1, OUTPUT);
  pinMode(h2, OUTPUT);
  pinMode(he, OUTPUT);
}

void start_L(bool rev=false) {
  int x = pwm;
  rev = !rev;
  if (rev) { x = -x; }
  Serial3.write(map(x, -100, 100, 1, 127));
}

void start_R(bool rev=false) {
  int y = pwm;
  rev = !rev;
  if (rev) { y = -y; }
  Serial3.write(map(y, -100, 100, 128, 255));
}

void start_F(dir d) {
  analogWrite(he, map(pwm_herc, 0, 100, 0, 255));
  if (d == left) {
    digitalWrite(h1, HIGH);
    digitalWrite(h2, LOW);
  } else if ( d == right ) {
    digitalWrite(h1, LOW);
    digitalWrite(h2, HIGH);
  }
 
}

void stop_L() {
  Serial3.write(map(0, -100, 100, 1, 127));
}

void stop_R() {
  Serial3.write(map(0, -100, 100, 128, 255));
}

void stop_F() {
  digitalWrite(h1, LOW);
  digitalWrite(h2, LOW);
}

void stop_all() {
  stop_L(); stop_R(); stop_F();
}

void setSpeed(int x) {
  // 0 <= x <= 100
  pwm = x;
  if (x <= 0)
    pwm = 0;
  else if (x >= 20)
    pwm = 20;
  
}

void changePWM(int diff) {
  pwm += diff;
  if (pwm < 0) pwm = 0;
  if (pwm > 50) pwm = 50;
  pwm_herc=map(pwm,0,100,0,18);
  Serial.println(pwm);
}

void turn_L() {
  start_R();
  start_L(true);
  start_F(left);
}

void turn_R() {
  start_L();
  start_R(true);
  start_F(right);
}

int zc = 0;
unsigned long lastPWMChange = 0;

void loop() {
  while (Serial2.available()) {
    char ch = Serial2.read();
 //Serial.println(ch);
    if (!(ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '7' || ch == '9'))
      continue;
//    Serial.println(ch);
    if (ch == '0') {// fwd {
      zc++;
      if (zc == 5) {
         stop_all();
//         Serial.println("braking");
         zc = 0;
      }
    } else {
      zc = 0;
      if (ch == '1') {
//        Serial.println("fwd");
        start_L(); start_R(); stop_F();
      } else if (ch == '2') {
        start_L(true); start_R(true); stop_F();
      } else if (ch == '3') {
//        Serial.println("left");
        start_L(true); start_R(); start_F(left);
      } else if (ch == '4') {
        start_L(); start_R(true); start_F(right);
      } else if (ch == '7') {
        unsigned long curTime = millis();
        if (curTime - lastPWMChange >= 200) {
          changePWM(5);
          lastPWMChange = curTime;
        }
      } else if (ch == '9') {
         unsigned long curTime = millis();
        if (curTime - lastPWMChange >= 200) {
          changePWM(-5);
          lastPWMChange = curTime;
        }
      }
    }
//    delay(50);
  }
}


