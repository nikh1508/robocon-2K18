void loop() {
  //  bno();
  /////////
  if (engine[select].tz[loco] == 5 && step[0].stepcount >= step[0].set_stepcount)
    read_feed();
  if (engine[select].tz[loco] == 2 && step[0].stepcount >= step[0].set_stepcount)
    feedback_3 = digitalRead(9);
  /////////
  filter();
  /////////
  error_interrupt();
  //////////////////////////////////////////////////////
  //  setup_run();
  //////////////////////////////////////////////////////
  if (flag_drive == true)
    drive();
  ///////////////////////////////////////////////////
  if (feedback_1 == LOW && feedback_2 == HIGH && engine[select].tz[loco] == 5 && flag_arena[0] == true && step[0].stepcount >= step[0].set_stepcount) {
    select = 0;
    loco = 0;
    engine[select].tz[loco] = 0;
    flag_drive = true;
    ping = 1;
  }
  ///////
  if (feedback_1 == HIGH && feedback_2 == HIGH && engine[select].tz[loco] == 5 && flag_arena[1] == true && step[0].stepcount >= step[0].set_stepcount) {
    flag_arena[0] = false;
    flag_arena[1] = false;
    select = 1;
    loco = 0;
    engine[select].tz[loco] = 0;
    flag_drive = true;
    ping = 2;
  }
  //////
  if (feedback_1 == HIGH && feedback_2 == HIGH && engine[select].tz[loco] == 5 && flag_arena[1] == false && step[0].stepcount >= step[0].set_stepcount) {
    select = 2;
    loco = 0;
    engine[select].tz[loco] = 0;
    flag_drive = true;
    ping = 3;
  }
  /////
  if (feedback_1 == LOW && feedback_2 == HIGH && engine[select].tz[loco] == 5 && flag_arena[0] == false && step[0].stepcount >= step[0].set_stepcount) {
    select = 3;
    loco = 0;
    engine[select].tz[loco] = 0;
    flag_drive = true;
    ping = 4;
  }
  ////
//      Serial.print(feedback_1); Serial.print("   "); Serial.print(feedback_2); Serial.print("   "); Serial.println(feedback_3);

  //////

  //////////////////////////////////////////////
  /////////////////////////////////////////////
  //Serial.print(step[0].stepcount); Serial.print("  "); Serial.print(OCR1A); Serial.print("   "); Serial.print(c); Serial.print("  "); Serial.println(ping);

  //  Serial.print(feedback_1); Serial.print("  "); Serial.println(feedback_2);

  //  Serial.print(OCR1A); Serial.print("  "); Serial.println(step[0].stepcount);

  //  Serial.print(feedback_1); Serial.print("   "); Serial.print(feedback_2); Serial.print("   "); Serial.print(feedback_3);Serial.print(" ping=");Serial.println(ping);
}
