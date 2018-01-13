# wifi-manual_drive


>The project folder contains code for NodeMCU and Arduino.

>The mobile app used is **"Blynk"**.

>To run the blynk server copy the **Blynk_Robocon** directory and **server-0.29.3-java8.jar** file and run the command below in terminal.

><i>java -jar [path to server jar file] -dataFolder [path to Blynk_Robocon]</i>

>Login on Blynk app with the ip-address of the system running the blynk server and the default port. Use the credential below:

>**username:**robocon@blynk.cc **password:**whatpassword  

>The bot is T-shaped with two traction at the back and a dummu omni-wheel at the front.

>The NodeMCU receives data from the blynk server and transmits all the required data through Serial communication.

>The Arduino further manipulates the received x, y , trim and max_speed_slider data for driving a differential drive.
