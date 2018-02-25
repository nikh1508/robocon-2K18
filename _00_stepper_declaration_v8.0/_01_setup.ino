void setup() {
  Serial.begin(9600);
  //////////////////////////////
  DDRC = 0xFF;
  DDRL = 0xFF;
  DDRK = 0xFF;
  PORTC = 0x00;
  PORTL = 0x00;
  PORTK = 0x00;
  ////////
  pinMode(load, INPUT);
  pinMode(redphoto, INPUT);
  pinMode(tz, INPUT);
  //
  pinMode(data_1, OUTPUT);
  pinMode(data_2, OUTPUT);
  pinMode(data_3, OUTPUT);
  //
  digitalWrite(data_1, HIGH);
  digitalWrite(data_2, HIGH);
  digitalWrite(data_3, HIGH);
  //
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  //
  digitalWrite(A1,LOW);
  digitalWrite(A2,LOW);
  //
  /////////////
  noInterrupts();
  ////////////////////////////////////
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = nx;//target
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12); //256 PRESCALE
  TIMSK1 |= (1 << OCIE1A);
  ////////////////////////////////////
  TCCR3A = 0;
  TCCR3B = 0;
  TCNT3 = 0;
  OCR3A = nx;//target
  TCCR3B |= (1 << WGM32);
  TCCR3B |= (1 << CS32); //256 PRESCALE
  TIMSK3 |= (1 << OCIE3A);
  ////////////////////////////////////
  TCCR4A = 0;
  TCCR4B = 0;
  TCNT4 = 0;
  OCR4A = nx;//target
  TCCR4B |= (1 << WGM42);
  TCCR4B |= (1 << CS42); //256 PRESCALE
  TIMSK4 |= (1 << OCIE4A);
  ////////////////////////////////
  interrupts();
  assign();
}
