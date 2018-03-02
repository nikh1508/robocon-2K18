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
      Serial.print(dshoot); Serial.print("\t"); Serial.print(zp1); Serial.print("\t"); Serial.print(zp2);
      launch(); 
    }
  }
}

