void backward(int speed) {
  ramp1(0);
  ramp2(0);
  write_motors(BRAKE, -speed, -speed);
}

void forward(int speed, int linecount, double target) {
  ramp1(2000);
  ramp2(2000);
  setpoint = target;
  input = get_yaw();
  mkpid(kp, ki, kd);
  ctr1 = 0;
  ctr1flag = true;
  long long tstart = millis();
  while (true) {
    Serial.println("ctr1 count: " + String(ctr1));
    if (ctr1 == linecount) {
      ramp1(0);
      ramp2(0);
      mkpid(kp, ki, kd);
      speed = 200;
      ctr1flag = false;
      ctr1 = 0;
      ctr2 = 0;
      ctr2flag = true;
      while (true) {
        if (line() >= 190) {
          Serial.println("stopping");
          stop_all();
          ctr2flag = false;
          ctr2 = 0;
          return;
        }  else {
          Serial.print("[forward PID]: " );
          Serial.print(output); Serial.print(" ");
          Serial.print(input); Serial.print(" ");
          Serial.print(setpoint); Serial.println(" ");
          input = get_yaw();
          myPID.Compute();
          write_motors(BRAKE, speed, speed + output);
        }
      }

    } else {
      Serial.print("[forward PID]: ");
      Serial.print(output); Serial.println(" ");
      Serial.print(input); Serial.println(" ");
      Serial.print(setpoint); Serial.println(" ");
      input = get_yaw();
      myPID.Compute();
      write_motors(BRAKE, speed, speed + output);
    }

  }

}


void rotate_to_angle(double target, byte dir) {
  ramp1(0);
  ramp2(0);
  while (true) {
    input = get_yaw();
    setpoint = target;
    double diff = angle_diff(input, setpoint);
    Serial.print("[rotate_to_angle]: ");
    Serial.print(input); Serial.print(" ");
    Serial.print(setpoint); Serial.print(" ");
    Serial.print(diff); Serial.println(" ");
    if (diff <= 0.5) {
      stop_all();
      return;
    } else {
      if (dir == CW) {
        write_motors(-8, 250, -250);
      } else if (dir == CCW) {
        write_motors(8, -250, 250);
      }
    }

  }
}

void backward_time(int speed, int target, int time) {
  setpoint = target;
  input = get_yaw();
  mkpid(kp, ki, kd);
  long long cur_time = millis();
  while (1) {
    if (millis() - cur_time >= time) {
      stop_all();
      return;
    }
    input = get_yaw();
    myPID.Compute();
    write_motors(BRAKE, -speed, -speed);
  }
}

void f2line(double tg) {
  ramp1(0);
  ramp2(0);
  mkpid(kp, ki, kd);
  setpoint = tg;
  while (true) {
    double val = line();
    if (val >= 200) break;
    input = get_yaw();
    myPID.Compute();
    write_motors(BRAKE, 100 + output, 100);
  }
  stop_all();
}

void l2line() {
  Serial.println("[l2line] l2line running");
  ramp1(0);
  ramp2(0);
  write_motors(+27, +300, -300);
  while (digitalRead(2) == HIGH);
  stop_all();
  Serial.println("[l2line] l2line done");
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
