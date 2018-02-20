void rotate_to_angle(int speed, double target, byte dir) {


  Serial.println("rotate called");

  ramp1(0);
  ramp2(0);
  while (true) {

    input = get_yaw();
    setpoint = target;
    double diff = angle_diff(input, setpoint);
    //        Serial.print(input); Serial.print(" ");
    //          Serial.print(setpoint); Serial.print(" ");
    //      Serial.print(diff); Serial.println(" ");
    if (diff <= 1.0) {
      stop_all();
      return;
    } else {
      if (dir == CW) {
        write_motors(5, 250, -250);
      } else if (dir == CCW) {
        write_motors(-5, -250, 250);
      }
    }

  }
}

void rot90(int speed) {

  bno_reset();
  setpoint = get_yaw() - 90;
  double cosine, saber, herc, last;
  long long last_time = millis();
  last = get_yaw();
  while (true)
  {
    input = get_yaw();
    if (Serial.available()) {
      char c = Serial.read();
      stop_all();
    }
    if ((millis() - last_time) > 1000) {
      //      if (input == last) {
      //        stop_all();
      //        Serial.println("No readings being obtained from BNO.");
      //        STOP
      //      }
      last = input;
      last_time = millis();
    }
    if (abs(setpoint - input) <= 0.08 || input < -90.08)
    {
      stop_all();
      Serial.print("Turned 90");
      ctr2 = 0;
      ctr2flag = true;

      while (true) {
        Serial.println("ctr2 count: " + String(ctr2));
        if (ctr2 == 1) {
          Serial.println(F("2nd photoswitch high. Stopping."));
          stop_all();

          ctr2flag = false;
          ctr2 = 0;

          return;
        }  else {
          input = get_yaw();
          myPID.Compute();
          write_motors(BRAKE, 250 + output, 250);
        }
      }
      //---------------------------
      while (1) {
        Serial.println(get_yaw());
      }
      //---------------------------
      return;
    }
    cosine = cos(D2R(input));
    saber = cosine * speed;
    herc = cosine * 7;
    write_motors(herc, -saber, saber);
    //    Serial.print(herc); Serial.print(" ");
    //    Serial.print(saber); Serial.print(" ");
    //    Serial.println(input);

  }
}

void forward_time(int speed, int dir, int d) {

  setpoint = dir;
  input = get_yaw();

  mkpid(kp, ki, kd);


  long long cur_time = millis();

  while (1) {
    if (millis() - cur_time >= d) {
      stop_all();
      return;
    }

    input = get_yaw();
    myPID.Compute();
    write_motors(BRAKE, speed + output, speed);
  }


}

void forward(int speed, int linecount, double target) {

  ramp1(0);
  ramp2(0);

  setpoint = target;
  input = get_yaw();

  mkpid(kp, ki, kd);

  ctr1 = 0;
  ctr1flag = true;

  while (true) {
    Serial.println("ctr1 count: " + String(ctr1));
    if (ctr1 == linecount) {

      mkpid(kp, ki, kd);
      speed = 200;

      ctr1flag = false;
      ctr1 = 0;

      ctr2 = 0;
      ctr2flag = true;

      while (true) {
        //        Serial.println("ctr2 count: " + String(ctr2));
        if (line() >= 180) {
          //          Serial.println(F("2nd photoswitch high. Stopping."));

          Serial.println("stopping");
          stop_all();

          ctr2flag = false;
          ctr2 = 0;

          return;
        }  else {
          //              Serial.print(output); Serial.print(" ");
          //        Serial.print(input); Serial.print(" ");
          //          Serial.print(setpoint); Serial.println(" ");
          input = get_yaw();
          myPID.Compute();
          write_motors(BRAKE, speed + output, speed);
        }
      }

    } else {

      //      Serial.print(output); Serial.println(" ");
      //        Serial.print(input); Serial.println(" ");
      //          Serial.print(setpoint); Serial.println(" ");
      input = get_yaw();
      myPID.Compute();
      write_motors(BRAKE, speed + output, speed);
    }

  }

}

