#include<Wire.h>
word data[8];
word min_data[8]={65534,65534,65534,65534,65534,65534,65534,65534};//it pointless
word max_data[8]={0,0,0,0,0,0,0,0};
word thre_data[8];/// once the thresold for a system is form no need of max and min
byte ddata[8];
int offset[8] = {0}, avg[5] = {0}, avg1;
int i, t = 0;

void Read_IICData()
{
  Wire.requestFrom(9, 16);    // request 16 bytes from slave device #9 
 for (int t=0; t <= 7; t++){ //while wire.availiable is also fine...
        data[t] = Wire.read() << 2 | Wire.read();//bit msb
     //   Serial.println(data[t]);
        //   data[t] = Wire.read(); // receive a byte as character
        min_data[t]=min_data[t]>data[t]?data[t]:min_data[t];
        max_data[t]=max_data[t]<data[t]?data[t]:max_data[t];
        thre_data[t]=((min_data[t]+max_data[t])/2);//thre is kept in loop for autocalibration 
        ddata[t]=(data[t]>thre_data[t]?1:0); 
  }

  //  for (i = 0; i < 8; i++)
  //  {
  //    if (data[2 * i] < threshold)
  //      Flag[i] = 1;
  //    else
  //      Flag[i] = 0;
  //  }
}
byte error, address = 0x09;

void print_array()///what about the msb bit? data[1]...probably stm has 10 bit ADC
{
for (int i=0; i <= 7; i++){Serial.print(data[i]);Serial.print(" d ");}Serial.println();//debug
for (int i=0; i <= 7; i++){Serial.print(min_data[i]);Serial.print(" mn ");}Serial.println();//debug
  for (int i=0; i <= 7; i++){Serial.print(max_data[i]);Serial.print(" mx ");}Serial.println();//debug
  for (int i=0; i <= 7; i++){Serial.print(thre_data[i]);Serial.print(" t ");}Serial.println();//debug
  for (int i=0; i <= 7; i++){Serial.print(ddata[i]);Serial.print(" dd ");}Serial.println();
  //Serial.println(ddata,BIN); 
}

void setup() {
  Wire.begin();
  Serial.begin(9600);
  delay(1000);
  while (error != 0) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    Serial.println("Unable to communicate with the I2C device. Trying again..");
  }
  Serial.println("Device Found.");
  delay(100);
  //---------------------------------------------------------------------------
   Serial.flush();
   Serial.println("move the bot across the line to and fro at least  7 times and send any character to end the calibration.");
while (!Serial.available()){Read_IICData();print_array();};
  Serial.flush();
//  Serial.println("Calibrating...");
  
//  for (int j = 0; j < 5; j++) {
//    Read_IICData();
//    for (i = 0; i < 8; i++)
//      avg[j] += data[i * 2];
//    avg[j] = avg[j] / 8;
//    print_array(data);
//    Serial.println("Average" + String(j + 1) + "=" + String(avg[j]));
//
//    delay(300);
//  }
//  avg1 = (avg[0] + avg[1] + avg[2] + avg[3] + avg[4]) / 5;
//  Serial.print("Average=" + String(avg1));
//  for (i = 0; i < 8; i++)
//    offset[i] = data[i * 2] - avg1;
//  Serial.println("Calibrated.");
//  delay(500);
  //---------------------------------------------------------------------------
}


void calibrate_data(unsigned char x[16]) {
  for (i = 0; i < 8; i++)
    x[i * 2] -= offset[i];
}

void loop() {
  Read_IICData();
  print_array();
 // Serial.println("Real Data:");
  //print_array(data);
 // calibrate_data(data);
  //print_array(data);
  Serial.println("---------------------------------------------------------------------------");
  //   Serial.print(data[1]);
  //  Serial.print(" ");
  //  Serial.print(data[3]);
  //  Serial.print(" ");
  //  Serial.print( data[5]);
  //  Serial.print(" ");
  //  Serial.print(data[7]);
  //  Serial.print(" ");
  //  Serial.print(data[9]);
  //  Serial.print(" ");
  //  Serial.print(data[11]);
  //  Serial.print(" ");
  //  Serial.print( data[13]);
  //  Serial.print(" ");
  //  Serial.println(data[15]);
  //  Serial.println("---------------------------------------------------------------------------");
  delay(200);
}
