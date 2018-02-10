void loop() {
  time_i = micros();
  time = time_i - time_f;
  bno();
  yaw_d = yaw - yaw_prev;
  yaw_d = yaw_d / time;
  yaw_i = (yaw * time) + yaw_i;
  ////////////////
  incrementals();
  //////////////
  error_interrupt();
  //////////////
  decrmentals();
  //////////////
  error_interrupt();
  /////////////
  stp();
  ////////////
  if (code_flag[0] == true)//15 degree func
    function_01();
  //////////////////////////
  if (code_flag[1] == true)
    function_02();
  if (code_flag[2] == true)
    function_03a();
  if (code_flag[3] == true)
    function_03();

//    Serial.println(step[2].stepcount);





  ////////////////////////////
  time_f = time_i;
  yaw_prev = yaw;
}
