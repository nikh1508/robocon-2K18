//void backward(int speed) {
//  ramp1(0);
//  ramp2(0);
//  write_motors(BRAKE, -speed, -speed);
//}
//
//void back_sun(int speed, int linecount, double target, int ignore=0) {
//  ramp1(0);
//  ramp2(0);
//  setpoint = target;
//  input = get_yaw();
//  mkpid(kp, ki, kd);
//
//  int cur_lc = 0;
//  long start_time = millis();
//
//  while (true) {
//    if (line() >= LINE_THRES && (millis() - start_time >= ignore)) {
//      cur_lc++;
//      if (cur_lc == linecount) {
//        stop_all();
//        return;
//      }
//    } else {
//      input = get_yaw();
//      myPID.Compute();
//      write_motors(BRAKE, -(speed + output), -speed);
//    }
//  }
//}
//
//void backward(int speed, int linecount, double target) {
//
//  ramp1(0);
//  ramp2(0);
//
//  int initial = 0;
//
//  setpoint = target;
//  input = get_yaw();
//  mkpid(kp, ki, kd);
//
//  int cur_lc = 0;
//
//  while (true) {
//    if (line() >= LINE_THRES) {
//      cur_lc++;
//      if (cur_lc >= linecount) {
//        stop_all();
//        break;
//      }
//    } else {
//
//      int final_val = ALPHA * initial + ( 1 - ALPHA ) * speed;
//      initial = final_val;
//
//      input = get_yaw();
//      myPID.Compute();
//      Serial.print("[backward PID]: " );
//      Serial.print(output); Serial.print(" ");
//      Serial.print(input); Serial.print(" ");
//      Serial.print(setpoint); Serial.println(" ");
////      write_motors(BRAKE, -(speed + output), -speed);
//      write_motors(BRAKE, -(final_val + output), -speed);
//    }
//  }
//}
//
//void fwd_enc(int speed, long count, int target) {
//  ramp1(0);
//  ramp2(0);
//  reset_encoder();
//  setpoint = target;
//  mkpid(kp, ki, kd);
//  while (1) {
//    if (encoder() >= count) {
//      stop_all();
//      return;
//    } else {
//      input = get_yaw();
//      myPID.Compute();
//      write_motors(BRAKE, +speed, +speed + output);
//    }
//  }
//}
//
//void fwd_sun(int speed, int linecount, double target, int ignore=0) {
//  ramp1(2000);
//  ramp2(2000);
//  setpoint = target;
//  input = get_yaw();
//  mkpid(kp, ki, kd);
//
//  int cur_lc = 0;
//  long start_time = millis();
//
//  while (true) {
//    if (line() >= LINE_THRES && (millis() - start_time >= ignore)) {
//      cur_lc++;
//      if (cur_lc == linecount) {
//        stop_all();
//        return;
//      }
//    } else {
//      input = get_yaw();
//      myPID.Compute();
//      write_motors(BRAKE, speed, speed + output);
//    }
//  }
//}
//
//
//
//void forward(int speed, int linecount, double target, int ign = 0) {
//  ramp1(2000);
//  ramp2(2000);
//  setpoint = target;
//  input = get_yaw();
//  mkpid(kp, ki, kd);
//  ctr1 = 0;
//  ctr1flag = false;
//  long long tstart = millis();
//  while (true) {
//    Serial.println("ctr1 count: " + String(ctr1));
//    if ((millis() - tstart) >= ign) ctr1flag = true;
//    if (ctr1 == linecount) {
//      ramp1(0);
//      ramp2(0);
//      mkpid(kp, ki, kd);
//      speed = 200;
//      ctr1flag = false;
//      ctr1 = 0;
//      ctr2 = 0;
//      ctr2flag = true;
//      while (true) {
//        if (line() >= LINE_THRES) {
//          Serial.println("stopping");
//          stop_all();
//          ctr2flag = false;
//          ctr2 = 0;
//          return;
//        }  else {
//          Serial.print("[forward PID]: " );
//          Serial.print(output); Serial.print(" ");
//          Serial.print(input); Serial.print(" ");
//          Serial.print(setpoint); Serial.println(" ");
//          input = get_yaw();
//          myPID.Compute();
//          write_motors(BRAKE, speed, speed + output);
//        }
//      }
//
//    } else {
//      Serial.print("[forward PID]: ");
//      Serial.print(output); Serial.println(" ");
//      Serial.print(input); Serial.println(" ");
//      Serial.print(setpoint); Serial.println(" ");
//      input = get_yaw();
//      myPID.Compute();
//      write_motors(BRAKE, speed, speed + output);
//    }
//
//  }
//
//}
//
//

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
//
//void backward_time(int speed, int target, int time) {
//  setpoint = target;
//  input = get_yaw();
//  mkpid(kp, ki, kd);
//  long long cur_time = millis();
//  while (1) {
//    if (millis() - cur_time >= time) {
//      stop_all();
//      return;
//    }
//    input = get_yaw();
//    myPID.Compute();
//    write_motors(BRAKE, -speed, -speed);
//  }
//}
//
//void f2line(double tg) {
//  ramp1(0);
//  ramp2(0);
//  mkpid(kp, ki, kd);
//  setpoint = tg;
//  while (true) {
//    double val = line();
//    if (val >= 200) break;
//    input = get_yaw();
//    myPID.Compute();
//    write_motors(BRAKE, 100 + output, 100);
//  }
//  stop_all();
//}
//
//void l2line() {
//  Serial.println("[l2line] l2line running");
//  ramp1(0);
//  ramp2(0);
//  write_motors(+27, +300, -300);
//  while (digitalRead(2) == HIGH);
//  stop_all();
//  Serial.println("[l2line] l2line done");
//}
//
//
//void forward_time(int speed, int dir, int d) {
//  setpoint = dir;
//  input = get_yaw();
//  mkpid(kp, ki, kd);
//  long long cur_time = millis();
//  while (1) {
//    if (millis() - cur_time >= d) {
//      stop_all();
//      return;
//    }
//    input = get_yaw();
//    myPID.Compute();
//    write_motors(BRAKE, speed + output, speed);
//  }
//}5\

