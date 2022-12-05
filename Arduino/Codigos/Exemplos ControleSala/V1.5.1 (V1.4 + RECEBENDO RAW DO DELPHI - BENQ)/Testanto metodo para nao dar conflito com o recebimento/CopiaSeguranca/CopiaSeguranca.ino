#include <SoftwareSerial.h>
#include <IRremote.h>
#include <virtuabotixRTC.h>           

virtuabotixRTC myRTC(6, 7, 8);
SoftwareSerial serial1(10, 11); // RX, TX

IRsend irsend;

int w=0;
int indice1=-1;
int indice3=-1;

unsigned int r=0;
unsigned int valor1[4];
unsigned int valor2;
unsigned int valor3[197];

boolean aux1=0;

boolean AC=false,DS=false;;

char dado;

void setup() 
{
  serial1.begin(9600);
  Serial.begin(9600);
  valor1[0]=0;
  valor1[1]=0;
  valor1[2]=0;
  valor1[3]=10;
  valor2=0;
}
void loop() 
{
  myRTC.updateTime();
  int khz = 38;
//-------------------------------------------------------------------------------------------              
  if (serial1.available()>0)  //se byte pronto para leitura
  {
    if ((!AC) && (!DS))
    {
      dado=serial1.read();
    }
    if (AC==true)
    {
      w++;
      char c = serial1.read();
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
          Serial.println(indice3);
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
    if (dado=='Z')
    {
       AC=true;
       DS=false;
       Serial.println("AC");
       dado=' ';
    }
    if (dado=='z')
    {
       AC=false;
       DS=true;
       Serial.println("DS");
       dado=' ';
    }    
  }
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  if (valor3[196]!=0)
  {
    for(int i = 0; i < 196; i++)
    {
      Serial.print(valor3[i]);
      Serial.print(",");
    }
    for(int o = 196; o < 197; o++)
    {
      Serial.println(valor3[o]);
    }
    irsend.sendRaw(valor3, sizeof(valor3) / sizeof(valor3[0]), khz);
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

