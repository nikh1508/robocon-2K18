void function_01() { // straight
  if (flag_func[0] == true) {//first
    flag_func[0] = false;
    routine_00(1760.00, 'a', 0.9997);
  }
  //////////
  if ((fake[0] == true) && (step[2].stepcount >= step[2].set_stepcount - 5)) { //general braking
    c = 't';
    if (step[2].brake >= step[2].set_brake - 5) {
      fake[0] = false;
      flag_func[1] = false;
      flag_reset();
      brake_reset();
    }
  }
  /////////
  if ((flag_func[1] == false) && (step[2].stepcount >= step[2].set_stepcount - 5)) { //general loco
    flag_func[1] = true;
    routine(100.00, 'e', 0.9995);
    fake[1] = true;
  }
  if ((fake[1] == true) && (step[2].stepcount >= step[2].set_stepcount - 5)) {//general braking
    c = 't';
    if (step[2].brake >= step[2].set_brake - 5) {
      fake[1] = false;
      flag_func[2] = false;
      flag_reset();
      brake_reset();
      code_flag[0] = false;
      code_flag[1] = true;
    }
  }
}
void function_02() {
  if (flag_func[2] == false) { //feedback
    flag_func[2] = true;
    routine(400, 'q', 0.9995);
    fake[2] = true;
  }
  //
  if ((fake[2] == true) && (step[2].stepcount >= step[2].set_stepcount - 5)) {//general braking
    c = 't';
    if (step[2].brake >= step[2].set_brake - 5) {
      fake[2] = false;
      flag_func[3] = false;
      flag_reset();
      brake_reset();
    }
  }
  //
  if (flag_func[3] == false) {
    flag_func[3] = true;
    routine(500, 'a', 0.9995);
    fake[3] = true;
  }
  //
  if ((fake[3] == true) && (step[2].stepcount >= step[2].set_stepcount - 5)) {//general braking
    c = 't';
    if (step[2].brake >= step[2].set_brake - 5) {
      fake[3] = false;
      flag_func[4] = false;
      flag_reset();
      brake_reset();
    }
  }
  if (flag_func[4] == false) {
    flag_func[4] = true;
    routine(500, 'd', 0.9995);
    fake[4] = true;
  }
  if ((fake[4] == true) && (step[2].stepcount >= step[2].set_stepcount - 5)) {//general braking
    c = 't';
    if (step[2].brake >= step[2].set_brake - 5) {
      fake[4] = false;
      flag_func[5] = false;
      flag_reset();
      brake_reset();
    }
  }
  if (flag_func[5] == false) {
    flag_func[5] = true;
    routine(400, 'e', 0.9995);
    fake[5] = true;
    //    code_flag[1] = false;
    //    code_flag[2] = true;
  }

  if ((fake[5] == true) && (step[2].stepcount >= step[2].set_stepcount - 5)) {//general braking
    c = 't';
    if (step[2].brake >= step[2].set_brake - 5) {
      fake[5] = false;
      flag_func[6] = false;//function_02 trigger
      flag_reset();
      brake_reset();
      code_flag[1] = false;
      code_flag[2] = true;
    }
  }
  /*if(feedback==tz1)
     code_flag[1] = true;
     flag_func[6] = true;
  */
}
///////////////////////////////////////////////////////////////////
void function_03a() {
  if (flag_func[6] == false) {
    flag_func[6] = true;
    routine(800, 'a', 0.9995);
    fake[6] = true;
  }
  if ((fake[6] == true) && (step[2].stepcount >= step[2].set_stepcount - 5)) {//general braking
    c = 't';
    if (step[2].brake >= step[2].set_brake - 5) {
      fake[6] = false;
      flag_func[7] = false;
      flag_reset();
      brake_reset();
      code_flag[2] = false;
      code_flag[3] = true;
    }
  }
}
void function_03() {
  if (flag_func[7] == false) {
    flag_func[7] = true;
    routine(400, 'q', 0.9995);
    fake[7] = true;
  }
  if ((fake[7] == true) && (step[2].stepcount >= step[2].set_stepcount - 5)) {//general braking
    c = 't';
    if (step[2].brake >= step[2].set_brake - 5) {
      fake[7] = false;
      flag_func[8] = false;
      flag_reset();
      brake_reset();
    }
  }
  if (flag_func[8] == false) {
    flag_func[8] = true;
    routine(800, 'a', 0.9995);
    fake[8] = true;
  }
  if ((fake[8] == true) && (step[2].stepcount >= step[2].set_stepcount - 5)) {//general braking
    c = 't';
    if (step[2].brake >= step[2].set_brake - 5) {
      fake[8] = false;
      flag_func[9] = false;
      flag_reset();
      brake_reset();
    }
  }
  if (flag_func[9] == false) {
    flag_func[9] = true;
    routine(800, 'd', 0.9995);
    fake[9] = true;
  }
  if ((fake[9] == true) && (step[2].stepcount >= step[2].set_stepcount - 5)) {//general braking
    c = 't';
    if (step[2].brake >= step[2].set_brake - 5) {
      fake[9] = false;
      flag_func[10] = false;
      flag_reset();
      brake_reset();
    }
  }
  if (flag_func[10] == false) {
    flag_func[10] = true;
    routine(400, 'e', 0.9995);
    fake[10] = true;
  }
  if ((fake[10] == true) && (step[2].stepcount >= step[2].set_stepcount - 5)) {//general braking
    c = 't';
    if (step[2].brake >= step[2].set_brake - 5) {
      fake[10] = false;
      flag_func[11] = false;
      flag_reset();
      brake_reset();
      code_flag[3] = false;
      code_flag[4] = true;
    }
  }
  /*if(feedback==tz2)
     code_flag[3] = true;
     flag_func[11] = true;
  */
}

