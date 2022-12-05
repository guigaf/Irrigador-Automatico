#include <SoftwareSerial.h>

SoftwareSerial BL(5, 6); // RX, TX
 
void setup() 
{
  BL.begin(38400);
  Serial.begin(9600);
  Serial.println("PRONTO");
}
void loop() 
{
   while(BL.available()) //se byte pronto para leitura
   {
    if(BL.available()>0)
    {
    Serial.print("Valor lido : ");
    Serial.println(BL.read());
      char m = BL.read();
      int hora(m);
      int horadesliga=hora;
      String TT(m);
      String TT2(BL.read());
      Serial.print("horadesliga: ");
      Serial.println(horadesliga);
      Serial.print("m: ");
      Serial.println(m);
      Serial.print("TT: ");
      Serial.println(TT);
      Serial.print("TT2: ");
      Serial.println(TT);
      hora=' ';
    }
    /*switch(BL.read())      //verifica qual caracter recebido
    {
      Serial.println("teste > 02");
      case 'q':       //caso '1'
      {
        digitalWrite(led1,!digitalRead(led1)); //inverte estado do LED
        Serial.println("teste > 3");
        break;
      }
    }*/
  }
}
