#include <SoftwareSerial.h>
#include <IRremote.h>
#include <virtuabotixRTC.h>           

virtuabotixRTC myRTC(6, 7, 8);
SoftwareSerial serial1(10, 11); // RX, TX

IRsend irsend;
boolean aux1=0;

unsigned int sinalraw[] ={};

String readString;
String readString2;
String readString3;

int q=0;
int w=0;
int e=0;
int varint=0;
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
  while(serial1.available()>0)
  {
    w++;
    q=0;
    char c = serial1.read();
    String str(c);
    readString += str;
    escreve=true;    
      if (w>=100)
      {
        readString2 += readString;
        readString = "";
        w=0;
      }
      escreve=true;
  }
  if (serial1.available()==0)
  {
    q++;
    delay(1);
  }
  if ((q>=1000) && (escreve==true))
  {
  readString2 += readString;
  Serial.print("readString= ");
  Serial.println(readString2);
  //unsigned int sinalraw[] = {'readString2'};
  //irsend.sendRaw(readString2, sizeof(readString2) / sizeof(readString2[0]), khz); 
  //varint =  (String (readString2, int));   
  readString = "";
  readString2="";
  q=0;
  escreve=false; 
  }
}

