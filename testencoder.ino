#define encL_A  2
#define encL_B  3


volatile  long  encR_pos = 0, encL_pos = 0;
volatile unsigned int  cR = 0, cL = 0;
int lastL, lastR;
void setup() {
  pinMode(8, INPUT);
  pinMode(encL_A, INPUT);
  pinMode(encL_B, INPUT);
  // attachInterrupt(digitalPinToInterrupt(encR_A), encR, RISING);
  attachInterrupt(digitalPinToInterrupt(encL_A), encL, RISING);
  Serial.begin (9600);
  //  Serial1.begin(9600);
  //Serial.println("start");
  //delay(10);
  //  Serial1.write(32);
}
int flag;
void loop() {

  //while (lastL == encL_pos && lastR == encR_pos);


  //Serial.write( (uint8_t *) &encL_pos, sizeof( encL_pos ) );
  if (Serial.available())
  { char c = Serial.read();
    if (c == 'k')
      Serial.print(encL_pos);
    else if (c == 'u')
      encL_pos = 0;
    c = 'n';
  }

  // delayMicroseconds(10);
  lastL = encL_pos;
  //lastR = encR_pos;
}

void encL()
{
  if (digitalRead(encL_B)) encL_pos++;
  else encL_pos--;
}

