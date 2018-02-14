void write_motor(int x, int y, boolean ramp = false, double cnst = alpha) {
  if (ramp) {
    cur_r += ((double)x - cur_r) * cnst;
    cur_l += ((double)y - cur_l) * cnst;
  }
  else {
    cur_r = x;
    cur_l = y;
  }
  //  x = map(x, -255, 255, -2047, 2047);
  //  y = map(y, -255, 255, -2047, 2047);
  //  x = constrain(x, -2000, 2000);
  //  y = constrain(y, -2000, 2000);
  saber.print("M1:" + String((int)cur_l) + "\r\n");
  saber.print("M2:" + String((int)cur_r) + "\r\n");
  Serial.print("L_PWM::"); Serial.print((int)cur_l); Serial.print("\t");
  Serial.print("R_PWM::"); Serial.println((int)cur_r);
}

void ramp_brake(double deacc) {
  while ((int)cur_l != 0 || (int)cur_l != 0) {
    write_motor(0, 0, true, deacc);
  }
}

void ramp_start(double acc) {
  while ((int)cur_l < setValue-1 || (int)cur_l < setValue-1) {
    write_motor(setValue, setValue, true,acc);
  }
}
