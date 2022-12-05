#include <SoftwareSerial.h>

SoftwareSerial serial1(10, 11); // RX, TX

#define led1 13
#define led2 6
#define led3 7
 
void setup() 
{
  serial1.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}
void loop() 
{
   if (serial1.available()) //se byte pronto para leitura
   {    
    switch(serial1.read())      //verifica qual caracter recebido
    {
      case '1':       //caso '1'
      {
        digitalWrite(led1,!digitalRead(led1)); //inverte estado do LED
        break;
      }
    }
  }
}
