#include <SoftwareSerial.h>
#include <IRremote.h>
#include <virtuabotixRTC.h>      
#include<stdlib.h>
int atoi(const char *nptr);

virtuabotixRTC myRTC(6, 7, 8);
SoftwareSerial serial1(10, 11); // RX, TX

IRsend irsend;
boolean aux1=0;

/*ON*/  //unsigned int sinalraw[] ={6150,7300,650,500,500,650,600,500,500,650,600,500,500,650,600,550,550,550,600,550,600,500,500,650,600,500,500,650,550,550,500,650,550,550,550,600,600,550,600,500,500,650,600,500,500,650,600,500,500,650,600,550,550,550,600,550,550,550,500,650,600,500,500,650,600,500,500,650,600,500,600,550,600,500,650,500,500,650,600,500,500,650,600,500,550,600,600,550,500,600,500,650,600,500,500,650,600,500,500,650,600,500,500,650,550,550,600,550,600,550,600,500,500,650,600,500,500,1700,600,1600,600,550,550,550,600,1600,550,1600,600,550,600,550,500,650,550,550,550,600,550,550,600,550,550,550,600,550,550,550,600,1600,600,550,600,550,550,550,550,1650,550,550,550,600,550,1650,550,550,600,1650,550,550,550,600,550,1600,500,650,550,1650,550,1650,500,650,550,1600,550,1650,500,600,600,1650,550,550,550,600,550,7350,600};
/*OFF*/ //unsigned int sinalraw[] ={6100,7350,600,550,550,550,600,550,600,550,550,550,600,550,550,550,600,550,500,650,550,550,500,650,550,550,600,500,600,550,600,500,600,550,600,550,500,650,550,550,550,600,550,550,600,550,550,550,600,550,500,600,600,550,500,600,600,550,550,600,550,550,600,500,600,550,600,550,550,550,600,550,500,650,550,550,550,600,550,550,550,550,550,600,600,550,550,550,600,550,550,550,600,550,550,600,550,550,550,600,550,550,550,600,550,550,600,550,550,550,600,550,550,600,550,550,500,650,550,1600,600,550,600,550,550,1650,500,1650,600,550,550,550,600,550,550,600,550,550,550,600,550,550,550,600,550,550,550,600,500,1700,550,550,600,550,500,600,600,1650,500,600,600,550,550,1650,500,600,600,1600,550,550,600,550,550,1600,550,600,600,1600,600,1600,500,1700,600,550,500,1650,550,600,600,1600,550,600,550,550,500,7500,550};
/*16*/  //unsigned int sinalraw[] ={6240,7600,600,560,600,540,580,520,620,540,560,540,620,500,600,540,580,540,600,580,540,560,600,560,560,540,580,540,600,540,500,620,600,520,600,560,600,520,600,540,580,540,600,540,560,560,580,540,600,540,540,600,600,540,540,580,600,520,580,540,600,520,600,540,560,560,600,580,560,540,600,520,600,540,560,560,600,540,580,540,600,520,600,1660,600,1620,600,520,600,540,580,540,600,540,500,620,580,540,600,560,600,520,600,540,560,560,600,540,560,560,580,520,620,520,560,600,580,1640,600,520,600,540,560,1680,500,1700,600,540,580,520,620,560,560,560,600,540,560,560,580,540,580,560,540,560,600,560,560,580,600,540,560,560,580,520,600,540,520,1720,560,560,580,520,620,1640,600,540,520,1700,580,560,580,540,580,1640,600,520,600,1620,600,580,540,1680,580,540,600,1640,540,1680,560,1640,600,1640,600,1620,600,7560,600};
/*25*/  //unsigned int sinalraw[] ={6300,7580,580,560,480,640,580,560,520,600,560,540,580,580,480,640,560,520,560,640,580,560,520,600,560,560,560,580,500,600,580,520,600,600,560,600,540,580,560,540,580,580,500,600,580,580,540,560,580,520,600,600,560,560,560,580,540,560,580,520,600,560,480,640,580,560,560,580,580,560,560,560,560,540,600,560,560,560,580,520,580,580,480,640,600,1660,560,580,540,560,580,520,600,560,480,640,580,560,560,580,580,560,560,560,540,560,600,560,540,580,560,540,580,580,480,640,600,1640,580,560,560,560,540,1700,540,1640,600,560,560,560,560,600,540,580,580,560,560,560,560,540,600,560,520,600,580,560,540,1660,600,580,480,640,560,1660,560,540,580,1660,580,560,560,560,560,1700,560,520,600,1660,580,560,560,560,560,1680,540,580,560,1660,520,600,600,1660,560,580,540,580,560,520,600,560,520,600,580,560,560,7600,560};
/*32*/  //unsigned int sinalraw[] ={6300,7620,520,620,560,580,540,580,560,520,600,580,480,620,580,520,600,560,580,540,600,560,560,540,600,560,520,580,580,580,540,580,560,540,580,600,520,580,580,580,540,580,560,520,600,580,520,560,600,560,540,620,560,580,520,600,560,520,600,560,480,640,580,560,540,580,560,560,600,560,560,540,600,560,560,560,580,520,600,560,540,560,580,600,480,1760,540,580,540,540,600,580,540,560,580,560,560,560,560,560,600,560,540,560,600,560,540,580,580,500,600,580,520,580,580,600,480,1740,560,560,560,540,600,1660,560,1660,560,540,600,560,540,580,600,560,560,560,580,520,600,560,480,620,600,560,540,580,560,600,560,560,560,540,600,560,540,1680,560,1620,600,580,540,580,560,1680,580,520,600,1620,600,580,540,560,580,1660,540,560,580,1660,580,1680,560,540,600,560,480,1740,560,560,560,540,600,560,480,640,580,7580,580};
/**/    //unsigned int sinalraw[] =
unsigned int sinalraw[] ={};
//char valores[197]={};
char valar1=0;
char valar2=0;

