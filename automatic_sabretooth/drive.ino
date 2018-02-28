void motor1(int pwm) {
  if (pwm == BRAKE) {
    write_m1("0");
    // write_m1("shutdown");
    return;
  }
  pwm = constrain(pwm, -2047, +2047);
  write_m1(String(pwm));
}

void motor2(int pwm) {
  if (pwm == BRAKE) {
    digitalWrite(MONSTER_L1, HIGH);
    digitalWrite(MONSTER_L2, HIGH);
    analogWrite(MONSTER_PWM, 0);
    return;
  }
  pwm = constrain(pwm, -255, +255);
  if (pwm == 0) {
    digitalWrite(MONSTER_L1, LOW);
    digitalWrite(MONSTER_L2, LOW);
  } else if (pwm > 0) {
    digitalWrite(MONSTER_L1, HIGH);
    digitalWrite(MONSTER_L2, LOW);
  } else {
    digitalWrite(MONSTER_L1, LOW);
    digitalWrite(MONSTER_L2, HIGH);
  }
  analogWrite(MONSTER_PWM, abs(pwm));
}

void motor3(int pwm) {
  if (pwm == BRAKE) {
    write_m3("0");
    return;
  }
  pwm = constrain(pwm, -2047, +2047);
  write_m3(String(pwm));
}

void write_motors(int f, int l, int r) {
  motor2(f);
  motor3(l);
  motor1(r);
}

void stop_all() {
  ramp1(0);
  ramp2(0);
  write_motors(BRAKE, BRAKE, BRAKE);
}
