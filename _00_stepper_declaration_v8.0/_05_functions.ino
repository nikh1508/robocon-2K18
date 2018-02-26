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
    feedback_1 = !digitalRead(tz);
  feedback_2 = !digitalRead(load);
}
//////////////////////////////
void pin_reset() {
  digitalWrite(data_1, LOW);
  digitalWrite(data_2, LOW);
  digitalWrite(data_3, LOW);
}
