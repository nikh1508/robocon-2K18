#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

BlynkTimer timer_event;
BlynkTimer timer1_event;

char auth[] = "171da3f4adbb48f08f77eeec9368acbc";

char ssid[] = "Robocon";
char pass[] = "whatpassword";

char power, slider, kp_data, ki_data, kd_data, l_motor, r_motor;
double kp, ki, kd;

void initialize_default() {
  kp_data = ki_data = kd_data = 0;
  power = 0;
  slider = 0;
  kp = ki = kd = 0.0;
  l_motor = r_motor = 0;
}


void send_data(char point, char data) {
  Serial.print('s');
  Serial.print(point);
  Serial.print(data);
}

void update_data() {
  send_data('p', kp_data);
  send_data('i', ki_data);
  send_data('d', kd_data);
  send_data('o', power);
  send_data('l', slider);
}
byte read() {
  while (!Serial.available()) {}
  return Serial.read();
}

//void get_data() {
//  if (read() == 's') {
//    byte type = read();
//    if (!(type == 'l' || type == 'r')) return;
//        byte val = read();
//
//    switch (type) {
//      case 'l':
//          l_motor = val;
//          Blynk.virtualWrite(V0, l_motor);
//          break;
//        case 'r':
//          r_motor = val;
//          Blynk.virtualWrite(V1, r_motor);
//          break;
//      }
//  }
//}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  Blynk.begin(auth, ssid, pass, IPAddress(192, 168, 0, 108), 8442);
  timer_event.setInterval(100L, update_data);
  initialize_default();
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer_event.run();
}
