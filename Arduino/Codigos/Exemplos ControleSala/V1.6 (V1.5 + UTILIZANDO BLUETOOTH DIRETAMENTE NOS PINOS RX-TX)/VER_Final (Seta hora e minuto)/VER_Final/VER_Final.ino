//#include <SoftwareSerial.h>
#include <IRremote.h>
#include <virtuabotixRTC.h>

virtuabotixRTC myRTC(6, 7, 8);
//SoftwareSerial serial1(10, 11); // RX, TX

IRsend irsend;

int w=0;
int indice1=-1;
int indice3=-1;
int horadesliga=22;
int mindesliga=00;
int auxtimeoff1[2];
int auxtimeoff11=-1;
int auxtimeoff2;
int auxtimeoff22=0;
int auxtimeoff3[2];
int auxtimeoff33=0;

unsigned int r=0;
unsigned int f=0;
unsigned int valor1[4];
unsigned int valor2;
unsigned int valor3[197];

boolean DSLIG=false;
boolean ACLIG=false;

boolean AC=false,DS=false;;
boolean HORA=false;

char dado;

int timer=0;

void setup() 
{
  //myRTC.setDS1302Time(00, 15, 17, 6, 11, 8, 2017); //segundo, minuto, hora, dia da semana, dia, mes, ano
  //delay(100);
  //serial1.begin(38400);
  Serial.begin(38400);
  valor1[0]=0;
  valor1[1]=0;
  valor1[2]=0;
  valor1[3]=10;
  valor2=0;
}
void loop()
{
  int khz = 38;
  myRTC.updateTime();
//-------------------------------------------------------------------------------------------
timer++;
if (timer>=1000)
{
  Serial.print("Hora : ");
  if (myRTC.hours < 10)
    {
      Serial.print("0");
    }
  Serial.print(myRTC.hours);
  Serial.print(":");
  if (myRTC.minutes < 10)
    {
      Serial.print("0");
    }
  Serial.print(myRTC.minutes);
  Serial.print(":");
  if (myRTC.seconds < 10)
    {
      Serial.print("0");
    }
  Serial.println(myRTC.seconds);
  Serial.println(DSLIG);
  timer=0;
}
//-------------------------------------------------------------------------------------------
  if ((DSLIG==true) && (myRTC.hours>=horadesliga) && (myRTC.minutes>=mindesliga))
    {
      delay(120000);
      //Serial.println("DESLIGAR DS");
      irsend.sendNEC(0xC40BF, 32);//manda o sinal IR-DESLIGA
      delay(1000);
      irsend.sendNEC(0xC40BF, 32); 
      DSLIG=false;  
    }  
//------------------------------------------------------------------------------------------- 
  if ((ACLIG==true) && (myRTC.hours>=horadesliga) && (myRTC.minutes>=mindesliga))
    {
      delay(5000);
      unsigned int irSignal[] = {6280, 7580, 560, 580, 600, 520, 580, 560, 580, 520, 620, 520, 560, 560, 600, 520, 600, 540, 580, 580, 580, 540, 560, 560, 600, 540, 580, 540, 600, 520, 600, 540, 560, 560, 600, 560, 520, 600, 600, 520, 600, 540, 580, 540, 600, 540, 540, 580, 580, 540, 580, 580, 580, 540, 600, 540, 540, 560, 620, 540, 560, 540, 560, 560, 600, 540, 520, 640, 580, 560, 560, 540, 600, 520, 600, 540, 560, 560, 600, 540, 580, 540, 560, 600, 580, 540, 560, 560, 600, 540, 520, 600, 600, 520, 600, 540, 540, 580, 600, 560, 500, 620, 600, 520, 600, 540, 560, 560, 600, 540, 500, 600, 600, 520, 620, 560, 580, 540, 600, 540, 500, 1720, 580, 1640, 580, 1640, 600, 1640, 540, 560, 600, 580, 560, 560, 600, 540, 580, 520, 600, 520, 600, 540, 540, 580, 600, 520, 600, 1660, 600, 540, 500, 620, 600, 1620, 580, 540, 600, 540, 520, 600, 600, 1640, 540, 1720, 500, 600, 600, 1640, 580, 540, 600, 540, 500, 1720, 580, 540, 560, 1660, 520, 640, 600, 1620, 600, 1640, 500, 620, 580, 560, 560, 1640, 600, 540, 500, 1720, 580, 7580, 580};
      Serial.println("DESLIGAR AC");
      irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), khz);
      ACLIG=false;  
    }
