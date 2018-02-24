void loop() {
  photos();
  if (Serial_debug)
  {
    debug();
  }

    if (manual_mode)
    {
      manual();
    }
    else
    {

      Serial.print(dphoto_forw); Serial.print(dphoto_bac); Serial.print("\t");
      Serial.print(zone1); Serial.print("\t"); Serial.print(zone2); Serial.print("\t"); Serial.print(zone3);
      photos(); 
     
      if(flag)
      {
        read_zone();
        if(zone1==1 || zone2==1 || zone3==1)
        {
          flag=false;
        }
        
      }
      
      launch(); 
    }
  
}

