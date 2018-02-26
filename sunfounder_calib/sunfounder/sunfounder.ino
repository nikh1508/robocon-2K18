#include <Wire.h>
#define uchar unsigned char
uchar t;
//void send_data(short a1,short b1,short c1,short d1,short e1,short f1);
uchar data[16];
void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  t = 0;
}
void loop()
{
  Wire.requestFrom(9, 16);    // request 16 bytes from slave device #9
  while (Wire.available())   // slave may send less than requested
  {
    data[t] = Wire.read(); // receive a byte as character
    if (t < 15)
      t++;
    else
      t = 0;
  }

  double f = 0;
 
//  Serial.print(data[0]);
//  Serial.print(" "); 
// 
//  Serial.print(data[2]);
//   Serial.print(" "); 
//  Serial.print(data[4]);
// Serial.print(" "); 
//  Serial.print(data[6]);
// Serial.print(" "); 
//  Serial.print(data[8]);
//   Serial.print(" "); 
//  Serial.print(data[10]);
// Serial.print(" "); 
//  Serial.print(data[12]);
// Serial.print(" "); 
//  Serial.print(data[14]);
//  Serial.println();

  for (int i = 0; i <= 14; i+= 2)
    f += data[i];

  Serial.println(f / 8.0, 2);

}
