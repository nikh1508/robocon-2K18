///////ISRs...!!!!/////
ISR(TIMER1_COMPA_vect) { //motor-->0
  if (c == 'a' || c == 'e') {
    forw[0] == true ? PORTL = 0x14 : PORTL = 0x04;
    forw[0] = !forw[0];
    step[0].stepcount++;
  }
  if (c == 'd' || c == 'q') {
    bac[0] == true ? PORTL = 0x10 : PORTL = 0x00;
    bac[0] = !bac[0];
    step[0].stepcount++;
  }
  if (c == 't') {
    PORTL = 0x00;
    step[0].brake++;
  }
}
ISR(TIMER3_COMPA_vect) {//motor-->1
  if (c == 'q') {
    forw[1] == true ? PORTC = 0x01 : PORTC = 0x00;
    forw[1] = !forw[1];
    step[1].stepcount++;
  }
  if (c == 'e') {
    bac[1] == true ? PORTC = 0x05 : PORTC = 0x04;
    bac[1] = !bac[1];
    step[1].stepcount++;
  }
  if (c == 't') {
    PORTC = 0x00;
    step[1].brake++;
  }
}
ISR(TIMER4_COMPA_vect) {//motor-->2
  if (c == 'd' || c == 'e') {
    forw[2] == true ? PORTK = 0xA0 : PORTK = 0x80;
    forw[2] = !forw[2];
    step[2].stepcount++;
  }
  if (c == 'a' || c == 'q') {
    bac[2] == true ? PORTK = 0x20 : PORTK = 0x00;
    bac[2] = !bac[2];
    step[2].stepcount++;
  }
  if (c == 't') {
    PORTK = 0x00;
    step[2].brake++;
  }
}
