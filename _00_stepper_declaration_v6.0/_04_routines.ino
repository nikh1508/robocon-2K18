void routine_00() {
  step[0].set_stepcount = di_exception;
  c = 'a';
}
void setup_run() {
  if (step[0].stepcount >= step[0].set_stepcount && flag_setup[0] == true) {
    delay(200);
    flag_setup[0] = false;
    flag_setup[1] = false;
    reset_OC();
    step[0].set_stepcount = c15;
    c = 'e';
  }
  if (step[0].stepcount >= step[0].set_stepcount && flag_setup[1] == false) {
    flag_setup[1] = true;
    engine[select].tz[loco] = 5;
  }
}
/////////////////////////
////////////////////////
void assign() {
  engine[4].tz[0] = 0;
  engine[4].tz[1] = 1;
  engine[4].tz[2] = 0;
  engine[4].tz[3] = 5;
  ///////////////////
  engine[0].tz[0] = 0;
  engine[0].tz[1] = 1;
  engine[0].tz[2] = 0;
  engine[0].tz[3] = 2;
  engine[0].tz[4] = 0;
  engine[0].tz[5] = 1;
  engine[0].tz[6] = 0;
  engine[0].tz[7] = 5;//default
  ////////////////////
  engine[1].tz[0] = 0;
  engine[1].tz[1] = 1;
  engine[1].tz[2] = 0;
  engine[1].tz[3] = 1;
  engine[1].tz[4] = 0;
  engine[1].tz[5] = 2;
  engine[1].tz[6] = 0;
  engine[1].tz[7] = 1;
  engine[1].tz[8] = 0;
  engine[1].tz[9] = 5;//default
  ///////////////////
  engine[2].tz[0] = 0;
  engine[2].tz[1] = 1;
  engine[2].tz[2] = 0;
  engine[2].tz[3] = 2;
  engine[2].tz[4] = 0;
  engine[2].tz[5] = 1;
  engine[2].tz[6] = 0;
  engine[2].tz[7] = 5;//default
  /////////////////////
  engine[3].tz[0] = 0;
  engine[3].tz[1] = 1;
  engine[3].tz[2] = 0;
  engine[3].tz[3] = 2;
  engine[3].tz[4] = 0;
  engine[3].tz[5] = 1;
  engine[3].tz[6] = 0;
  engine[3].tz[7] = 5;//default
  //////////////////////////////////////////
  /////////////////////////////////////////
  engine[4].cc[0] = 'a';
  engine[4].cc[1] = 't';
  engine[4].cc[2] = 'e';
  engine[4].cc[3] = 't';
  /////////////////////
  engine[0].cc[0] = 'q';
  engine[0].cc[1] = 't';
  engine[0].cc[2] = 'a';
  engine[0].cc[3] = 't';
  engine[0].cc[4] = 'd';
  engine[0].cc[5] = 't';
  engine[0].cc[6] = 'e';
  engine[0].cc[7] = 't';
  //////////////////////
  engine[1].cc[0] = 'a';
  engine[1].cc[1] = 't';
  engine[1].cc[2] = 'q';
  engine[1].cc[3] = 't';
  engine[1].cc[4] = 'a';
  engine[1].cc[5] = 't';
  engine[1].cc[6] = 'd';
  engine[1].cc[7] = 't';
  engine[1].cc[8] = 'e';
  engine[1].cc[9] = 't';
  //////////////////////
  engine[2].cc[0] = 'q';
  engine[2].cc[1] = 't';
  engine[2].cc[2] = 'a';
  engine[2].cc[3] = 't';
  engine[2].cc[4] = 'd';
  engine[2].cc[5] = 't';
  engine[2].cc[6] = 'e';
  engine[2].cc[7] = 't';
  //////////////////////
  engine[3].cc[0] = 'q';
  engine[3].cc[1] = 't';
  engine[3].cc[2] = 'a';
  engine[3].cc[3] = 't';
  engine[3].cc[4] = 'd';
  engine[3].cc[5] = 't';
  engine[3].cc[6] = 'e';
  engine[3].cc[7] = 't';
  /////////////////////////////////////////
  ////////////////////////////////////////
  engine[4].actual_step[0] = di_exception;
  engine[4].actual_step[2] = c15;
  //////////////////////
  engine[0].actual_step[0] = c90;
  engine[0].actual_step[2] = t1;
  engine[0].actual_step[4] = t1;
  engine[0].actual_step[6] = c90;
  //////////////////////
  engine[1].actual_step[0] = straight;
  engine[1].actual_step[2] = c90;
  engine[1].actual_step[4] = t1;
  engine[1].actual_step[6] = t1;
  engine[1].actual_step[8] = c90;
  /////////////////////
  engine[2].actual_step[0] = c90;
  engine[2].actual_step[2] = t1;
  engine[2].actual_step[4] = t1;
  engine[2].actual_step[6] = c90;
  //////////////////
  engine[3].actual_step[0] = c90;
  engine[3].actual_step[2] = t3;
  engine[3].actual_step[4] = t3;
  engine[3].actual_step[6] = c90;
}
