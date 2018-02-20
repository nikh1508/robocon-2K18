void launch()
{   //--------------------------TZ1-------------------------------
  if(shoot && zp1==0 && zp2==0)
  {
    
       if(dphoto_bac)
    {
      launch_cw(85);                                 //IF USING 5S BATTERY DONT GIVE MORE THAN 159 PWM ON ANY POINT.........!!!!!!!!!
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
   }

   //---------------------TZ2---------------------------------
   else if(shoot && (zp1^zp2))
   {
      if(dphoto_bac)
    {
      launch_cw(120);                                 //IF USING 5S BATTERY DONT GIVE MORE THAN 160 PWM ON ANY POINT.........!!!!!!!!!
      Serial.println("Throwing");
    }
     if (dphoto_forw)
    {
      delayMicroseconds(50);//experimnetal
      for (int i = 0; i < 4 ; i++) { //2
        launch_ccw(140);                              //IF USING 5S BATTERY DONT GIVE MORE THAN 160 PWM ON ANY POINT.........!!!!!!!!!
        delay(20);
        brake_lock();
        Serial.println("Retracting");
      }
    

      
    } 
   }
   //----------------------_TZ3--------------------------------
   else if(shoot && (zp1&&zp2))
   {
    if(dphoto_bac)
    {
      launch_cw(148);                                 //IF USING 5S BATTERY DONT GIVE MORE THAN 160 PWM ON ANY POINT.........!!!!!!!!!
      Serial.println("Throwing");
    }
     if (dphoto_forw)
    {
      delayMicroseconds(60);//experimnetal
      for (int i = 0; i < 4 ; i++) { //2
        launch_ccw(150);                              //IF USING 5S BATTERY DONT GIVE MORE THAN 160 PWM ON ANY POINT.........!!!!!!!!!
        delay(20);
        brake_lock();
        Serial.println("Retracting");
      }
    

      
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
 
  dshoot=digitalRead(shoot);
  zp1=digitalRead(zone_pin1);
  zp2=digitalRead(zone_pin2);
}


//-------------------------------------------------------
void debug()
{
  
  Serial.print("Photo_FWD:" + String(dphoto_forw));
  Serial.print("\t");
  Serial.print("Photo_BK:" + String(dphoto_bac));
  Serial.print("\t");
  Serial.print("Shoot:" + String(dshoot));
  Serial.print("\t");
  Serial.print("Zone 1:"+String(zp1));
  Serial.print("\t");
  Serial.println("Zone 2:" +String(zp2));
  
}

