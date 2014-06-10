#include <LiquidCrystal.h>


LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
byte leer[8] = { 
  B11111,
  B10001, 
  B10001, 
  B10001, 
  B10001, 
  B10001, 
  B10001, 
  B11111   };


void balkenDiagramm(int zeile,int spalte, int wert,int minimum,int maximum);
void aufgabeA();
void aufgabeB();
void aufgabeC();
void aufgabeD();
void aufgabeE();
double getDist();
long fetchPulse();
void sendTrigger();

void setup() {
  pinMode(A0, INPUT);
  pinMode(4,  INPUT_PULLUP);
  pinMode(2,  OUTPUT);
  pinMode(3,  INPUT);

  lcd.begin(16, 2);

  lcd.createChar(0,leer);
}

void loop() {
  //aufgabeA(); 
  //aufgabeB();
  //aufgabeC();
  //aufgabeD();
  aufgabeE();
  //Aufgabe f ist in FunktionBlakendiagramm integriert
}

void aufgabeE()
{
  int maximumL,minimumL,maximum,minimum,wert;
  boolean funktion = false;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Kalibrierung");
  lcd.setCursor(0,1);
  lcd.print("Ultraschall");
  delay(1500);  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("\176Wert 1");
  lcd.setCursor(1,1);
  lcd.print("Wert 2");  
  while(digitalRead(4)){
  }
  lcd.setCursor(0,1);
  lcd.print("\176");
  minimum = getDist();
  delay(200);
  while(!digitalRead(4));  
  while (digitalRead(4)){  
  }
  maximum = getDist();
  delay(200);
  while(!digitalRead(4));
  if (minimum > maximum)
  {
    int buffer = maximum;
    maximum = minimum;
    minimum = buffer;
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Kalibrierung");
  lcd.setCursor(0,1);
  lcd.print("Lichtsensor");
  delay(1500);  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("\176Wert 1");
  lcd.setCursor(1,1);
  lcd.print("Wert 2");  
  while(digitalRead(4)){
  }
  lcd.setCursor(0,1);
  lcd.print("\176");
  minimumL = analogRead(0);
  delay(200);
  while(!digitalRead(4));  
  while (digitalRead(4)){  
  }
  maximumL = analogRead(0);
  delay(200);
  while(!digitalRead(4));
  if (minimumL > maximumL)
  {
    int buffer = maximumL;
    maximumL = minimumL;
    minimumL = buffer;
  }

  lcd.clear();

  uint32_t zeit;
  while(1)
  {
    lcd.setCursor(0,0);
    if (!digitalRead(4) && millis() - zeit > 200)
    {
      funktion = !funktion;
      zeit = millis();
    }

    if (!funktion)
    {
      wert = getDist();
      lcd.print("Ultraschall:");
      balkenDiagramm(1,0,wert,minimum,maximum);
    }
    else
    {
      lcd.print("Licht:       ");
      wert = analogRead(0);
      balkenDiagramm(1,0,wert,minimumL,maximumL);
    }
    lcd.setCursor(13,0);
    lcd.print(wert);
    lcd.print("     ");  
  }
}

void aufgabeD()
{
  int maximum,minimum,wert;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Kalibrierung");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("N\341hern und");
  lcd.setCursor(0,1);
  lcd.print("Knopf Dr\365cken");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Dann entfernen und");
  lcd.setCursor(0,1);
  lcd.print("Knopf Dr\365cken");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("\176Wert 1");
  lcd.setCursor(1,1);
  lcd.print("Wert 2");  
  while(digitalRead(4)){
  }
  lcd.setCursor(0,1);
  lcd.print("\176");
  minimum = getDist();
  while(!digitalRead(4));  
  while (digitalRead(4)){  
  }
  maximum = getDist();
  while(!digitalRead(4));
  if (minimum > maximum)
  {
    int buffer = maximum;
    maximum = minimum;
    minimum = buffer;
  }

  lcd.clear();
  while(1)
  {
    wert = getDist();

    lcd.setCursor(0,0);
    lcd.print(wert);
    lcd.print("   ");
    balkenDiagramm(1,0,wert,minimum,maximum);  
  }
}

void aufgabeC()
{
  int maximum,minimum,wert;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Kalibrierung");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Abdunkeln +");
  lcd.setCursor(0,1);
  lcd.print("Knopf Dr\365cken");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Dann erhellen +");
  lcd.setCursor(0,1);
  lcd.print("Knopf Dr\365cken");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("\176Wert 1");
  lcd.setCursor(1,1);
  lcd.print("Wert 2");  
  while(digitalRead(4)){
  }
  lcd.setCursor(0,1);
  lcd.print("\176");
  minimum = analogRead(0);
  while(!digitalRead(4));  
  while (digitalRead(4)){  
  }
  maximum = analogRead(0);
  while(!digitalRead(4));
  if (minimum > maximum)
  {
    int buffer = maximum;
    maximum = minimum;
    minimum = buffer;
  }

  lcd.clear();
  while(1)
  {
    wert = analogRead(0);

    lcd.setCursor(0,0);
    lcd.print(wert);
    lcd.print("   ");
    balkenDiagramm(1,0,wert,minimum,maximum);  
  }
}

void aufgabeB()
{
  int maximum,minimum,wert;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Kalibrierung");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Abdunkeln und");
  lcd.setCursor(0,1);
  lcd.print("Knopf Dr\365cken");
  while(digitalRead(4)){
  }
  minimum = analogRead(0);
  while(!digitalRead(4));
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Erhellen und");
  lcd.setCursor(0,1);
  lcd.print("Knopf Dr\365cken");
  while (digitalRead(4)){
  }
  maximum = analogRead(0);
  while(!digitalRead(4));
  lcd.clear();
  while(1)
  {
    wert = analogRead(0);

    lcd.setCursor(0,0);
    lcd.print(wert);
    lcd.print("   ");
    balkenDiagramm(1,0,wert,minimum,maximum);  
  }
}

void aufgabeA()
{
  int wert = analogRead(0);

  lcd.setCursor(0,0);
  lcd.print(wert);
  lcd.print("   ");
  balkenDiagramm(1,0,wert,0,1023);
}

void balkenDiagramm(int zeile, int spalte, int wert, int minimum, int maximum)
{
  lcd.setCursor(spalte,zeile);
  int intervalllaenge =(maximum-minimum)/7;
  int anzahlRauten = wert/intervalllaenge;
  if(anzahlRauten > 6)
    anzahlRauten = 6;
  for(int i = 0; i < anzahlRauten;i++)
  {
    lcd.print("\377"); //volle Kästchen gibt es bereits auf dem display
  }
  for(int i = 0 ; i < 6 - anzahlRauten ; i++)
  {
    //lcd.write(0); für galileo
    lcd.print((char)0); 
  }

}

void sendTrigger()
{
  digitalWrite(2, HIGH);
  delayMicroseconds(10);
  digitalWrite(2, LOW);
}

long fetchPulse()
{
  uint32_t zeit = micros();
  while (!digitalRead(3)) 
  {
    if (micros() - zeit > 23324) //8m (4 hin 4 zurück) /343 m/s = 0.0233236s also ~23324 us
    {
      return -1;
    } 
  }

  zeit = micros();
  while (digitalRead(3))
  {
    if (micros() - zeit > 23324)
    {
      return -1;
    } 
  }

  return micros() - zeit;
}

double getDist()
{
  sendTrigger();
  double abstand = (fetchPulse()*343.0)/20000.0; 
  return abstand;
}



