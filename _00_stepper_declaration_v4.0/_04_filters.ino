void increment_0() {
  filter[0].output = ((filter[0].alpha_a) * filter[0].initial) + ((1 - (filter[0].alpha_a)) * (filter[0].target));
  filter[0].initial = filter[0].output;
  filter[0].output = filter[0].rev - filter[0].output;
  OCR1A = int(filter[0].output);
}
void increment_1() {
  filter[1].output = ((filter[1].alpha_a) * filter[1].initial) + ((1 - (filter[1].alpha_a)) * (filter[1].target));
  filter[1].initial = filter[1].output;
  filter[1].output = filter[1].rev - filter[1].output;
  OCR3A = int(filter[1].output);
}
void increment_2() {
  filter[2].output = ((filter[2].alpha_a) * filter[2].initial) + ((1 - (filter[2].alpha_a)) * (filter[2].target));
  filter[2].initial = filter[2].output;
  filter[2].output = filter[2].rev - filter[2].output;
  OCR4A = int(filter[2].output);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void decrement_0() {
  if (flag[0] == true) {
    filter[0].initial = OCR1A;
    flag[0] = false;
  }
  filter[0].output = ((filter[0].alpha_b) * filter[0].initial) + ((1 - (filter[0].alpha_b)) * (filter[0].target));
  filter[0].initial = filter[0].output;
  OCR1A = int(filter[0].output);
}
void decrement_1() {
  if (flag[1] == true) {
    filter[1].initial = OCR3A;
    flag[1] = false;
  }
  filter[1].output = ((filter[1].alpha_b) * filter[1].initial) + ((1 - (filter[1].alpha_b)) * (filter[1].target));
  filter[1].initial = filter[1].output;
  OCR3A = int(filter[1].output);
}
void decrement_2() {
  if (flag[2] == true) {
    filter[2].initial = OCR4A;
    flag[2] = false;
  }
  filter[2].output = ((filter[2].alpha_b) * filter[2].initial) + ((1 - (filter[2].alpha_b)) * (filter[2].target));
  filter[2].initial = filter[2].output;
  OCR4A = int(filter[2].output);
}
