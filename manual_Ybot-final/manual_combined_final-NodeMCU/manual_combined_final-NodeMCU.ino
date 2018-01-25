/*Data Pointing Character:
  f- forward
  b-backward
  l-left
  r-right
  p-pwm slider
  o-power
  c-clockwise rotation
  d-counter clockwo=ise rotation
  v-left DCV
  w-Right DCV
  x- left belt
  y-right belt
*/

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

BlynkTimer timer_event;
BlynkTimer timer1_event;

char auth[] = "f3b63e03dbaf40c7a6c377ddf9504387";

char ssid[] = "Robocon";
char pass[] = "whatpassword";

char power, slider, fwd, bkd, left, right, cw, ccw, belt_r, belt_l, dcv_l, dcv_r;
char belt_l_fwd, belt_l_rev, belt_r_fwd, belt_r_rev;
char dcv_l_up, dcv_l_down, dcv_r_up, dcv_r_down;

void initialize_default() {
  fwd = 0, bkd = 0, left = 0, right = 0;
  cw = 0; ccw = 0;
  power = 0;
  slider = 0;
  dcv_l = dcv_r = 0;
  belt_l = belt_r = 0;
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
  send_data('r', right);
  send_data('p', slider);
  send_data('o', power);
  send_data('c', cw);
  send_data('v', dcv_l);
  send_data('w', dcv_r);
  send_data('x', belt_l);
  send_data('y', belt_r);
  send_data('d', ccw);
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

void print_recv_data(){
  Serial.print("DL-" + String((int)dcv_l)); Serial.print("\t");
  Serial.print("DR-" + String((int)dcv_r)); Serial.print("\t");
  Serial.print("BL-" + String((int)belt_l)); Serial.print("\t");
  Serial.println("BR-" + String((int)belt_r));
  }
void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  check_belt();
  check_dcv();
  timer_event.run();  
}
