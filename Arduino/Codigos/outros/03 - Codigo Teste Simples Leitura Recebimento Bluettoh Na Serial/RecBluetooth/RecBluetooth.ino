#include <SoftwareSerial.h>

SoftwareSerial bluetooth(5, 6); // RX, TX
String command = "";
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
    command += b1; //Variável para armazenar todos os dados
    Serial.println(command); //Printa o comando
   
    if (b1 == '\n')
    { //Se o dado atual for um pulador de linha (\n)
      Serial.print(command); //Printa o comando
      command = ""; //Limpa o comando para futuras leituras
    }
  }
}
