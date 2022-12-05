#include <SoftwareSerial.h>
SoftwareSerial BT(5,6); //rx, tx

void setup()
{
  Serial.begin(9600);
  BT.begin(38400);
  Serial.println("Bluetooth AT command mode");
}
void loop()
{
  if(BT.available())
    Serial.write(BT.read());

  if(Serial.available())
    BT.write(Serial.read());
}
