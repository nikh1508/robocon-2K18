void launch()
{
  if (zone1 == 1)
  {
    if (dphoto_bac)
    {
      launch_cw(72);
      Serial.println("Throwing");
    }

    if (dphoto_forw )
    {

      delayMicroseconds(1);//experimnetal
      for (int i = 0; i < 4 ; i++) { //2
        launch_ccw(72);                              //IF USING 5S BATTERY DONT GIVE MORE THAN 159 PWM ON ANY POINT.........!!!!!!!!!
        delay(20);
        brake_lock();
        Serial.println("Retracting");
      }

      while (!dphoto_bac)
      {
        launch_ccw(10);
        delay(20);
        brake_lock();
        photos();
      }
      flag = true;
    }
  }

  if (zone2 == 1)
  {
    if (dphoto_bac)
    {
      launch_cw(107);
      Serial.println("Throwing");
    }

    if (dphoto_forw )
    {

      delayMicroseconds(17000);//experimnetal
      for (int i = 0; i < 4 ; i++) { //2
        launch_ccw(107);                              //IF USING 5S BATTERY DONT GIVE MORE THAN 159 PWM ON ANY POINT.........!!!!!!!!!
        delay(20);
        brake_lock();
        Serial.println("Retracting");
      }

      while (!dphoto_bac)
      {
        launch_ccw(10);
        delay(20);
        brake_lock();
        photos();
      }
      flag = true;
    }
  }
  if (zone3 == 1)
  {
    if (dphoto_bac)
    {
      launch_cw(142);
      Serial.println("Throwing");
    }

    if (dphoto_forw )
    {

      delayMicroseconds(5000);//experimnetal
      for (int i = 0; i < 4 ; i++) { //2
        launch_ccw(144);                              //IF USING 5S BATTERY DONT GIVE MORE THAN 159 PWM ON ANY POINT.........!!!!!!!!!
        delay(20);
        brake_lock();
        Serial.println("Retracting");
      }

      while (!dphoto_bac)
      {
        launch_ccw(10);
        delay(20);
        brake_lock();
        photos();
      }
      flag = true;
    }
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


}
void read_zone()
{
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

