void loop()
{
// Serial2.write(60);
//    delay(100);
    // motorA(3);
        //motorB(0);
       // motorC(3);
        //  motorD(0);
//        if(Serial.available())
//        {char c=Serial.read();
//        if (c=='s')
//         flag=1;
//        if((flag==1))
//        {intial_motion();
//        flag=0;c='o';
//        }
// 
//        
//        
//       
//       
//        
//        
//          }
 //s2.motor(2,map(constrain(10,-lim,lim), 100, -100, -127,127));
  // s1.motor(1,map(constrain(0,-lim,lim), 100, -100, -127,127));
// s2.motor(1,map(constrain(10,-lim,lim), 100, -100, 127,-127));
// s1.motor(2,map(constrain(10,-lim,lim), 100, -100, -127,127));
        

   }
   void freewheel_on()
   {   Serial2.print("Q1:2047\r\n");
      Serial2.print("Q2:2047\r\n");
      Serial3.print("Q1:2047\r\n");
      Serial3.print("Q2:2047\r\n");}
      void freewheel_off()
      {      Serial2.print("Q1:-2047\r\n");
      Serial2.print("Q2:-2047\r\n");
      Serial3.print("Q1:-2047\r\n");
      Serial3.print("Q2:-2047\r\n");
        }
