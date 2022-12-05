const int ReleTroca =  8;      // the number of the LED pin

bool releState = false;         // variable for reading the pushbutton status
bool canChange = true;

void setup() 
{
  pinMode(ReleTroca, OUTPUT);
  Serial.begin(9600);
  Serial.println("PRONTO");
}

void loop() 
{
  if ((releState == false) and (canChange == true))
  {
    // turn RELE on:
    digitalWrite(ReleTroca, HIGH);
    releState = true;
    canChange = false;
    Serial.print("Estado: ");
    Serial.println("Ligado");
  } 
  if ((releState == true) and (canChange == true))
  {
    // turn RELE off:
    digitalWrite(ReleTroca, LOW);
    releState = false;
    canChange = false;
    Serial.print("Estado: ");
    Serial.println("Desligado");
  }
  delay(5000);
  canChange = true;
}