String dado;
String readString;
String readString2;

int valor[255];
int valor2[4];
int q=0;
int w=0;
int e=0;
int indice=0;
int indice2=0;
int r=0;
int resultado;
int t1;
int t2;
boolean escreve=true;
void setup() 
{
  serial1.begin(9600);
  Serial.begin(9600);
  //myRTC.setDS1302Time(15, 33, 17, 4, 28, 06, 2017); 
}

void loop() 
{
  //myRTC.updateTime();
  int khz = 38; // 38kHz carrier frequency for the NEC protocol
  while(Serial.available()>0)
  {
    w++;
    q=0;
    char c = Serial.read();
    String str(c);
    int sig(c);
    r=sig;
    //readString += c;
//-------------------------------------------------------------------------------------------
if (r==49)
{
  resultado=1;
}
if (r==50)
{
  resultado=2;
}
if (r==51)
{
  resultado=3;
}
if (r==52)
{
  resultado=4;
}
if (r==53)
{
  resultado=5;
}
if (r==54)
{
  resultado=6;
}
if (r==55)
{
  resultado=7;
}
if (r==56)
{
  resultado=8;
}
if (r==57)
{
  resultado=9;
}
//-------------------------------------------------------------------------------------------
//t1 += resultado;
    if (c==",")
    {
      ++indice;
      valor[indice]=t1;
      t1 = "";
      //r=atoi(valar2);
      //readString = "";
      //w=0;
      //valores[1]=0;
      //valores[2]=0;
      //valores[3]=0;
      //valores[4]=0;
      //readString2 = "";
    }
//-------------------------------------------------------------------------------------------
    if (c!=",")
    {
      indice2++;
      valor2[indice2]=resultado;
      //readString2 += readString;
      //valores[w]=readString2;  
      //readString = "";
    }
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
    /*if (w>=100)
    {
      readString2 += readString;
      readString = "";
      w=0;
    }*/
//-------------------------------------------------------------------------------------------
  escreve=true; 
  }
//-------------------------------------------------------------------------------------------
  if (serial1.available()==0)
  {
    q++;
    delay(1);
  }
//-------------------------------------------------------------------------------------------
  if ((q>=5000) && (escreve==true))
  {
  readString2 += readString;
  Serial.print("readString= ");
  Serial.println(valor2[1]);
  readString = "";
  readString2 = "";
  q=0;
  w=0;
  e=0;
  indice=0;
  r="";
  resultado="";
  t1="";
  t2="";
  valor[255]="";
  valor2[1]="";
  valor2[2]="";
  valor2[3]="";
  valor2[4]="";

  escreve=false;
  //delay(100);
  //unsigned int sinalraw[] ={readString2};
  //delay(100);
  //irsend.sendRaw(sinalraw, sizeof(sinalraw) / sizeof(sinalraw[0]), khz); 
  }
//-------------------------------------------------------------------------------------------
/*  Serial.print("Hora : ");
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
  Serial.println(myRTC.seconds);*/
//-------------------------------------------------------------------------------------------
/*  
    if ((aux1==1) && (myRTC.hours>=22))
    {
      Serial.println("DESLIGAR");
      irsend.sendNEC(0xC40BF, 32);//manda o sinal IR-DESLIGA
      delay(1000);
      irsend.sendNEC(0xC40BF, 32); 
      aux1=0;   
    }
*/
//-------------------------------------------------------------------------------------------
/*
  if (Serial.available()>0)  //se byte pronto para leitura
    {
        char texto;
        texto = Serial.read();

        
        if (texto==',')
        { 
          ++x;
          Serial.print("If: "); 
          Serial.println(texto);
          Serial.print("Dado: "); 
          Serial.println(readString);  
          sinalraw[x]=(readString.toInt());
          readString="";
        }
        else
        {
          readString  += texto;
          Serial.print("Else: ");
          Serial.println(texto);
        } 
             
     /* switch(serial1.read())  //verifica qual caracter recebido
        {
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
         
          case 'W':
              irsend.sendRaw(sinalraw, sizeof(sinalraw) / sizeof(sinalraw[0]), khz); 
             break;
          case 'A':       //caso 'A' = 65
            {
              while(serial1.available())
              {
                //delay(3);
                texto = serial1.read();
                readString +=texto;                
              }
              Serial.println(readString);
              readString = "";
              
              //irsend.sendRaw(sinalraw, sizeof(sinalraw) / sizeof(sinalraw[0]), khz); 
              break;          
            }
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
          case 'B':     //caso 'B' = 66
            {
              //irsend.sendNEC(0xD42AEDAD, 32); 
              //irsend.sendRaw(signaloff, sizeof(signaloff) / sizeof(signaloff[0]), khz); 
              //irsend.sendNEC(0xC40BF, 32);//manda o sinal IR-DESLIGA
              //delay(1000);
              //irsend.sendNEC(0xC40BF, 32); 
              //aux1=!aux1;
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
    }
    */
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
}

