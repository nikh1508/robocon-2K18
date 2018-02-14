void motor1(int pwm) {
  if (motors.m1 == pwm) return; // do nothing

  if (pwm == BRAKE) {
    write_m1("0");
    write_m1("shutdown");
    motors.m1 = BRAKE;
    return;
  }

  pwm = constrain(pwm, -2047, +2047);
  if (motors.m1 == BRAKE) 
    write_m1("startup");

  write_m1(String(pwm));
  motors.m1 = pwm;
} 

void motor2(int pwm) {

  if (pwm == motors.m2) return ;

  if (pwm == BRAKE) { 

//    int diff = motors.m2;
//    int dec = diff/10.0;
//
//    for (int i = 0; i < 10; i++) {
//      analogWrite(MONSTER_PWM, diff - (dec * i));
//      delay(100);
//    }
    
    analogWrite(MONSTER_PWM, 0);
    digitalWrite(MONSTER_L1, HIGH);
    digitalWrite(MONSTER_L2, HIGH);

    motors.m2 = BRAKE;
    return;
  }

  pwm = map(pwm, -2047, +2047, -255, +255);

  if (motors.m2 == BRAKE) {
    if (pwm > 0) {
      digitalWrite(MONSTER_L1, HIGH);
      digitalWrite(MONSTER_L2, LOW);
    } else {
      digitalWrite(MONSTER_L1, LOW);
      digitalWrite(MONSTER_L2, HIGH);
    }
  }

  analogWrite(MONSTER_PWM, pwm);
  Serial.println(pwm);
  motors.m2 = pwm;

}
 

void motor3(int pwm) {
 
  if (motors.m3 == pwm) return; // do nothing

  if (pwm == BRAKE) {
    write_m3("0");
    write_m3("shutdown");
    motors.m3 = BRAKE;
    return;
  }

  pwm = constrain(pwm, -2047, +2047);
  if (motors.m3 == BRAKE) 
    write_m3("startup");

  write_m3(String(pwm));
  motors.m3 = pwm;
}



void write_motors(int f, int l, int r) {
  motor2(f);
  motor3(l);
  motor1(r);
}

void stop_all() {
  write_motors(BRAKE, BRAKE, BRAKE);
}