void forward_enc(int speed, int enc, int target, int offset=1500) {
  setpoint = target;
  mkpid(kp, ki, kd);
  reset_encoder();

  while ((enc - encoder()) > offset) {
    input = get_yaw();
    myPID.Compute();
    Serial.print("[pid]: ");
    Serial.print(output); Serial.print(" ");
    Serial.print(input); Serial.print(" ");
    Serial.print(setpoint); Serial.println(" ");
    write_motors(BRAKE, speed , speed + output) ;
    Serial.println(encoder());
  }

  speed = 130;
  mkpid(kp, ki, kd);

  while ((enc-encoder()) > 0) {
    input = get_yaw();
    myPID.Compute();
    write_motors(BRAKE, speed, speed + output);
    Serial.println(encoder());
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
    Serial.print("[pid]: ");
    Serial.print(output); Serial.print(" ");
    Serial.print(input); Serial.print(" ");
    Serial.print(setpoint); Serial.println(" ");
    write_motors(BRAKE, speed , speed + output) ;
  }

  speed = 200;
  mkpid(kp, ki, kd);

  while (line() < LINE_THRES) {
    input = get_yaw();
    myPID.Compute();
    Serial.print("[pid]: ");
    Serial.print(output); Serial.print(" ");
    Serial.print(input); Serial.print(" ");
    Serial.print(setpoint); Serial.println(" ");
    write_motors(BRAKE, speed , speed + output);
  }

  stop_all();

}
void backward_enc(int speed, int enc, int target, bool fence=false) {
  setpoint = target;
  mkpid(kp, ki, kd);
  reset_encoder();
  long long start=millis();
  while (abs(enc - encoder()) > 1500) {
    input = get_yaw();
    myPID.Compute();
    Serial.print("[pid]: ");
    Serial.print(output); Serial.print(" ");
    Serial.print(input); Serial.print(" ");
    Serial.print(setpoint); Serial.println(" ");
    write_motors(BRAKE, -speed , -speed+output) ;
    Serial.println(encoder());
    if(fence && (millis()-start)>1500)
    break;
  }
  if(fence)
  {
    stop_all();
    return;
    }
  speed = 120;
  mkpid(kp, ki, kd);

  while ((enc-encoder()) < 0) {
    input = get_yaw();
    myPID.Compute();
    write_motors(BRAKE, -speed, -speed + output);
    Serial.println(encoder());
  }
  Serial.println("Stop.");
  stop_all();
}
