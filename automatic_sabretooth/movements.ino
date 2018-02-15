void rot90(int speed, int time) {
  //  bno.begin();
  delay(100);

  setpoint = get_yaw() - 90;
  input = get_yaw();

  int cur_time = millis();

  while (1) {
    write_motors(5, -speed, +speed);
    input = get_yaw();
    //    Serial.print(input, 6);
    //    Serial.print(" ");
    //    Serial.println(setpoint);
    if (abs(setpoint - input) <= 0.5) {
      stop_all();
      return;
    }
  }
}

void forward_ig(int speed, long long time, int ig) {
  ctr = 0;
  attachInterrupt(digitalPinToInterrupt(2), isr, RISING);

  setpoint = get_yaw();

  input = setpoint;
  mkpid(kp, ki, kd);
  long long start_time = millis();
  int last = ctr;
  int linecount = 0;

  ctr = 0;

  while ((millis() - start_time) <= time || time < 0) {
    if (ctr == 1) {
      ctr3 = 0;
      attachInterrupt(digitalPinToInterrupt(19), isr3, FALLING);
      while (1) {
        if (ctr3 == 1 && ctr == 1)
          break;
        else if (ctr3 == 0 && ctr == 2) {
          ctr--;
          break;
        } else if (ctr == 2)
          break;
      }
    }

    if (ctr == ig) {
      Serial.println("here");

      attachInterrupt(digitalPinToInterrupt(3), isr2, RISING);

      mkpid(kp, ki, kd);
      speed = 250;

      ctr2 = 0;
      int last2 = ctr2;

      while ((millis() - start_time <= time || time < 0)) {
        if (last2 != ctr2) {
          Serial.println("here2");
          stop_all();
          return;
        } else {
          input = get_yaw();
          myPID.Compute();
          write_motors(BRAKE, speed + output, speed);
          Serial.print(ctr2);
          Serial.print("\n");
        }
      }
      Serial.println("timeout");
      stop_all();
      return;

    } else {
      input = get_yaw();
      myPID.Compute();
      write_motors(BRAKE, +speed + output, +speed);
    }
  }

  Serial.println("timeout");
  stop_all();
  return;
}

void forward(int speed, long long time) {
  attachInterrupt(digitalPinToInterrupt(2), isr, RISING);

  setpoint = get_yaw();
  input = setpoint;

  mkpid(kp, ki, kd);

  long long start_time = millis();

  ctr = 0;

  while ((millis() - start_time) <= time || time < 0) {
    Serial.println(ctr);
    if (ctr != 0) {
      Serial.println(ctr);
      Serial.println("here");

      attachInterrupt(digitalPinToInterrupt(3), isr2, FALLING);
      mkpid(kp, ki, kd);
      speed = 250;
      ctr2 = 0;
      int last2 = ctr2;

      int first = true;

      while ((millis() - start_time <= time || time < 0)) {
        if (last2 != ctr2) {
          Serial.println("here2");
          stop_all();
          return;
        } else {
          input = get_yaw();
          myPID.Compute();
          write_motors(BRAKE, +speed + output, +speed);
        }
      }

      Serial.println("timeout");
      stop_all();
      return;
    } else {
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
    myPID.Compute();
    Serial.println(output);
    write_motors(+(20 + output), +speed, -speed);

    input = get_yaw();
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
    Serial.println(output);
    //    write_motors(-(20+ output), -speed, +speed);

    input = get_yaw();
    myPID.Compute();
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
