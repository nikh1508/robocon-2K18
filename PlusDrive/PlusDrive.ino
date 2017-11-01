
int pins[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
int a, b, c, d, e, f, dir;
void setup()
{
  Serial.begin(9600);
  int i = 1;
  while (i < 13)
    pinMode(pins[i++], OUTPUT);
  int dir = 1;

}
void up()
{
  a = 5;
  b = 6;
  c = 7;
  d = 8;
  e = 1;
  f = 3;
}
void down()
{
  a = 8;
  b = 7;
  c = 6;
  d = 5;
  e = 3;
  f = 1;
}
void right()
{
  a = 12;
  b = 11;
  c = 10;
  d = 9;
  e = 4;
  f = 2;
}
void left()
{
  a = 9;
  b = 10;
  c = 11;
  d = 12;
  e = 2;
  f = 4;
}
void loop()
{
  if (Serial.available())
  {
    dir = Serial.read();
    switch (dir)
    {
      case 1: up(); break;
      case 2: right(); break;
      case 3: down(); break;
      case 4: left(); break;
    }
  }
  attachInterrupt(digitalPinToInterrupt(e), isr, CHANGE);
  attachInterrupt(digitalPinToInterrupt(f), isr, CHANGE);
}

void isr()
{
  if (digitalRead(a) == LOW && digitalRead(b) == LOW || digitalRead(c) == LOW && digitalRead(d) == LOW)return;
  if (digitalRead(a) == HIGH || digitalRead(d) == HIGH)
  {
    //turn bot ac by 2 deg
  }
  else
  {
      //turn bot c by 2 deg
  }

}

