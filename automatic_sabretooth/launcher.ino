void launch_ccw(int spd) {
  digitalWrite(LAUNCHER_L1, 0);
  digitalWrite(LAUNCHER_L2, 1);
  analogWrite(LAUNCHER_PWM, spd);
}

void launch_cw(int spd) {
  digitalWrite(LAUNCHER_L1, 1);
  digitalWrite(LAUNCHER_L2, 0);
  analogWrite(LAUNCHER_PWM, spd);
}

void brake_free() {
  digitalWrite(LAUNCHER_L1, 0);
  digitalWrite(LAUNCHER_L2, 0);
  analogWrite(LAUNCHER_PWM, 0);
}

void brake_lock() {
  digitalWrite(LAUNCHER_L1, 1);
  digitalWrite(LAUNCHER_L2, 1);
  analogWrite(LAUNCHER_PWM,
              180);  // IF USING 5S BATTERY DONT GIVE MORE THAN 160 PWM ON
                     // ANY POINT.........!!!!!!!!!
}

void photos() {
  dphoto_forw = digitalRead(photo_forw);
  dphoto_bac = digitalRead(photo_bac);
}

void launch(int i) {
  digitalWrite(LED, 0);
  photos();
  if (dphoto_bac) {
    launch_cw(fwm[i - 1]);
  }

  while (flag_test) {
    photos();
    if (dphoto_forw) {
      delayMicroseconds(del[i - 1]);
      for (int i = 0; i < 4; i++) {
        launch_ccw(bwm[i - 1]);
        delay(20);
        brake_lock();
      }
    }

    while (!dphoto_bac) {
      launch_ccw(10);
      delay(20);
      brake_lock();
      photos();
    }

    flag_test = false;
  }

  tz = LOW;
  load = LOW;
  dphoto_forw = LOW;
  flag_test = true;
}
//////////////////
/////////////////

