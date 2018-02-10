void global_initialize() {
  for (i = 0; i < 3; i++) {
    step[i].multiplier = 9;
    step[i].divisor = 10;
    filter[0].target = 2100;
    filter[1].target = 2100;
    filter[2].target = 2100;
    step[i].set_brake = 400;
  }
}
//////////////////////////////////
void routine_00(double step0,char ch,double alpha) {
  c=ch;
  //
  filter[0].initial = 5;
  filter[0].initial_a = 5;
  filter[0].rev = filter[0].initial_a + filter[0].target;
  filter[0].alpha_a = alpha;
  filter[0].alpha_b = 0.99991;
  step[0].stepcount = 0;
  step[0].set_stepcount = step0;
  //
  filter[1].initial = 5;
  filter[1].initial_a = 5;
  filter[1].rev = filter[1].initial_a + filter[1].target;
  filter[1].alpha_a = alpha;
  filter[1].alpha_b = 0.99991;
  step[1].stepcount = 0;
  step[1].set_stepcount = step0;
  //
  filter[2].initial = 5;
  filter[2].initial_a = 5;
  filter[2].rev = filter[2].initial_a + filter[2].target;
  filter[2].alpha_a = alpha;
  filter[2].alpha_b = 0.99991;
  step[2].stepcount = 0;
  step[2].set_stepcount = step0;
}
//////////////////////////////////////
void routine(double step0,char ch,double alpha) {
  c=ch;
  //
  filter[0].initial = 5;
  filter[0].initial_a = 5;
  OCR1A = 2100;
  filter[0].rev = filter[0].initial_a + filter[0].target;
  filter[0].alpha_a = alpha;
  filter[0].alpha_b = 0.99991;
  step[0].stepcount = 0;
  step[0].set_stepcount = step0;
  //
  filter[1].initial = 5;
  filter[1].initial_a = 5;
  OCR3A = 2100;
  filter[1].rev = filter[1].initial_a + filter[1].target;
  filter[1].alpha_a = alpha;
  filter[1].alpha_b = 0.99991;
  step[1].stepcount = 0;
  step[1].set_stepcount = step0;
  //
  filter[2].initial = 5;
  filter[2].initial_a = 5;
  OCR4A = 2100;
  filter[2].rev = filter[2].initial_a + filter[2].target;
  filter[2].alpha_a = alpha;
  filter[2].alpha_b = 0.99991;
  step[2].stepcount = 0;
  step[2].set_stepcount = step0;
}
//////////////////////////////////////
