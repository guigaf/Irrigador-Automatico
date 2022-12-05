#include <TimerOne.h> //inclui a função timer
#include <avr/wdt.h> //inclui a função watchdog

int tempo = 0;

void setup()
{
  Timer1.initialize(1000000); //Executa a cada 1 SEC
  Timer1.attachInterrupt( timerIsr ); // A cada 1 SEC chama esta rotina

  Serial.begin(38400);

  wdt_enable(WDTO_8S); //habilita o watchdog a cada 8 segundos
}
void loop()
{
 if (tempo <=10 ) // apos 10 segundos, nao entrara mais nessa funcao, e apos 8 segundos sem passar por essa funcao, o arduino ira reiniciar o ciclo, com o "tempo" em 0
 {
 wdt_reset();  //  reseta o watchdog,  ou seja se o programa travar e o pointer não ativar esse reset em 8 segundos o watchdog sera ativado
 }
}
//=====================================================================================================================================================================================
void timerIsr()
{
  tempo = tempo + 1; // a cada 1 segundo ira incrementar em 1 a variavel "tempo"
  Serial.println(tempo);
}
