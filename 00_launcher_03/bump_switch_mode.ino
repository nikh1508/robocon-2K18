void manual()
{
  photos();
  if(Serial.available())
  {
    qw=Serial.read();
    
    
  }
    if(qw=='s' && dphoto_bac)
    {
      launch_cw(140);
      Serial.println("Throwing");
    }
//    photos();
    if (dphoto_forw && qw=='s')
    {
      delayMicroseconds(3000);//experimnetal
      for (int i = 0; i < 4 ; i++) { //2
        launch_ccw(140);                              //IF USING 5S BATTERY DONT GIVE MORE THAN 159 PWM ON ANY POINT.........!!!!!!!!!
        delay(20);
        brake_lock();
        Serial.println("Retracting");
      }
//   delay(25);
//   brake_free();
   while(!dphoto_bac)
   {
    launch_ccw(5);
    delay(20);
    brake_lock();
    photos();
   }
     qw='o';
    }
    Serial.print(dphoto_forw); Serial.print(dphoto_bac); Serial.println("\t");
}


