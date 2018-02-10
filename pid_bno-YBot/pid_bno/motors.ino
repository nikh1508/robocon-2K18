void write_motor(int x, int y) {
  //dir-fwd
  //  digitalWrite(motor.dir_l, 0);
  //  digitalWrite(motor.dir_r, 0);
  //dir-rev
  digitalWrite(motor.dir_l, 1);
  digitalWrite(motor.dir_r, 1);
  analogWrite(motor.pwm_l, x);
  analogWrite(motor.pwm_r, y);
}
