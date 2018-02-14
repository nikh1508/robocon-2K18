

void forward(int speed, long long  time) {

  flag = 1;

  attachInterrupt(digitalPinToInterrupt(3), isr, FALLING);
  
  delay(50);
  setpoint = get_yaw();
  input = setpoint;

  mkpid(kp, ki, kd);

  long long start_time = millis();
  while ((millis() - start_time) <= time || time < 0) {

    if (flag == 0) {
      Serial.println("here");
      detachInterrupt(digitalPinToInterrupt(2));
      attachInterrupt(digitalPinToInterrupt(3), isr2, RISING);
      mkpid(kp, ki, kd);
      speed = 250;
      while ((millis() - start_time <= time || time < 0)) {
        if (flag2 == 0) {
          Serial.println("here2");
          stop_all();
          return;
        }
  
        input = get_yaw();   
        myPID.Compute();
        write_motors(BRAKE, +speed + output, +speed);
      }

      Serial.println("timeout");
      stop_all();
      return;
    }
    else {
      input = get_yaw();
      myPID.Compute();
      write_motors(BRAKE, +speed + output, +speed);
    }
  }

  Serial.println("timeout");

  write_motors(BRAKE, BRAKE, BRAKE);
}

void left(int speed, int time) {
  bno.begin();
  delay(50);
  setpoint = get_yaw();
  input = setpoint;
  mkpid(kp, ki, kd);

  long long start_time = millis();
  while ((millis() - start_time) <= time || time < 0) {
    write_motors(-(speed + output), +speed, -speed);
    input = get_yaw();
    myPID.Compute();
    debug();
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
  while ((millis() - start_time) <= time || time < 0) {
    write_motors(+(speed + output), -speed, +speed);

    input = get_yaw();
    myPID.Compute();
    debug();
  }

  stop_all();
}

void back(int speed, int time) {
  bno.begin();
  delay(50);
  setpoint = get_yaw();
  input = setpoint;
  mkpid(kp, ki, kd);

  long long start_time = millis();
  while ((millis() - start_time) <= time || time < 0) {
    write_motors(0, -speed, -speed);
    input = get_yaw();
    myPID.Compute();
  }

  stop_all();
}
