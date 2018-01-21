BLYNK_CONNECTED() {
  Blynk.syncAll();
}

BLYNK_APP_CONNECTED() {
  Blynk.syncAll();
}

BLYNK_APP_DISCONNECTED() {
  initialize_default();
}
BLYNK_WRITE(V0)
{
  fwd=param.asInt();
}
BLYNK_WRITE(V1)
{
  bkd=param.asInt();
}

BLYNK_WRITE(V2)
{
  left=param.asInt();
}

BLYNK_WRITE(V3)
{
  right=param.asInt();
}
BLYNK_WRITE(V4)
{
  slider=param.asInt();
}
BLYNK_WRITE(V5)
{
  power=param.asInt();
}
BLYNK_WRITE(V6)
{
  cw=param.asInt();
}
BLYNK_WRITE(V7)
{
  ccw=param.asInt();
}






