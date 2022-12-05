#include <IRremote.h>
#define liga 5
#define up 6
#define down 7

boolean liga_aux = false;
boolean up_aux = false;
boolean down_aux = false;

IRsend irsend;

void setup() 
{
  Serial.begin(9600);
  pinMode(liga, INPUT_PULLUP);
  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
}

void loop() 
{
  if((digitalRead(liga)== LOW) && (liga_aux==false))
  {
    irsend.sendNEC(0xC40BF, 32);
    Serial.println("liga");
    liga_aux=true;
  }
  if((digitalRead(liga)== HIGH) && (liga_aux==true))
  {
    liga_aux=false;
  }
  
  //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
  if((digitalRead(up)== LOW) && (up_aux==false))
  {
    irsend.sendNEC(0xC41BE, 32);
    Serial.println("UP");
    up_aux=true;
  }
  if((digitalRead(up)== HIGH) && (up_aux==true))
  {
    up_aux=false;
  }

  //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------  
  
  if((digitalRead(down)== LOW) && (down_aux==false))
  {
    irsend.sendNEC(0xCC13E, 32);
    Serial.println("DOWN");
    down_aux=true;
  }
  if((digitalRead(down)== HIGH) && (down_aux==true))
  {
    down_aux=false;
  }
}
