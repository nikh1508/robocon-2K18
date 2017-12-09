#include<Wire.h>


unsigned char data[16];
int offset[8] = {0}, avg[5]={0}, avg1;
int i, t = 0;

void Read_IICData()
{
  Wire.requestFrom(9, 16);    // request 16 bytes from slave device #9
  while (Wire.available())   // slave may send less than requested
  {
    data[t] = Wire.read(); // receive a byte as character
    if (t < 15) t++;
    else t = 0;
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

void print_array(unsigned char data[16])
{
  Serial.print(data[0]);
  Serial.print(" ");
  Serial.print(data[2]);
  Serial.print(" ");
  Serial.print( data[4]);
  Serial.print(" ");
  Serial.print(data[6]);
  Serial.print(" ");
  Serial.print(data[8]);
  Serial.print(" ");
  Serial.print(data[10]);
  Serial.print(" ");
  Serial.print( data[12]);
  Serial.print(" ");
  Serial.println(data[14]);
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
  Serial.println("Keep any object of uniform colour under the sensor and send any character to start the calibration.");
  while (!Serial.available());
  Serial.flush();
  Serial.println("Calibrating...");
  for (int j = 0; j < 5; j++) {
    Read_IICData();
    for (i = 0; i < 8; i++)
      avg[j] += data[i * 2];
    avg[j] = avg[j] / 8;
    print_array(data);
    Serial.println("Average"+String(j+1)+"="+String(avg[j]));
    
    delay(300);
  }
  avg1 = (avg[0] + avg[1] + avg[2] + avg[3] + avg[4]) / 5;
  Serial.print("Average=" + String(avg1));
  for (i = 0; i < 8; i++)
    offset[i] = data[i * 2] - avg1;
  Serial.println("Calibrated.");
  delay(500);
  //---------------------------------------------------------------------------
}


void calibrate_data(unsigned char x[16]) {
  for (i = 0; i < 8; i++)
    x[i * 2] -= offset[i];
}

void loop() {
  Read_IICData();
  Serial.println("Real Data:");
  print_array(data);
  calibrate_data(data);
  print_array(data);
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