//-------------------------------------------------------------------------------------------              
  while (Serial.available()>0)  //se byte pronto para leitura
  {
    if ((!AC) && (!DS) && (!HORA))
    {
      dado=Serial.read();
    }
//-------------------------------------------------------------------------------------------
    if (HORA==true)
    {
      char m = Serial.read();
      unsigned int hora(m);
      f=hora-48;
      //Serial.println(f);
      //Serial.println(f);
//-------------------------------------------------------------------------------------------
      if (m!=':')
      {
        auxtimeoff11++;
        auxtimeoff1[auxtimeoff11]=f;
        f=0;
      }
//-------------------------------------------------------------------------------------------
      if (m==':')
      {
        //Serial.println(auxtimeoff33);
          auxtimeoff22++;
          auxtimeoff1[0]=auxtimeoff1[0]*10;
          auxtimeoff1[1]=auxtimeoff1[1]*1;
          auxtimeoff2=auxtimeoff1[0]+auxtimeoff1[1];
        if (auxtimeoff33==1)
        {
          auxtimeoff33++;  
          mindesliga=auxtimeoff2;        
          //Serial.println(mindesliga);
          //Serial.println("entrou em minutos");
        }
        if (auxtimeoff33==0)
        {
          auxtimeoff33++;
          horadesliga=auxtimeoff2;
          //Serial.println(horadesliga);
          //Serial.println("entrou em horas");
        }
        auxtimeoff11=-1;
        f=0;
        //Serial.println(auxtimeoff33);
      }
//-------------------------------------------------------------------------------------------
        if (auxtimeoff22>=2)
        {
          //Serial.print(horadesliga);
          //Serial.print(':');
          //Serial.print(mindesliga);    
          //Serial.println(' ');
          HORA=false;
          hora=' ';
          auxtimeoff1[0]=0;
          auxtimeoff1[1]=0;
          auxtimeoff1[2]=0;                    
          auxtimeoff11=-1;
          auxtimeoff2=0;
          auxtimeoff22=0;
          auxtimeoff3[0]=0;
          auxtimeoff3[1]=0;
          auxtimeoff3[2]=0;                   
          auxtimeoff33=0;
        }

    }
//-------------------------------------------------------------------------------------------
    if (AC==true)
    {
      w++;
      char c = Serial.read();
      unsigned int sig(c);
      r=sig-48;
//-------------------------------------------------------------------------------------------
      if (c!=',')
      {
        indice1++;
        valor1[indice1]=r;
        r=0;
      }
//-------------------------------------------------------------------------------------------
      if (c==',')
      {
        if (valor1[3]!=10)
        {
          valor1[0]=valor1[0]*1000;
          valor1[1]=valor1[1]*100;
          valor1[2]=valor1[2]*10;
          valor2=valor1[0]+valor1[1]+valor1[2]+valor1[3];    
        }
        if (valor1[3]==10)
        {
          valor1[0]=valor1[0]*100;
          valor1[1]=valor1[1]*10;
          valor1[2]=valor1[2]*1;
          valor2=valor1[0]+valor1[1]+valor1[2];
        }
        if (indice3<197)
        {
          indice3++;
          valor3[indice3]=valor2;
          //Serial.println(indice3);
        }
        valor1[3]=10;
        indice1=-1;
        r=0;
      }
//-------------------------------------------------------------------------------------------      
        if (indice3>=196)
        {
          AC=false;
        }
    }
//-------------------------------------------------------------------------------------------      
    if (DS==true)
    {
      switch(Serial.read())  //verifica qual caracter recebido
        {
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
          /*case 'A':       //caso 'A' = 65
            {
              irsend.sendNEC(0xC40BF, 32);    //manda o sinal IR-LIGA
              break;
            }*/
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
          case 'B':     //caso 'B' = 66
            {
              irsend.sendNEC(0xC40BF, 32);    //manda o sinal IR-DESLIGA
              delay(1000);
              irsend.sendNEC(0xC40BF, 32);
              DSLIG=!DSLIG;
              break;
            }
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------     
          case 'C':       //caso 'C' = 67
            {
              irsend.sendNEC(0xCC03F, 32);    //manda o sinal IR-PAUSE/PLAY
              break;
            }
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------               
          case 'D':       //caso 'D' = 68
            {
              irsend.sendNEC(0xCF00F, 32);    //manda o sinal IR-MENU
              break;
            }
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                                
          case 'E':       //caso 'E' = 69
            {
              irsend.sendNEC(0xC10EF, 32);    //manda o sinal IR-AUTO
              break;
            }
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
          case 'F':       //caso 'F' = 70
            {
              irsend.sendNEC(0xC20DF, 32);    //manda o sinal IR-SOURCE
              break;
            }
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
          case 'G':       //caso 'G' = 71
            {
              irsend.sendNEC(0xC08F7, 32);    //manda o sinal IR-MODE
              break;
            }
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
          case 'H':       //caso 'H' = 72
            {
              irsend.sendNEC(0xC0CF3, 32);    //manda o sinal IR-SMART ECO
              break;
            }
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
          case 'I':       //caso 'I' = 73
            {
              irsend.sendNEC(0xCE01F, 32);    //manda o sinal IR-ECO BLANK
              break;
            }
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
          case 'J':       //caso 'J' = 74
            {
              irsend.sendNEC(0xCD02F, 32);    //manda o sinal IR-UP
              break;
            }
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
          case 'K':       //caso 'K' = 75
            {
              irsend.sendNEC(0xC30CF, 32);    //manda o sinal IR-DOWN
              break;
            }
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
          case 'L':       //caso 'L' = 76
            {
              irsend.sendNEC(0xC708F, 32);    //manda o sinal IR-RIGHT
              break;
            }
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
          case 'M':       //caso 'M' = 77
            {
              irsend.sendNEC(0xCB04F, 32);    //manda o sinal IR-LEFT
              break;
            }
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
          case 'N':       //caso 'N' = 78
            {
              irsend.sendNEC(0xC41BE, 32);    //manda o sinal IR-VOL_UP
              break;
            }
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
          case 'O':       //caso 'O' = 79
            {
              irsend.sendNEC(0xCC13E, 32);    //manda o sinal IR-VOL_DOWN
              break;
            }
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
          case 'P':       //caso 'P' = 80
            {
              irsend.sendNEC(0xC18E7, 32);    //manda o sinal IR-ZOOM_UP
              break;
            }
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
          case 'Q':       //caso 'Q' = 81
            {
              irsend.sendNEC(0xC9867, 32);    //manda o sinal IR-ZOOM_DOWN
              break;
            }
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
          case 'R':       //caso 'R' = 82
            {
              irsend.sendNEC(0xCA05F, 32);    //manda o sinal IR-PAGE_UP
              break;
            }
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
          case 'S':       //caso 'S' = 83
            {
              irsend.sendNEC(0xC609F, 32);    //manda o sinal IR-PAGE_DOWN
              break;
            }
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
          case 'T':       //caso 'T' = 84
            {
              irsend.sendNEC(0xCA45B, 32);    //manda o sinal IR-ON
              break;
            }
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
          case 'U':       //caso 'U' = 85
            {
              irsend.sendNEC(0xC649B, 32);    //manda o sinal IR-SET_UP
              break;
            }
        }
      DS=false;
    }
//-------------------------------------------------------------------------------------------  
     if (dado=='Z')
    {
       AC=true;
       DS=false;
       HORA=false;
       //Serial.println("AC");
       dado=' ';
    }
    if (dado=='z')
    {
       AC=false;
       DS=true;
       HORA=false;
       //Serial.println("DS");
       dado=' ';
    }
    if (dado=='[')
    {
       AC=false;
       DS=false;
       HORA=true;
       //Serial.println("HORA Confirmada");
       dado=' ';  
    }
  }
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  if (valor3[196]!=0)
  {
    /*for(int i = 0; i < 196; i++)
    {
      Serial.print(valor3[i]);
      Serial.print(",");
    }
    for(int o = 196; o < 197; o++)
    {
      Serial.println(valor3[o]);
    }*/
    //Serial.println("ENVIADO");
    irsend.sendRaw(valor3, sizeof(valor3) / sizeof(valor3[0]), khz);
    ACLIG=true;
    w=0;
    indice1=-1;
    indice3=-1;
    r=0;
    valor1[0]=0;
    valor1[1]=0;
    valor1[2]=0;
    valor1[3]=10;
    valor2=0;
    valor3[196]=0;
  }
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
}

