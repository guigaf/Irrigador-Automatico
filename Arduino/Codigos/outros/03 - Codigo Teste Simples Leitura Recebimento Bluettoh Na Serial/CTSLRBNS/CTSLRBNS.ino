#include <SoftwareSerial.h>

SoftwareSerial serial1(5, 6); // RX, TX

void setup()
{
  serial1.begin(38400);
  Serial.begin(9600);
}

void loop() 
{
  while(serial1.available()>0)
  {
    Serial.println(serial1.read());
  }
}
