#include <SoftwareSerial.h>

SoftwareSerial bluetooth(5, 6); // RX, TX
char b1;

void setup() 
{
  bluetooth.begin(9600);
  Serial.begin(9600);
  Serial.println("PRONTO");
}

void loop()
{// Lê os dados do bluetooth
  if (bluetooth.available()>0) 
  { // Se existem dados para leitura
    b1 = bluetooth.read(); //Variável para armazenar o dado atual
    Serial.println(b1); //Printa o comando
  }
}
