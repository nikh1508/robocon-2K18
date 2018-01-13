#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

BlynkTimer timer_event;

char auth[] = "cb6b5198a212417e9578367af827cb85";

char ssid[] = "Robocon";
char pass[] = "whatpassword";

char x, y, button, slider, trm_data;
float trm;

void initialize_default() {
  x = y = 128;
  button = 0;
  slider = 0;
  trm_data = 127;
}

void send_data(char point, char data) {
  Serial.print('s');
  Serial.print(point);
  Serial.print(data);
}

void update_data() {
  send_data('x', x);
  send_data('y', y);
  send_data('p', button);
  send_data('l', slider);
  send_data('t', trm_data);
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, IPAddress(192, 168, 0, 108), 8442);
  timer_event.setInterval(70L, update_data);
}

void loop()
{
  Blynk.run();
  timer_event.run();
}
