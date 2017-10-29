void setup()
{Serial.begin(9600);
  setup_launcher();
}
void setup_launcher()
{
  pinMode(launcher.a,OUTPUT);
  pinMode(launcher.b,OUTPUT);
  pinMode(launcher.pwm,OUTPUT);
  pinMode(launcher.photo,INPUT);
   pinMode(launcher.photostop,INPUT);
    pinMode(launcher.photocock,INPUT);
}

