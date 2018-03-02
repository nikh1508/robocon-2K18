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
  dphoto_forw = !digitalRead(photo_forw);
  dphoto_bac = digitalRead(photo_bac);
  //  Serial.print("[photos:] ");
  //  Serial.print(dphoto_forw);
  //  Serial.print(dphoto_bac
}

void launch(int i) {
  delay(1000);
  //  digitalWrite(99, 0);
  photos();
  digitalWrite(8, HIGH);
   digitalWrite(9, HIGH);
  if (dphoto_bac) {
    launch_cw(fwm[i - 1]);
  }

  while (flag_test) {
    photos();
    if (dphoto_forw) {
      Serial.println("jerk");
      delayMicroseconds(del[i - 1]);
      for (int j = 0; j < 4; j++) {
        launch_ccw(bwm[i - 1]);
        delay(20);
        brake_lock();
      }

      while (dphoto_bac == LOW) {
        Serial.println("backing");
        launch_ccw(20);
        delay(20);
        brake_lock();
        photos();
        flag_test = false;
      }
    }
  }

  Serial.println("out");

  digitalWrite(8, LOW);
   digitalWrite(9, LOW);

  tz = LOW;
  load = LOW;
  dphoto_forw = LOW;
  flag_test = true;
  
}
//////////////////
/////////////////

