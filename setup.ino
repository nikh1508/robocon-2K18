#define debug false;


void setup()
{
  Serial.begin(9600);
  setup_motor();

}

void setup_motor()
{ 
  Serial2.begin(9600);
  Serial3.begin(9600);
  
}
