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
 
  pinMode(tz1,INPUT);
  pinMode(tz2,INPUT);
  pinMode(tz3,INPUT);
}
