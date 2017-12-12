int opt, a,dly = 1000;
String str1, str2 = "o";
String s1,s2,s3;
void call_debug()
{
  //Main-Menu Options
 Serial.println("Bot is in Debug Mode.\n***Maake Sure the Serial Montor is in \"No Line Ending\" Mode.\n\n Please Choose from the options below.\n\t1. Motor Testing\n\t2. Photoswitch Testing\n\t3.Bump-Switch Testing\n\tLauncher Testing\nPls Enter(1-4):");
  opt = Serial.parseInt();
  switch (opt)
  {
    case 1:
      motor_testing();                                              //All the Tests related to Drive Motors
      break;
    case 2:
    photoswitch_testing();                                          //Test all photoSwitchs
      break;
    case 3:
      break;
    case 4:
      break;
    default:
      Serial.println("Wrong Option. Try Again.");
  }
}

void motor_testing()
{
  Serial.println("***Make Sure that the bot is not in contact with GROUND before starting the Test.***\n");
tag1: Serial.println("Choose from the options below:\n\t1.Test All the Motors.\n\t2.Send Custom Commands.\n\t3. Main Menu\nPls Enter(1-3):");
  opt = Serial.parseInt();
  switch (opt)
  {
    case 1:
      Serial.println("Each Motor will run turn by turn for 1 sec. Send any character to start the test.\n Send \"set\" to set custom time  and start the test or send \"cancel\" to cancel the test");
      while (!Serial.available());
      str1 = Serial.readString();
      if (str1 == "set")
      {
        Serial.println("Enter custom time in milliseconds:");
        while (!Serial.available());
        dly = Serial.parseInt();
        dly = constrain(dly, 0, 10000);
        goto tag2;
      }
      else if (str1 == "calcel")
        goto tag1;
      else
      {
tag2: for (int i = 0; i < 2; i++)
        {
          (i == 0) ? switch_axis('x') : switch_axis('y');
          delay(50);
          motorA(50);
          delay(dly);
          motor_off();
          motorB(50);
          delay(dly);
          motor_off();
        }

      }
      break;
    case 2:
      Serial.println("This mode allows you to send Sbertooth commands over Serial Monoitor.\n ***Set your Serial Monitor to \"No Line Ending\" mode for this to work.\nYou can send \"close\" anytime to come out of this mode.\n You can now send Commands.");
      while (str2 != "close")
      {
        if (Serial.available()) {
          str2 = Serial.readString();
          Serial3.print(str2 + "\r\n");
        }
      }
      break;

      case 3:
      call_debug();
      break;
    default:
      Serial.println("Wrong Option. Try Again.");
      goto tag1;
  }
}

void photoswitch_testing()
{
  Serial.println("**Entering photoswitch testing mode**");
  tag3: Serial.println("Choose from the below options:\n1.All Switches Reading \n 2.Individual Readings\n3.Main Menu\nPls Enter(1-3)");
  opt=Serial.parseInt();
  switch(opt)
  {
    case 1:
    Serial.println("**Displaying Reading from all Senors   Press 's' to stop and return to Main Menu**");
    while(s1!='s')
    {
      s1=Serial.read();
      if(s1=='s')
      goto tag3;
      
      else
      {
      Serial.println(String(digitalRead(bot.photo[0])) + " " + String(digitalRead(bot.photo[1])) + " " +  String(digitalRead(bot.photo[2])));
     // Serial.println("*************************************");
      delay(100);
      }
    }
   
    break;

    case 2:
    Serial.println("Choose which photoswitch reading you want \n1.Switch 1\t2.Switch 2\t3.Switch 3");
    a=Serial.parseInt();
    switch(a)
    {
      case 1:
      while(s2!='s')
      {
      s2=Serial.readString();
      Serial.println(digitalRead(bot.photo[0]));
      }
      break;

      case 2:
      while(s2!='s')
      {
      s2=Serial.readString();
      Serial.println(digitalRead(bot.photo[1]));
      }
      break;

      case 3:
      while(s2!='s')
      {
      s2=Serial.readString();
      Serial.println(digitalRead(bot.photo[2]));
      }
      break;
      
    
    }
   
    break;

    case 3:
    call_debug();
    break;

    default:
    Serial.println("Wrong Option.Try Again");
    goto tag3;
    
    
  }
}

