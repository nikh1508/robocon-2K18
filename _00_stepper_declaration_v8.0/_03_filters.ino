void global_increment() {
  ny = nx * nm + nc;
  OCR1A = int(ny);
  OCR3A = int(ny);
  OCR4A = int(ny);
  nx = nx + 1;
}
///////////////////////////////
void global_decrement() {
  ny = nx * nm + nc;
  OCR1A = int(ny);
  OCR3A = int(ny);
  OCR4A = int(ny);
  nx = nx - 1;
}
void filter() {
  if ((step[0].stepcount <= part * step[0].set_stepcount) && (c != 't') && OCR1A >= max_speed)
    global_increment();
  /////////////////
  if ((step[0].stepcount > part * step[0].set_stepcount) && (c != 't') && OCR1A <= least_speed)
    global_decrement();
  ////////////////
  if (step[0].stepcount >= step[0].set_stepcount) {
    c = 't';
  }
}
