char b = 'o';
void loop()
{ launcher_sens();

  if (Serial_debug)
    laun_debug();
  else
  {
    if (Serial.available())
    {
      b = Serial.read();
      if ('s' == b)
      { laun_cw(255);
      }
      if ('l' == b)
      { //laun_cw(255);
      }
    }
    if (launcher.dphoto)
    { for (int i = 0; i < 2; i++) {
        laun_ccw(255);
        delay(20);
        laun_brakF();
      }
      b = 'o';
    }
    if (launcher.dphotocock && b == 'l')
    { delay(500);
      laun_cw(20);
    }
    //b='o';
  }
  if (launcher.dphotostop && b == 'l')
  { for (int i = 0; i < 2; i++) {
      laun_ccw(60);
      delay(5);
      laun_brak();
    }
    b = 'o';
  }
  Serial.println(b);

}

