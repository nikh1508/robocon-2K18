void loop()
{
// Serial2.write(60);
//    delay(100);
    // motorA(3);
        //motorB(0);
       // motorC(3);
        //  motorD(0);
        if(Serial.available())
        {char c=Serial.read();
        if (c=='s')
         flag=1;
        if((flag==1))
        {intial_motion();
        flag=0;c='o';
        }
 
        
        
       
       
        
        
          }
        
 
   }
