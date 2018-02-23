bool receiving_data = false;
struct data {
  int fwd, bkd, left, right, cw, ccw;
  int slider = 0;
  int power = 0;
  int motion;
  int curr_motion = 0;
  int pneumatic;
  int dcv_l, dcv_r;
  int belt_l, belt_r;
} bot_data;

void check_motion() {
  if (!(bot_data.fwd || bot_data.bkd || bot_data.left || bot_data.right || bot_data.cw || bot_data.ccw ))
    bot_data.motion = 0;
}

void check_pneumatic() {
  if (!(bot_data.belt_l || bot_data.belt_r || bot_data.dcv_l || bot_data.dcv_r))
    bot_data.pneumatic = 0;
}
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
      if (!(type == 'p' || type == 'f' || type == 'b' || type == 'l' || type == 'r' || type == 'o' || type == 'c' || type == 'd' || type == 'v' || type == 'w' || type == 'x' || type == 'y'))continue;
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
        case 'v':
          if (bot_data.dcv_l != val) didchange = true;
          bot_data.dcv_l = val;
          if (bot_data.dcv_l)
            bot_data.pneumatic = 1;
          break;
        case 'w':
          if (bot_data.dcv_r != val) didchange = true;
          bot_data.dcv_r = val;
          if (bot_data.dcv_r)
            bot_data.pneumatic = 1;
          break;
        case 'x':
          if (bot_data.belt_l != val) didchange = true;
          bot_data.belt_l = val;
          if (bot_data.belt_l)
            bot_data.pneumatic = 2;
          break;
        case 'y':
          if (bot_data.belt_r != val) didchange = true;
          bot_data.belt_r = val;
          if (bot_data.belt_r)
            bot_data.pneumatic = 2;
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
  Serial.print("DV_L:" + String(bot_data.dcv_l)); Serial.print("\t");
  Serial.print("DV_R:" + String(bot_data.dcv_r)); Serial.print("\t");
  Serial.print("BT_L:" + String(bot_data.belt_l)); Serial.print("\t");
  Serial.print("BT_R:" + String(bot_data.belt_r)); Serial.print("\t");
  Serial.print("PN:" + String(bot_data.pneumatic)); Serial.print("\t");
  Serial.println("P:" + String(bot_data.power));
}


void setup() {
  // put your setup code here, to run once:
Serial1.begin(115200);
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
update_data();
check_motion();
check_pneumatic();
print_recv_data();
}
