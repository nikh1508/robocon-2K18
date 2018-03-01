void startup() {
  write_motors(+27, +300, -300);
  delay(SIDEWAYS_DELAY);
  stop_all();
  delay(MOTOR_DELAY);
  forward_enc(FAST_SPEED, START_TO_A, 0);  // A
  delay(MOTOR_DELAY);
  rotate_to_angle(90, CW);
  delay(MOTOR_DELAY);
  backward(200, 50, 90);  // Sunfounder Offset
  delay(MOTOR_DELAY);
  backward_enc(FAST_SPEED, -A_TO_BLUE, 90); // BLUE LINE (TZ1)
}

void tz1() {
  // BLUE -->
  backward_enc(FAST_SPEED, -BLUE_TO_TZ1, 90);  // TZ1
  delay(MOTOR_DELAY);
  rotate_to_angle(0, CCW);
  delay(MOTOR_DELAY);
  // digitalWrite(99,HIGH);
  backward_enc(250, -TZ1_TO_FENCE, 0, true);  // FENCE
  write_motors(BRAKE, FENCE_SPEED, FENCE_SPEED);
  launch(1);
  // digitalWrite(99,LOW);
  delay(MOTOR_DELAY);
  
  forward(200, FENCE_TO_TZ1, 0);  // TZ1
  delay(MOTOR_DELAY);
  rotate_to_angle(90, CW);
  delay(MOTOR_DELAY);
  forward_enc(FAST_SPEED, TZ1_TO_BLUE, 90);  // BLUE

 
}

void tz1_to_tz2() {
  // BLUE ->
  forward_enc(FAST_SPEED, TZ1BLUE_OFFSET, 90);
  rotate_to_angle(0, CCW);
  forward(FAST_SPEED, A_TO_B, 0);  // A2B
  rotate_to_angle(90, CW);
  backward(FAST_SPEED, -OFFSET_TO_TZ2, 90);
  rotate_to_angle(0, CCW);
  delay(MOTOR_DELAY);
  // digitalWrite(99,HIGH);
  backward_enc(250, -TZ1_TO_FENCE, 0, true);  // FENCE
  write_motors(BRAKE, -FENCE_SPEED, -FENCE_SPEED);
  launch(2);
  // digitalWrite(99,LOW);
  forward(200, FENCE_TO_TZ1, 0);  // TZ2
  delay(MOTOR_DELAY);
  rotate_to_angle(90, CW);
  delay(MOTOR_DELAY);
  forward_enc(FAST_SPEED, TZ1_TO_BLUE, 90);
}

void tz2() {
  backward_enc(FAST_SPEED, -BLUE_TO_TZ1, 90);  // TZ1
  delay(MOTOR_DELAY);
  rotate_to_angle(0, CCW);
  delay(MOTOR_DELAY);
  // digitalWrite(99,HIGH);
  backward_enc(250, -TZ1_TO_FENCE, 0, true);  // FENCE
  write_motors(BRAKE, -FENCE_SPEED, -FENCE_SPEED);
  launch(2);
  // digitalWrite(99,LOW);
  forward(200, FENCE_TO_TZ1, 0);  // TZ1
  delay(MOTOR_DELAY);
  rotate_to_angle(90, CW);
  delay(MOTOR_DELAY);
  forward_enc(FAST_SPEED, BLUE_TO_TZ1, 90);  // BLUE
}

void tz3() {
  backward_enc(FAST_SPEED, -BLUE_TO_TZ3, 90);  // TZ1
  delay(MOTOR_DELAY);
  rotate_to_angle(0, CCW);
  delay(MOTOR_DELAY);
  // digitalWrite(99,HIGH);
  backward_enc(250, -TZ1_TO_FENCE, 0, true);  // FENCE
  write_motors(BRAKE, -FENCE_SPEED, -FENCE_SPEED);
  launch(3);
  // digitalWrite(99,LOW);
  forward(200, FENCE_TO_TZ1, 0);  // TZ1
  delay(MOTOR_DELAY);
  rotate_to_angle(90, CW);
  delay(MOTOR_DELAY);
  forward_enc(FAST_SPEED, BLUE_TO_TZ3, 90);
}

