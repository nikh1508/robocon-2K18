void manual()
{
  if(Serial.available())
  {
    qw=Serial.read();
    fwm=Serial.parseInt();
    bwm=Serial.parseInt();
    del=Serial.parseInt();
    fwm=constrain(fwm,0,160);
    bwm=constrain(bwm,0,160);
    del=constrain(del,0,160);
  }
    if(qw=='s' && dphoto_bac)
    {
      launch_cw(fwm);
      Serial.println("Throwing");
    }
    if (dphoto_forw)
    {
      delayMicroseconds(del);//experimnetal
      for (int i = 0; i < 4 ; i++) { //2
        launch_ccw(bwm);                              //IF USING 5S BATTERY DONT GIVE MORE THAN 159 PWM ON ANY POINT.........!!!!!!!!!
        delay(20);
        brake_lock();
        Serial.println("Retracting");
      }
   delay(25);
   brake_free();
   
     qw='o';
    }
    Serial.print(dphoto_forw); Serial.print(dphoto_bac); Serial.println("\t");
}

