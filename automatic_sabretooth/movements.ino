void rot90(int speed, int time) {

  bno_reset();

  setpoint = get_yaw() - 90 - last_error;
  input = get_yaw();

  long cur_time = millis();
  ctr = 0;
  while (1) {

    write_motors(5, -speed, +speed);
    input = get_yaw();
    Serial.print(input, 6);
    //    Serial.print(" ");
    Serial.println(setpoint);

    if (abs(setpoint - input) <= 0.5 || ctr == 2 ) {
      stop_all();
      last_error = get_yaw() - setpoint;
      return;
    }


  }
}


void move180(int speed, int time) {
  bno_reset();
  int input = get_yaw2();
  setpoint = get_yaw2() + 180 - last_error;
  ctr = 0;
  while (1) {
    write_motors(5, -speed, +speed);
    input = get_yaw2();

    int diff = abs(input - setpoint);
    diff = min(diff, 360 - diff);
    Serial.print(input);
    Serial.print(" ");
    Serial.println(setpoint);
    if (diff <= 0.5 || ctr == 3) {
      stop_all();
      last_error = get_yaw() - setpoint;
      return;
    }
  }

}


void forward_ig(int speed, long long time, int ig) {

  bno_reset();
  ctr = 0;
  attachInterrupt(digitalPinToInterrupt(2), isr, RISING);
  setpoint = get_yaw() - last_error;
  input = setpoint;
  mkpid(kp, ki, kd);
  long long start_time = millis();
  int last = ctr; int linecount = 0;

  ctr = 0;

  while ((millis() - start_time) <= time || time < 0) {

    Serial.println(ctr);


    if (ctr == ig) {
      Serial.println("here");


      attachInterrupt(digitalPinToInterrupt(3), isr2, RISING);

      mkpid(kp, ki, kd);
      speed = 250;

      ctr2 = 0;
      int last2 = ctr2;

      while ((millis() - start_time <= time || time < 0)) {
        Serial.println("ctr2" + String(ctr2));
        if (last2 != ctr2) {
          Serial.println("here2");
          stop_all();
          last_error = get_yaw() - setpoint;
          return;
        }
        else {
          input = get_yaw();
          myPID.Compute();
          write_motors(BRAKE, speed + output, speed);
          //          Serial.print(ctr2);
          //          Serial.print("\n");
        }
      }
      //      Serial.println("timeout");
      stop_all();
      last_error = get_yaw() - setpoint;
      return;

    } else {
      input = get_yaw();
      myPID.Compute();
      write_motors(BRAKE, +speed + output, +speed);
    }
  }

  Serial.println("timeout");
  stop_all();
  last_error = get_yaw() - setpoint;
  return;

}



void forward(int speed, long long  time) {
  bno_reset();
  attachInterrupt(digitalPinToInterrupt(2), isr, RISING);
  setpoint = get_yaw() - last_error;

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

      ramp1(2000);
      ramp3(2000);
      speed = 250;
      ctr2 = 0;


      while ((millis() - start_time <= time || time < 0)) {
        if (ctr2 != 0) {
          Serial.println("here2");
          last_error = get_yaw() - setpoint;
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
      last_error = get_yaw() - setpoint;
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

void backward_ig(int speed, int time, int ig) {

  ctr2 = 0;
  //  attachInterrupt(digitalPinToInterrupt(2), isr, RISING);
  setpoint = get_yaw();
  input = setpoint;
  mkpid(kp, ki, kd);
  long long start_time = millis();
  int last = ctr; int linecount = 0;

  ctr2 = 0;

  while ((millis() - start_time) <= time || time < 0) {

    if (ctr2 == ig) {
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
        }
        else {
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

