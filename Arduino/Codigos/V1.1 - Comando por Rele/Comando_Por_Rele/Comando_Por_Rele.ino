
const int pinoRele = 2; //PINO DIGITAL UTILIZADO PELO MÓDULO RELÉ
int statusLamp = 0; //VARIÁVEL QUE CONTROLA O ESTADO DO MÓDULO RELÉ (LIGADO / DESLIGADO)
char a1;

void setup(){
  pinMode(pinoRele, OUTPUT); //DEFINE O PINO COMO SAÍDA
  digitalWrite(pinoRele, LOW); //MÓDULO RELÉ INICIA DESLIGADO
  Serial.begin(9600);
  Serial.println("PRONTO");
}    
void loop(){
  if(Serial.available()>0)
  {
     a1 = Serial.read();
     Serial.print("Lendo Serial: ");
     Serial.println(a1);
  }
  
  if(a1 == 'a')
  {  
    digitalWrite(pinoRele, HIGH); //LIGA O MÓDULO RELÉ (LÂMPADA ACENDE)
    statusLamp = 1;
    Serial.println("Ligando Rele");
    delay(200);
  }  
  else if (a1 == 'b')
  {
    digitalWrite(pinoRele, LOW); //DESLIGA O MÓDULO RELÉ (LÂMPADA APAGA)
    statusLamp = 0;
    Serial.println("Desligando Rele");
    delay(200);
  }
 
  a1 = ""; //Limpa a variavel
 
}
