enum direction { FWD, BACK };

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
  Serial3.begin(9600);
  pinMode(29, OUTPUT);
  pinMode(31, OUTPUT);
}

//void moveX(dirction d, eint pwm) {
//  if (d == FWD) {
//    int x = map(pwm, 0, 100, 64, 127);
//    int y = map(pwm, 0, 100, 192, 128);
//    Serial3.write(x);
//    Serial3.write(y);
//  } else {
//    int x = map(pwm, 0, 100, 0, 63);
//    int y = map(pwm, 0, 100, );
//    Serial
//  }
//
//}
//
void moveX(int pwm) {
  int x = map(pwm, -100, 100, 1, 127);
  int y = map(pwm, -100, 100, 128, 255);
  digitalWrite(29, LOW);
  digitalWrite(31, LOW);
  Serial3.write(x);
  Serial3.write(y);
}

void stop(){
  Serial2.write(0);
  Serial3.write(0);
}

void moveY(int pwm) {
  int x = map(pwm, -100, 100, 1, 127);
  int y = map(pwm, -100, 100, 128, 255);
  diigtalWrite(29, HIGH);
  digitalWrite(31, HIGH);;
  Serial3.write(x);
  Serial3.write(y);
}

void loop() {
//  while (Serial.available()) {
//    int s = Serial.parseInt();
//    int m = Serial.parseInt();
//    Serial.print(s);
//    Serial.print(" ");
//    Serial.println(m);
//    
//    if (s == 1)
//      moveX(m);
//    else if (s == 2)
//      moveY(m);
//  }

    stop();
    moveY(100);
    delay(2000);
    stop();
    while (1) {}
    while (Serial.available()) {
//      moveX(0);
//    stop();
      char c = Serial.read();
      if (c == 's') {
        Serial.println("moving");
        moveY(10);
//        moveX(0);
        delay(1000);
        stop();
      }      
    }
}
