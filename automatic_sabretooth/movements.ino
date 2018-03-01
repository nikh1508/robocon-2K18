void rotate_to_angle(double target, byte dir) {
  ramp1(0);
  ramp2(0);

  if (dir == CCW)
    write_motors(8, -250, 250);
  else if (dir == CW)
    write_motors(-8, 250, -250);

  while (true) {
    if (target == 0) {
      input = get_yaw();
      setpoint = target;
      while (true) {
        input = get_yaw();
        if (input < 1 || input > 359) {
          stop_all();
          return;
        }
      }
    } else if (target == 270) {
      setpoint = target;
      while (true) {
        input = get_yaw();
        if (input < 271 && input > 269) {
          stop_all();
          return;
        }
      }
    } else if (target == 90) {
      setpoint = target;
      while (true) {
        input = get_yaw();
        if (input < 91 && input > 89) {
          stop_all();
          return;
        }
      }
    }
  }
}

void forward_enc(int speed, int enc, int target, int offset = 1500) {
  reset_encoder();
  Serial.print("Enc_Initial::");
  Serial.println(encoder());
  setpoint = target;
  mkpid(kp, ki, kd);
  while ((enc - encoder()) > offset) {
    input = get_yaw();
    myPID.Compute();
    write_motors(BRAKE, speed, speed + output);
    Serial.println(encoder());
  }

  speed = SLOW_SPEED;
  mkpid(kp, ki, kd);

  while ((enc - encoder()) > 0) {
    input = get_yaw();
    myPID.Compute();
    write_motors(BRAKE, speed, speed + output);
  }
  Serial.println("Stop.");
  stop_all();
}

void forward(int speed, int enc, int target) {
  setpoint = target;
  mkpid(kp, ki, kd);
  reset_encoder();


  while (enc - encoder() > 800) {
    input = get_yaw();
    myPID.Compute();
    write_motors(BRAKE, speed, speed + output);
    Serial.print("encoder: ");
    Serial.println(encoder());
  }

  speed = 200;
  mkpid(kp, ki, kd);


  while (line() < LINE_THRES) {

    input = get_yaw();
    myPID.Compute();
    write_motors(BRAKE, speed, speed + output);
  }

  Serial.println("Stop");
  stop_all();
}

void backward(int speed, int enc, int target) {
  setpoint = target;
  mkpid(kp, ki, kd);
  reset_encoder();

  Serial.print("encoder: ");
  Serial.println(encoder());

  while (abs(enc - encoder()) > 800) {
    input = get_yaw();
    myPID.Compute();
    write_motors(BRAKE, -speed, -speed + output);
     Serial.print("encoder: ");
    Serial.println(encoder());
  }

  speed = SLOW_SPEED;
  mkpid(kp, ki, kd);


  while (line() < LINE_THRES) {

    input = get_yaw();
    myPID.Compute();
    write_motors(BRAKE, -speed, -speed + output);
  }

  stop_all();
}

void backward_enc(int speed, int enc, int target, bool fence = false) {
  enc = -abs(enc);
  setpoint = target;
  mkpid(kp, ki, kd);
  reset_encoder();


  long long start = millis();
  while (abs(enc - encoder()) > 1500) {
    input = get_yaw();
    myPID.Compute();
    write_motors(BRAKE, -speed, -speed + output);
    if (fence && (millis() - start) > 4000)
      break;
    Serial.print("encoder: ");
    Serial.println(encoder());
  }

  speed = SLOW_SPEED;
  mkpid(kp, ki, kd);

  while ((enc - encoder()) < 0) {
    input = get_yaw();
    myPID.Compute();
    write_motors(BRAKE, -speed, -speed + output);
    if (fence && (millis() - start) > 4000)
      break;
    Serial.println(encoder());
  }
  if (fence) {
    stop_all();
    Serial.println("Stop.");
    return;
  }
  Serial.println("Stop.");
  stop_all();
}
