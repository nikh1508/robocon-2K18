void laun_ccw(int spd)
{
digitalWrite(launcher.a,1);
digitalWrite(launcher.b,0);
analogWrite(launcher.pwm,spd);
}
void laun_cw(int spd)
{
digitalWrite(launcher.a,0);
digitalWrite(launcher.b,1);
analogWrite(launcher.pwm,spd);
}
void laun_brak()
{
digitalWrite(launcher.a,0);
digitalWrite(launcher.b,0);
analogWrite(launcher.pwm,0);
}
void laun_brakF()
{
digitalWrite(launcher.a,1);
digitalWrite(launcher.b,1);
analogWrite(launcher.pwm,0);
}
void launcher_sens()
{launcher.dphoto=!digitalRead(launcher.photo);
launcher.dphotostop=!digitalRead(launcher.photostop);
launcher.dphotocock=!digitalRead(launcher.photocock);}

void laun_debug()
//{Serial.print("phot ");Serial.println(!digitalRead(launcher.photo));
{
if (Serial.available())
{Serial.print("phot ");Serial.println(!digitalRead(launcher.photo));
Serial.print("phot stop ");Serial.println(!digitalRead(launcher.photostop));
Serial.print("phot cock");Serial.println(!digitalRead(launcher.photocock));
char a=Serial.read();
//if ('c'==a)
//{laun_cw(255);delay(10);laun_brak();Serial.println("cw");}
//if ('x'==a)
//{laun_ccw(255);delay(10);laun_brak();Serial.println("ccw");}
//if ('b'==a)
//{laun_brak();Serial.println("brak");}
//}
}}

