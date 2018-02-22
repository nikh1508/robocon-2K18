void global_initialize() {
  for (i = 0; i < 3; i++) {
    step[i].multiplier = 9;
    step[i].divisor = 10;
    step[i].set_brake = brake_time;
  }
  part = step[0].multiplier / step[0].divisor;
}
////////////////////////////////////////////////////////
void bno_initialize() {
  Wire.beginTransmission(adr);
  Wire.write(0x3D);
  Wire.write(0x0C);
  Wire.endTransmission();
  delay(10);
  ////////////////
  for (i = 0; i < 50; i++) {
    Wire.beginTransmission(adr);
    Wire.write(0x1A);
    Wire.endTransmission();
    Wire.requestFrom(adr, 2);
    lsb_yaw = Wire.read();
    msb_yaw = Wire.read();
    yaw_offset = yaw_offset + (((((int)msb_yaw) << 8) | lsb_yaw));
  }
  yaw_offset /= 800;
  Serial.println(yaw_offset);
  delay(50);
}
////////////////////////////////////////////
void bno() {
  Wire.beginTransmission(adr);
  Wire.write(0x1A);
  Wire.endTransmission();
  Wire.requestFrom(adr, 2);
  lsb_yaw = Wire.read();
  msb_yaw = Wire.read();
  yaw = (((((int)msb_yaw) << 8) | lsb_yaw));
  yaw /= 16;
  yaw = yaw - yaw_offset;
  if (yaw < 0)
    yaw = yaw + 360;
  if (yaw > 180 && yaw < 360) {
    yaw = map(yaw, 180, 360, -180, 0);
  }
  //  Serial.print("yaw=");
  //  Serial.println(yaw);
}
/////////////////////////////////////////////////////
void error_interrupt() {
  TCNT1 > OCR1A ? TCNT1 = 0 : OCR1A = OCR1A;/////error correction
  TCNT3 > OCR3A ? TCNT3 = 0 : OCR3A = OCR3A;/////error correction
  TCNT4 > OCR4A ? TCNT4 = 0 : OCR4A = OCR4A;/////error correction
}
///////////////////////////////////////////////////
void reset_OC() {
  nx = initial_speed;
  ny = nx;
  step[0].brake = 0;
  step[0].stepcount = 0;
}
//////////////////////////////////////////////////
void read_feed() {
  if (feedback_1 == LOW)
    feedback_1 = !digitalRead(11);
  feedback_2 = !digitalRead(10);
  //  feedback_3 = digitalRead(9);
}
/////////////////////////////////////////////////
