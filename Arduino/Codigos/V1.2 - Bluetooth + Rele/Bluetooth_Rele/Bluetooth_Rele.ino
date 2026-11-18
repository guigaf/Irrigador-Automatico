/*
  Irrigador Automatico - V1.2 (V1.0 + V1.1)
  Liga e desliga a valvula de irrigacao por comando via Bluetooth (HC-05)
  ou pelo monitor serial (USB).

  Comandos (1 caractere):
    'a' -> liga a irrigacao (rele ligado)
    'b' -> desliga a irrigacao (rele desligado)
    's' -> informa o estado atual

  Ligacoes:
    HC-05 TXD -> pino 5 (RX do Arduino)
    HC-05 RXD <- pino 6 (TX do Arduino) via divisor de tensao 1k/2k (5V -> 3,3V)
    Pino 2    -> resistor 1k -> base do BC337 -> rele 12V
*/

#include <SoftwareSerial.h>

const int PINO_RELE = 2;          // HIGH = rele ligado (transistor NPN BC337)
SoftwareSerial bluetooth(5, 6);   // RX, TX

bool irrigando = false;

void definirRele(bool ligar)
{
  irrigando = ligar;
  digitalWrite(PINO_RELE, ligar ? HIGH : LOW);
}

void responder(const char *mensagem)
{
  Serial.println(mensagem);
  bluetooth.println(mensagem);
}

void processarComando(char comando)
{
  switch (comando)
  {
    case 'a':
      definirRele(true);
      responder("Irrigacao LIGADA");
      break;

    case 'b':
      definirRele(false);
      responder("Irrigacao DESLIGADA");
      break;

    case 's':
      responder(irrigando ? "Estado: LIGADA" : "Estado: DESLIGADA");
      break;

    case '\r':
    case '\n':
      break;                      // ignora fim de linha enviado por apps e pelo monitor serial

    default:
      responder("Comando invalido. Use: a = liga, b = desliga, s = estado");
      break;
  }
}

void setup()
{
  pinMode(PINO_RELE, OUTPUT);
  definirRele(false);             // seguranca: sempre inicia com a valvula fechada

  Serial.begin(9600);
  bluetooth.begin(9600);          // velocidade padrao do HC-05
  responder("PRONTO - comandos: a = liga, b = desliga, s = estado");
}

void loop()
{
  if (bluetooth.available() > 0)
  {
    processarComando(bluetooth.read());
  }

  if (Serial.available() > 0)
  {
    processarComando(Serial.read());
  }
}
