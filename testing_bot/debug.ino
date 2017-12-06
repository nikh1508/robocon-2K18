void call_debug() {
  Serial.print("\nBot is in Debug Mode. Choose from the options below.\n\t1.Motor Test\n\t2.BNO Data Test\n\t3.Bluetooth Test\n\t4.Run I2C Scanner.\nEnter your option(1-4):");
  while (!Serial.available());
  int opt = Serial.parseInt();
  if (opt < 1 || opt > 4) {
    Serial.println("Wrong Choice. Try Again.");
    return;
  }
  Serial.println(opt);
  switch (opt) {
    case 1:
tag1: Serial.print("Choose the Motor for Testing:\n\t1.Left\n\t2.Right\n\t3.Both\n\t4.Main Menu\nEnter your option(1-4):");
      while (!Serial.available());
      opt = Serial.parseInt();
      Serial.println(opt);
      if (opt < 1 || opt > 4) {
        Serial.println("Wrong Choice. Try again.");
        goto tag1;
      }
      else if (opt == 4) loop();
tag2:  Serial.print("Enter values -255 to 255. Motors will run at this PWM for 2sec. Entering values out of this range will take you back.Enter Values:");
      while (!Serial.available());
      spd = Serial.parseInt();
      Serial.println(spd);
      if (spd > 255 || spd < -255) goto tag1;
      move_motors(spd, opt);
      delay(2000);
      stop_motors(3);
      goto tag2;
      break;

    case 2:
      Serial.println("Send any character to return to Main Menu.");
      delay(1000);
      Serial.println("Displaying BNO Data:");
tag3: Serial.println("X=" + String(get_angle('x')) + "     " + "Y=" + String(get_angle('y')) + "     " + "Z=" + String(get_angle('z')));
      if (Serial.available()) {
        Serial.flush();
        loop();
      }
      else goto tag3;
      break;

    case 3:
      Serial.println("Starting Bluetooth Testing.Send \"close()\" from Serial Monitor to close this portal and return back to main menu.");
tag4: if (bt.available()) {
        while (bt.available()) {
          char ch = bt.read();
          Serial.print(ch);
        }
        Serial.println();
      }
      if (Serial.available())
      { str1 = Serial.readString();
        if (str1 == "close()") {
          Serial.println("Closing Portal"); return;
        }
        bt.println(Serial.readString());
      }
      goto tag4;
      break;

    case 4:
      i2c_scanner();
      Serial.flush();
      return;
      break;

    default:
      Serial.println("Wrong choice. Try Again.");
  }

}

