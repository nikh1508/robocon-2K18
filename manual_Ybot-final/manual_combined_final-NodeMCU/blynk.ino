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
  fwd = param.asInt();
}
BLYNK_WRITE(V1)
{
  bkd = param.asInt();
}

BLYNK_WRITE(V2)
{
  left = param.asInt();
}

BLYNK_WRITE(V3)
{
  right = param.asInt();
}
BLYNK_WRITE(V4)
{
  slider = param.asInt();
}
BLYNK_WRITE(V5)
{
  power = param.asInt();
}
BLYNK_WRITE(V6)
{
  cw = param.asInt();
}
BLYNK_WRITE(V7)
{
  ccw = param.asInt();
}
BLYNK_WRITE(V8) {
  dcv_r_up = param.asInt();
}
BLYNK_WRITE(V9) {
  dcv_r_down = param.asInt();
}
BLYNK_WRITE(V10) {
  belt_r_fwd = param.asInt();
}
BLYNK_WRITE(V11) {
  belt_r_rev = param.asInt();
}
BLYNK_WRITE(V12) {
  belt_l_fwd = param.asInt();
}
BLYNK_WRITE(V13) {
  belt_l_rev = param.asInt();
}
BLYNK_WRITE(V14) {
  dcv_l_up = param.asInt();
}
BLYNK_WRITE(V15) {
  dcv_l_down = param.asInt();
}


void check_belt() {
  if (belt_l_fwd)
    belt_l = 1;
  else if (belt_l_rev)
    belt_l = 2;
  else
    belt_l = 0;


  if (belt_r_fwd)
    belt_r = 1;
  else if (belt_r_rev)
    belt_r = 2;
  else
    belt_r = 0;
}

void check_dcv() {
  if (dcv_l_up)
    dcv_l = 1;
  else if (dcv_l_down)
    dcv_l = 2;
  else
    dcv_l = 0;


  if (dcv_r_up)
    dcv_r = 1;
  else if (dcv_r_down)
    dcv_r = 2;
  else
    dcv_r = 0;
}




