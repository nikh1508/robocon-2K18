void setup() {
  Serial.begin(9600);
  bt.begin(9600);
  //startup_tone();
 declare_pins();

  if (!bno.begin())
  {
    Serial.print("BNO not detected. Check connections or I2C ADDR!(Run I2C Scanner in Debug Mode.)");
    if (!debug) while (1);
  }
  delay(1000);
  bno.setExtCrystalUse(true);
  pid.SetTunings(0, 0, 0);
}


