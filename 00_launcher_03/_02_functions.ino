void launch()
{

  //--------------------------TZ1-------------------------------
  if (zone1 == 1)
  {

    if (dphoto_bac)
    {
      launch_cw(50);                                 //IF USING 5S BATTERY DONT GIVE MORE THAN 159 PWM ON ANY POINT.........!!!!!!!!!
      Serial.println("Throwing");
    }
    if (dphoto_forw)
    {
      delayMicroseconds(1);//experimnetal
      for (int i = 0; i < 4 ; i++) { //2
        launch_ccw(80);                              //IF USING 5S BATTERY DONT GIVE MORE THAN 159 PWM ON ANY POINT.........!!!!!!!!!
        delay(20);
        brake_lock();
        Serial.println("Retracting");
      }
      while (!dphoto_bac)
      {
        launch_ccw(20);
        delay(20);
        brake_lock();
        photos();
      }
      //      delay(40);
      //      brake_free();
    }
  }

  //---------------------TZ2---------------------------------
  else if (zone2 == 1)
  {
    if (dphoto_bac)
    {
      launch_cw(50);                                 //IF USING 5S BATTERY DONT GIVE MORE THAN 160 PWM ON ANY POINT.........!!!!!!!!!
      Serial.println("Throwing");
    }
    if (dphoto_forw)
    {
      delayMicroseconds(1);//experimnetal
      for (int i = 0; i < 4 ; i++) { //2
        launch_ccw(80);                              //IF USING 5S BATTERY DONT GIVE MORE THAN 160 PWM ON ANY POINT.........!!!!!!!!!
        delay(20);
        brake_lock();
        Serial.println("Retracting");
      }
      while (!dphoto_bac)
      {
        launch_ccw(20);
        delay(20);
        brake_lock();
        photos();
      }
      //      delay(25);
      //      brake_free();



    }
  }
  //----------------------_TZ3--------------------------------
  else if (zone3 == 1)
  {
    if (dphoto_bac)
    {
      launch_cw(50);                                 //IF USING 5S BATTERY DONT GIVE MORE THAN 160 PWM ON ANY POINT.........!!!!!!!!!
      Serial.println("Throwing");
    }
    if (dphoto_forw)
    {
      delayMicroseconds(1);//experimnetal
      for (int i = 0; i < 4 ; i++) { //2
        launch_ccw(80);                              //IF USING 5S BATTERY DONT GIVE MORE THAN 160 PWM ON ANY POINT.........!!!!!!!!!
        delay(20);
        brake_lock();
        Serial.println("Retracting");
      }
      while (!dphoto_bac)
      {
        launch_ccw(20);
        delay(20);
        brake_lock();
        photos();
      }
      //      delay(25);
      //      brake_free();



    }
  }
  else
  {
    brake_free();
  }
}


void launch_ccw(int spd)
{
  digitalWrite(a, 0);
  digitalWrite(b, 1);
  analogWrite(pwm, spd);
}
void launch_cw(int spd)
{
  digitalWrite(a, 1);
  digitalWrite(b, 0);
  analogWrite(pwm, spd);
}
void brake_free()
{
  digitalWrite(a, 0);
  digitalWrite(b, 0);
  analogWrite(pwm, 0);
}
void brake_lock()
{
  digitalWrite(a, 1);
  digitalWrite(b, 1);
  analogWrite(pwm, 180); //IF USING 5S BATTERY DONT GIVE MORE THAN 160 PWM ON ANY POINT.........!!!!!!!!!
}
void photos()
{ dphoto_forw = digitalRead(photo_forw);
  dphoto_bac = digitalRead(photo_bac);

  zone1 = digitalRead(tz1);
  zone2 = digitalRead(tz2);
  zone3 = digitalRead(tz3);
}


//-------------------------------------------------------
void debug()
{

  Serial.print("Photo_FWD:" + String(dphoto_forw));
  Serial.print("\t");
  Serial.print("Photo_BK:" + String(dphoto_bac));
  Serial.print("\t");
  Serial.print("Zone 1:" + String(zone1));
  Serial.print("\t");
  Serial.print("Zone 2:" + String(zone2));
  Serial.print("\t");
  Serial.println("Zone 3:" + String(zone3));

}

