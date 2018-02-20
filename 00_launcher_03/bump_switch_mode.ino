void manual()
{
  if(Serial.available())
  {
    qw=Serial.read();
    if(qw=='s' && dphoto_bac)
    {
      launch_cw(85);
      Serial.println("Throwing");
    }
    if (dphoto_forw)
    {
      delayMicroseconds(700);//experimnetal
      for (int i = 0; i < 4 ; i++) { //2
        launch_ccw(120);                              //IF USING 5S BATTERY DONT GIVE MORE THAN 159 PWM ON ANY POINT.........!!!!!!!!!
        delay(20);
        brake_lock();
        Serial.println("Retracting");
      }
     }
     qw='o';
  }
}

