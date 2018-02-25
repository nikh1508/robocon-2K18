void loop() {
  if (engine[select].tz[loco] == 5 && step[0].stepcount >= step[0].set_stepcount)
    read_feed();
  //
  if (engine[select].tz[loco] == 2 && step[0].stepcount >= step[0].set_stepcount) { //launch info pass
    digitalWrite(A1, HIGH);
    digitalWrite(A2, HIGH);
    (select == 0) ? digitalWrite(data_1, HIGH) : ((select == 1 || select == 2) ? digitalWrite(data_2, HIGH) : digitalWrite(data_3, HIGH));
    feedback_3 = digitalRead(redphoto);
  }
  /////////
  filter();
  /////////
  error_interrupt();
  //////////////////////////////////////////////////////
  if (flag_drive == true)
    drive();
  ///////////////////////////////////////////////////
  if (feedback_1 == LOW && feedback_2 == HIGH && engine[select].tz[loco] == 5 && flag_arena[0] == true && step[0].stepcount >= step[0].set_stepcount) {
    select = 0;
    loco = 0;
    engine[select].tz[loco] = 0;
    flag_drive = true;
  }
  ///////
  if (feedback_1 == HIGH && feedback_2 == HIGH && engine[select].tz[loco] == 5 && flag_arena[1] == true && step[0].stepcount >= step[0].set_stepcount) {
    flag_arena[0] = false;
    flag_arena[1] = false;
    select = 1;
    loco = 0;
    engine[select].tz[loco] = 0;
    flag_drive = true;
  }
  //////
  if (feedback_1 == HIGH && feedback_2 == HIGH && engine[select].tz[loco] == 5 && flag_arena[1] == false && step[0].stepcount >= step[0].set_stepcount) {
    select = 2;
    loco = 0;
    engine[select].tz[loco] = 0;
    flag_drive = true;
  }
  /////
  if (feedback_1 == LOW && feedback_2 == HIGH && engine[select].tz[loco] == 5 && flag_arena[0] == false && step[0].stepcount >= step[0].set_stepcount) {
    select = 3;
    loco = 0;
    engine[select].tz[loco] = 0;
    flag_drive = true;
  }
  //  Serial.print("OCR1A= ");Serial.print(OCR1A);Serial.print(" stepcount=");Serial.print(step[0].stepcount);Serial.print(" c=");Serial.println(c);
}
