bool receiving_data=false;
byte read() {
  if(receiving_data){
  while (!Serial1.available()) {}
  return Serial1.read();
  }
  else if(Serial1.available()){
  return Serial1.read();
  }
  else
  return '\0';
}

bool update_data() {
  bool didchange = false;
  if (read() == 's') {
    receiving_data=true;
    byte type = read();
    if (!(type == 'p' || type == 'i' || type == 'd' || type == 'l' || type == 'o')) return didchange;
    byte val = read();

    switch (type) {
      case 'p':
        if (bot_data.kp != val) didchange = true;
        bot_data.kp = (double)val / 4;
        myPID.SetTunings(Kp,Ki,Kd);
        break;
      case 'i':
        if (bot_data.ki != val) didchange = true;
        bot_data.ki = (double)val / 4;
        myPID.SetTunings(Kp,Ki,Kd);
        break;
      case 'd':
        if (bot_data.kd != val) didchange = true;
        bot_data.kd = (double)val / 4;
        myPID.SetTunings(Kp,Ki,Kd);
        break;
      case 'l':
        if (bot_data.slider != val) didchange = true;
        bot_data.slider = val;
        break;
      case 'o':
        if (bot_data.power != val) didchange = true;
        bot_data.power = val;
        break;
    }
    receiving_data=false;
    return didchange;
  }
  return didchange;
}

void print_recv_data() {
  Serial.print(Kp); Serial.print("\t");
  Serial.print(Ki); Serial.print("\t");
  Serial.print(Kd); Serial.print("\t");
  Serial.print(bot_data.slider); Serial.print("\t");
  Serial.println(bot_data.power);
}
