void setup() {
  Serial.begin(9600);
  setup_launcher();
}
void setup_launcher()
{
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(pwm, OUTPUT);
  pinMode(photo_forw, INPUT);
  pinMode(photo_bac, INPUT);
 
  pinMode(shoot,INPUT);
  pinMode(zone_pin1,INPUT);
  pinMode(zone_pin2,INPUT);
}
