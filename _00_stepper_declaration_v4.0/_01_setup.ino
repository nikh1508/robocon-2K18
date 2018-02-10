void setup() {
  Serial.begin(9600);
  Wire.begin();
  global_initialize();
  bno_initialize();
  //////////////////////////////
  DDRC = 0xFF;
  DDRL = 0xFF;
  DDRK = 0xFF;
  PORTC = 0x00;
  PORTL = 0x00;
  PORTK = 0x00;
  /////////////
  noInterrupts();
  ////////////////////////////////////
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = (int)filter[0].target;//target
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12); //256 PRESCALE
  TIMSK1 |= (1 << OCIE1A);
  ////////////////////////////////////
  TCCR3A = 0;
  TCCR3B = 0;
  TCNT3 = 0;
  OCR3A = (int)filter[1].target;//target
  TCCR3B |= (1 << WGM32);
  TCCR3B |= (1 << CS32); //256 PRESCALE
  TIMSK3 |= (1 << OCIE3A);
  ////////////////////////////////////
  TCCR4A = 0;
  TCCR4B = 0;
  TCNT4 = 0;
  OCR4A = (int)filter[2].target;//target
  TCCR4B |= (1 << WGM42);
  TCCR4B |= (1 << CS42); //256 PRESCALE
  TIMSK4 |= (1 << OCIE4A);
  ////////////////////////////////
  interrupts();
  bno();
}
