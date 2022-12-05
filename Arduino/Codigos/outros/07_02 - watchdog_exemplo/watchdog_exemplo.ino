#include <avr/wdt.h>  // inclui a função watchdog, biblioteca já consta dentro do sistema do arduino

int led = 3;  // indica um pino para led que servirá de referencia visual
int soma = 0;  // cria variavel para demonstracão de tempo de funcionamento ok
int temporeset = 0;  // cria variavel para informar em quanto tempo o watchdog funcionara

void setup() {   
  Serial.begin(9600);    // inicia a serial
  pinMode(led, OUTPUT);    // indica o pino como saida
  digitalWrite(led, HIGH);   // liga o led dentro do setup
  delay(1000);               // aguarda um segundo aceso
  digitalWrite(led, LOW);    // desliga o led

  wdt_enable(WDTO_4S);  // habilita o watchdog
}

void loop() {
  soma++;  // soma mais um a variavel soma
  Serial.println(soma);   // imprime na serial o valor de soma
  delay(500);  //  aguarda meio segundo

  wdt_reset();  //  reseta o watchdog,  ou seja se o programa travar e o pointer não ativar esse reset em 4 segundos o watchdog sera ativado

 while(soma >= 20){  //  cria uma condição de loop para que o pointer não passe pela funcao reset
   temporeset++;    // soma mais um a variavel tempo de reset
   Serial.print("tempo reset: ");   // imprime texto indicativo
   Serial.println(temporeset);     //  imprime o valor da variavel tempo de reset
   delay(1000);   //    aguarda um segundo
 }
 }

