void loop() {
  photos();
  if (Serial_debug)
  {
    debug();
  }
  else
  {
    if (manual_mode)
    {
      manual();
    }
    else
    {

      Serial.print(dphoto_forw); Serial.print(dphoto_bac); Serial.print("\t");
      Serial.print(zone1); Serial.print("\t"); Serial.print(zone2); Serial.print("\t"); Serial.print(zone3);
      photos();
      launch(); 
    }
  }
}

