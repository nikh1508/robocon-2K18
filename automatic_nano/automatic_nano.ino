void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), isr1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), irs2, CHANGE);
}

volatile long enc_cnt = 0;

void isr1() {
  enc_cnt++;
}

void isr2() {
  enc_cnt--;
}

void loop() {
  if (Serial.available()) {
    char ch = Serial.read();
    if (ch == 'u') enc_cnt = 0;
    else if (ch == 'k') Serial.print(enc_cnt);
  }
}

