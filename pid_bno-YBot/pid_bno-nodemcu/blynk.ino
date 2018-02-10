BLYNK_CONNECTED() {
  Blynk.syncAll();
}

BLYNK_APP_CONNECTED() {
  Blynk.syncAll();
}

BLYNK_APP_DISCONNECTED() {
  initialize_default();
}

BLYNK_WRITE(V0) {
  slider = param.asInt();
}


BLYNK_WRITE(V1) {
  kp_data = param.asInt();
}

BLYNK_WRITE(V2) {
  ki_data = param.asInt();
}

BLYNK_WRITE(V3) {
  kd_data = param.asInt();
}

BLYNK_WRITE(V4) {
  power = param.asInt();
}

