#define debug false;


void setup()
{
  Serial.begin(9600);
  setup_motor();
   control(270);
    delay(2000);
    motor_off();
   control(0);
   delay(2000);
   motor_off();
}

void setup_motor()
{ 
  Serial2.begin(9600);
  Serial3.begin(9600);
  
}
