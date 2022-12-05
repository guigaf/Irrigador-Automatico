#include <virtuabotixRTC.h>           

// myRTC(clock, data, rst)
virtuabotixRTC myRTC(6, 7, 8);

void setup()  
{      
  Serial.begin(9600);
  // Apos setar as informacoes, comente a linha abaixo
  // (segundos, minutos, hora, dia da semana, dia do mes, mes, ano)
  myRTC.setDS1302Time(50, 59, 21, 5, 26, 06, 2017);
}

void loop()  
{
  // Le as informacoes do CI
  myRTC.updateTime(); 
  //if ((myRTC.hours<22) && (myRTC.minutes>=00) && (myRTC.seconds>=00))
    {
    Serial.print("Hora : ");
    // Adiciona um 0 caso o valor da hora seja <10
    if (myRTC.hours < 10)
      {
        Serial.print("0");
      }
    Serial.print(myRTC.hours);
    Serial.print(":");
    // Adiciona um 0 caso o valor dos minutos seja <10
    if (myRTC.minutes < 10)
      {
        Serial.print("0");
      }
    Serial.print(myRTC.minutes);
    Serial.print(":");
    // Adiciona um 0 caso o valor dos segundos seja <10
    if (myRTC.seconds < 10)
      {
        Serial.print("0");
      }
    Serial.println(myRTC.seconds);
    }
//-------------------------------------------------------------------------------------------
  if ((myRTC.hours>=22) && (myRTC.minutes>=00) && (myRTC.seconds>=00))
    {
      Serial.println("DESLIGAR");
    }
delay(1000); 
}
