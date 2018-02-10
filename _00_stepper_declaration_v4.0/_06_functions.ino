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
////
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
/////////////////////////////////////////////////////
void incrementals() {
  if ((step[0].stepcount <= ((step[0].set_stepcount / step[0].divisor)*step[0].multiplier)) && ( (c == 'a') || (c == 'd')  || (c == 'q') || (c == 'e') ) )
    
  ////////////////
  if ((step[1].stepcount <= ((step[1].set_stepcount / step[1].divisor)*step[1].multiplier)) && ((c == 'w') || (c == 's') || (c == 'q') || (c == 'e') ) )
    increment_1();
  ////////////////
  if ((step[2].stepcount <= ((step[2].set_stepcount / step[2].divisor)*step[2].multiplier)) && ((c == 'w') || (c == 's') || (c == 'a') || (c == 'd') || (c == 'q') || (c == 'e'))) {
    increment_2();
  }
}
/////////////////////////////////////////////////////
void decrmentals() {
  if ((step[0].stepcount > ((step[0].set_stepcount / step[0].divisor)*step[0].multiplier)) && ( (c == 'a') || (c == 'd') || (c == 'q') || (c == 'e') ) )
    decrement_0();
  ////////////////
  if ((step[1].stepcount > ((step[1].set_stepcount / step[1].divisor)*step[1].multiplier)) && ((c == 'w') || (c == 's') || (c == 'q') || (c == 'e')))
    decrement_1();
  ////////////////
  if ((step[2].stepcount > ((step[2].set_stepcount / step[2].divisor)*step[2].multiplier)) && ((c == 'w') || (c == 's') || (c == 'a') || (c == 'd') || (c == 'q') || (c == 'e') ) )
    decrement_2();
}
////////////////////////////////////////////////////
void stp() {
  if ((step[0].stepcount >= step[0].set_stepcount ) && ( (c == 'a') || (c == 'd') || (c == 'q') || (c == 'e') ) )
    c = 't';
  if ((step[1].stepcount >= step[1].set_stepcount ) && ( (c == 'w') || (c == 's') || (c == 'q') || (c == 'e') ) )
    c = 't';
  if ((step[2].stepcount >= step[2].set_stepcount ) && ( (c == 'w') || (c == 's') || (c == 'a') || (c == 'd') || (c == 'q') || (c == 'e') ) )
    c = 't';
}
///////////////////////////////////////////////////
void flag_reset(){
  flag[0]=true;
  flag[1]=true;
  flag[2]=true;
}
////
void brake_reset(){
  step[0].brake=0;
  step[1].brake=0;
  step[2].brake=0;
}

