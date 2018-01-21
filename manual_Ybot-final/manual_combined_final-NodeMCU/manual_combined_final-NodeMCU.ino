#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

BlynkTimer timer_event;
BlynkTimer timer1_event;

char auth[] = "f3b63e03dbaf40c7a6c377ddf9504387";

char ssid[] = "Robocon";
char pass[] = "whatpassword";

char power, slider, fwd, bkd, left, right,cw,ccw;


void initialize_default() {
  fwd = 0, bkd = 0, left = 0, right = 0;
   cw=0;ccw=0;
   power = 0;
    slider = 0;

}


void send_data(char point, char data) {
  Serial.print(point);
  Serial.print(data);
}

void update_data() {
  Serial.print('s');
  send_data('f', fwd);
  send_data('b', bkd);
  send_data('l', left);
  send_data('r',right);
  send_data('p', slider);
  send_data('o', power);
  send_data('c',cw);
  send_data('d',ccw);
  
}
byte read() {
  while (!Serial.available()) {}
  return Serial.read();
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  Blynk.begin(auth, ssid, pass, IPAddress(192, 168, 0, 108), 8442);
  timer_event.setInterval(200L, update_data);
  //  timer1_event.setInterval(200L, get_data);
  //  Blynk.virtualWrite(V0, 0);
  //  Blynk.virtualWrite(V1, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer_event.run();
 
}
