BLYNK_CONNECTED() {
  Blynk.syncAll();
}

BLYNK_APP_CONNECTED(){
 Blynk.syncAll();
 }

 BLYNK_APP_DISCONNECTED(){
  initialize_default();
  }

BLYNK_WRITE(V0) {
  y = param[0].asInt();
}


BLYNK_WRITE(V1) {
  x = param[1].asInt();
}

BLYNK_WRITE(V2) {
  button = param.asInt();
  //Serial.println("Button::"+String(button));
}

BLYNK_WRITE(V3) {
  slider = param.asInt();
  //Serial.println("Slider::"+String(slider));
}

BLYNK_WRITE(V4) {
  trm = (param.asFloat())*1024;
  trm_data = map(trm, -1024, 1024, 0, 255);
  //Serial.println("Trim::"+String(trm));
}
