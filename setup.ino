#define debug false;


void setup()
{pinMode(8,INPUT_PULLUP);

Serial.begin(9600);
while(digitalRead(8)){};//20v battery
  delay(3000);
  setup_motor();
   s1.setRamping(14);
   s2.setRamping(14);
     freewheel_off();
//     skim_motion();
////     delay(20000);
//     motor_off();
//       freewheel_on();
    control(270);
        delay(2350);
          s1.setRamping(8);
        s2.setRamping(8); 
        control(270+45);
        delay(1050);
          control(0);
        delay(254);
        motor_off();
        delay(1000);
        freewheel_on();
       
 

}

void setup_motor()
{ 
  Serial2.begin(9600);
  //s1.autobaud();
  Serial3.begin(9600);
  //s2.autobaud();
}
