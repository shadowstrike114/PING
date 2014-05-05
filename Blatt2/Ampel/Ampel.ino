const int rotzeit = 10000;
const int rotausfallzeit = 10000;
const int gelbzeit = 3000;
const int blinkzeit = 125;
const int ledrot = 13;
const int ledgelb = 12;
const int ledgruen = 11;
const int ledfussgaenger = 8;
const int sigin = 2;
const int ledFrot = 7;  
const int ledFgelb = 6; 
const int ledFgruen = 5;  

uint8_t zustand = 0; // 0: grün, 1: gelb, 2: rot,3: gelb
boolean taster = false;
uint32_t letzterTastendruck = 0;
uint32_t letzteSystemzeit = 0;
uint32_t letzteBlinkzeit = 0;


void setup()
{
  pinMode(ledrot,OUTPUT);
  pinMode(ledgelb,OUTPUT);
  pinMode(ledgruen,OUTPUT);
  pinMode(ledFrot,OUTPUT);
  pinMode(ledFgelb,OUTPUT);
  pinMode(ledFgruen,OUTPUT);
  pinMode(ledfussgaenger,OUTPUT);
  pinMode(sigin,INPUT);
  digitalWrite(ledgruen, HIGH);
}

void loop()
{  
  if (!taster && digitalRead(sigin))
  {
    taster = true;
  }

  if (millis() - letzteSystemzeit >= rotausfallzeit && zustand == 0 && taster)
  {
    digitalWrite(ledgruen, LOW);
    digitalWrite(ledgelb, HIGH);
    zustand++;
    letzteSystemzeit = millis();
  }

  if (zustand & 1  && millis() - letzteSystemzeit >= gelbzeit)
  {
    digitalWrite(ledgelb, LOW);
    if (zustand == 1)
      digitalWrite(ledrot, HIGH);

    if (zustand == 3)
      digitalWrite(ledgruen, HIGH);

    zustand++;
    letzteSystemzeit = millis();      
  }

  if (zustand == 2 && millis() - letzteSystemzeit >= rotzeit)
  {
    digitalWrite(ledrot, LOW);
    digitalWrite(ledgelb, HIGH);
    zustand++;
    taster = false;
    letzteSystemzeit = millis();
  }

  if (taster && millis() - letzteBlinkzeit >= blinkzeit && zustand == 0)
  {
    digitalWrite(ledfussgaenger, !digitalRead(ledfussgaenger));
    letzteBlinkzeit = millis();
  }

  if (zustand != 0)
    digitalWrite(ledfussgaenger,LOW);

  if ( zustand > 3)
    zustand = 0;

  digitalWrite(ledFrot, digitalRead(ledgruen));
  digitalWrite(ledFgelb, digitalRead(ledgelb));
  digitalWrite(ledFgruen, digitalRead(ledrot));
}
