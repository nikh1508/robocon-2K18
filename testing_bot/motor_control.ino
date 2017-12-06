void move_motors(int spd, int mot) {                                        //spd ranges from -100 to 100 and mot:: (1) is for left motor (2) is for right and (3) is for both motors
  dir = true;
  if (spd < 0) {
    spd *= -1;
    dir = !dir;
  }
  spd = map(spd, 0, 100, 0, 255);
  if (dir)str1 = "Forward"; else str1 = "Backward";
  if (mot == 1)str2 = "Left"; else if (mot == 2)str2 = "Right"; else {
    str2 = "Both";
  }
  Serial.println("Moving " + str2 + " motor " + str1 + " at PWM: " + String(spd));
  switch (mot) {
    case 1:
      analogWrite(bot.m_left[1], spd);
      digitalWrite(bot.m_left[0], dir);
      digitalWrite(bot.m_left[2], !dir);
      break;

    case 2:
      analogWrite(bot.m_right[1], spd);
      digitalWrite(bot.m_right[0], dir);
      digitalWrite(bot.m_right[2], !dir);
      break;

    case 3:
      analogWrite(bot.m_left[1], spd);
      digitalWrite(bot.m_left[0], dir);
      digitalWrite(bot.m_left[2], !dir);
      analogWrite(bot.m_right[1], spd);
      digitalWrite(bot.m_right[0], dir);
      digitalWrite(bot.m_right[2], !dir);
  }
}

void stop_motors(int mot, bool hard_brake = true) {                                   //mot:: (1) is for left motor (2) is for right and (3) is for both motors 
  switch (mot) {                                                                      //soft brake will be implemented in case second arguement is sent as false
      if (mot == 1)str2 = "Left"; else if (mot == 2)str2 = "Right"; else str2 = "Both";
      Serial.println("Stopping " + str2 + " motor.");
    case 1:
      if (hard_brake) {
        analogWrite(bot.m_left[1], 255);
        digitalWrite(bot.m_left[0], 1);
        digitalWrite(bot.m_left[2], 1);
      }
      else {
        analogWrite(bot.m_left[1], 0);
        digitalWrite(bot.m_left[0], 0);
        digitalWrite(bot.m_left[2], 0);
      }

      break;

    case 2:
      if (hard_brake) {
        analogWrite(bot.m_right[1], 255);
        digitalWrite(bot.m_right[0], 1);
        digitalWrite(bot.m_right[2], 1);
      }
      else {
        analogWrite(bot.m_right[1], 0);
        digitalWrite(bot.m_right[0], 0);
        digitalWrite(bot.m_right[2], 0);
      }
      break;

    case 3:

      if (hard_brake) {
        analogWrite(bot.m_left[1], 255);
        digitalWrite(bot.m_left[0], 1);
        digitalWrite(bot.m_left[2], 1);
        analogWrite(bot.m_right[1], 255);
        digitalWrite(bot.m_right[0], 1);
        digitalWrite(bot.m_right[2], 1);
      }
      else {
        analogWrite(bot.m_left[1], 0);
        digitalWrite(bot.m_left[0], 0);
        digitalWrite(bot.m_left[2], 0);
        analogWrite(bot.m_right[1], 0);
        digitalWrite(bot.m_right[0], 0);
        digitalWrite(bot.m_right[2], 0);
      }
  }
}

void change_pwm(int mot, int x) {
  x = constrain(x, 0, 255);
  if (mot == 1)
    analogWrite(bot.m_left[1], x);
  else
    analogWrite(bot.m_right[1], x);
}
