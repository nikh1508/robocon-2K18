void drive() {
  switch (engine[select].tz[loco]) {
    case (0): {
        reset_OC();
        step[0].set_stepcount = engine[select].actual_step[loco];
        c = engine[select].cc[loco];
        loco++;
        feedback_1 = LOW;
        feedback_2 = LOW;
        feedback_3 = LOW;
        digitalWrite(A1, LOW);
        digitalWrite(A2, LOW);
        pin_reset();
        break;
      }
    case (1): {
        if (step[0].brake >= step[0].set_brake) {
          loco++;
          feedback_1 = LOW;
          feedback_2 = LOW;
          feedback_3 = LOW;
          pin_reset();
          break;
        }
      }
    case (2): {
        if (step[0].brake >= step[0].set_brake && feedback_3 == 1) {
          loco++;
          feedback_1 = LOW;
          feedback_2 = LOW;
          feedback_3 = LOW;
          pin_reset();
          break;
        }
      }
    case (4): {//buffer
        break;
      }
    case (5): { //default
        flag_drive = false;
        feedback_1 = LOW;
        feedback_2 = LOW;
        feedback_3 = LOW;
        pin_reset();
        break;
      }
  }
}
