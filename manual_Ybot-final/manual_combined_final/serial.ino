bool receiving_data = false;

byte read() {
  if (receiving_data) {
    while (!Serial1.available()) {}
    return Serial1.read();
  }
  else if (Serial1.available()) {
    return Serial1.read();
  }
  else
    return '\0';
}

bool update_data() {
  bool didchange = false;
  if (read() == 's') {
    receiving_data = true;
    while (receiving_data) {
      byte type = read();
      if (!(type == 'p' || type == 'f' || type == 'b' || type == 'l' || type == 'r' || type == 'o' || type == 'c' || type == 'd'))continue;
      byte val = read();
      switch (type) {
        case 'p':
          if (bot_data.slider != val) didchange = true;
          bot_data.slider = val;
          break;
        case 'f':
          if (bot_data.fwd != val) didchange = true;
          bot_data.fwd = val;
          if (bot_data.fwd)
            bot_data.motion = 1;
          break;
        case 'b':
          if (bot_data.bkd != val) didchange = true;
          bot_data.bkd = val;
          if (bot_data.bkd)
            bot_data.motion = 2;
          break;
        case 'l':
          if (bot_data.left != val) didchange = true;
          bot_data.left = val;
          if (bot_data.left)
            bot_data.motion = 3;
          break;
        case 'r':
          if (bot_data.right != val) didchange = true;
          bot_data.right = val;
          if (bot_data.right)
            bot_data.motion = 4;
          break;
        case 'c':
          if (bot_data.cw != val) didchange = true;
          bot_data.cw = val;
          if (bot_data.cw)
            bot_data.motion = 5;
          break;
        case 'd':
          if (bot_data.ccw != val) didchange = true;
          bot_data.ccw = val;
          if (bot_data.ccw)
            bot_data.motion = 6;
          receiving_data = false;                                                             //last data received
          break;
        case 'o':
          if (bot_data.power != val) didchange = true;
          bot_data.power = val;
          break;
      }
    }
    return didchange;
  }
  return didchange;
}

void print_recv_data() {
  Serial.print("F:" + String(bot_data.fwd)); Serial.print("\t");
  Serial.print("B:" + String(bot_data.bkd)); Serial.print("\t");
  Serial.print("L:" + String(bot_data.left)); Serial.print("\t");
  Serial.print("R:" + String(bot_data.right)); Serial.print("\t");
  Serial.print("CW:" + String(bot_data.cw)); Serial.print("\t");
  Serial.print("CCW:" + String(bot_data.ccw)); Serial.print("\t");
  Serial.print("S:" + String(bot_data.slider)); Serial.print("\t");
  Serial.print("M:" + String(bot_data.motion)); Serial.print("\t");
  Serial.println("P:" + String(bot_data.power));
}
