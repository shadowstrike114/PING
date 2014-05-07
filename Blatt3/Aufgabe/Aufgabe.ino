static uint8_t segment[] = { 4, 3, 5, 2, 6, 8, 7, 9 };
static uint8_t kreis[] = { 0, 2, 5, 6, 4, 1 };
static uint8_t zahlen[11][8]={
                       {  1,      //0
                         1,1,
                          0,
                         1,1,
                          1, 0 },
                          
                        { 0,      //1
                         0,1,
                          0,
                         0,1,
                          0, 0},
                          
                        { 1,      //2
                         0,1,
                          1,
                         1,0,
                          1, 0},
                          
                        { 1,      //3
                         0,1,
                          1,
                         0,1,
                          1, 0},
                          
                        { 0,      //4
                         1,1,
                          1,
                         0,1,
                          0, 0},
                          
                        { 1,      //5
                         1,0,
                          1,
                         0,1,
                          1, 0},
                          
                        { 1,      //6
                         1,0,
                          1,
                         1,1,
                          1, 0},
                          
                        { 1,      //7
                         0,1,
                          0,
                         0,1,
                          0, 0},
                          
                        { 1,      //8
                         1,1,
                          1,
                         1,1,
                          1, 0},
                          
                        { 1,      //9
                         1,1,
                          1,
                         0,1,
                          1, 0},
                          
                        { 1,      //E rror
                         1,0,
                          1,
                         1,0,
                          1, 0}
                        };
static uint8_t button = 10;
boolean gedrueckt = false;
unsigned long letzterDruck = 0;
unsigned long letzteAktion = 0;

void dot();
void lauflicht();
void digit();
void wuerfel();
void wuerfeleins();
void wuerfelzwei();

void setup()
{
  for (int i = 0; i < 9; i++)
  {
    pinMode(segment[i], OUTPUT);
  }
  pinMode(button, INPUT);
}

void loop()
{
  //####Aufgaben####
  //lauflicht();      // Aufgabe 2 
  //wuerfeleins();    //Aufgabe 3
  //wuerfelzwei();    //Aufgabe 3 Bonusaufgabe
  //digit(123);       //Aufgabe 4, werte > 9: undefiniertes Verhalten, wnegative werte: undefiniertes verhalten, da digit unsigned verwendet und die funktion daher mit einem sehr großen wert aufgerufen wird 
}



void dot(unsigned int nr)
{
  for (int i = 0 ; i < 9 ; i++)
  {
    digitalWrite(segment[i],LOW);
  }
  digitalWrite(segment[nr], HIGH);
}

void lauflicht()
{ 
  for (int i = 0 ; i < 6 ; i++)
  {
    dot(kreis[i]);
    delay(200);
  }
}

void digit(unsigned int zahl)
{ 
  for (int i = 0; i < 8 ; i++)
  {
    if (zahl < 10)
      digitalWrite(segment[i],zahlen[zahl][i]);
    else
      digitalWrite(segment[i],zahlen[10][i]);
  }
}

void wuerfel()
{  
    digit(random() % (9 + 1));
}

void wuerfeleins()
{
  if (digitalRead(button) && millis() - letzterDruck > 400)
  {
    gedrueckt = !gedrueckt;  
    letzterDruck = millis();
  }
  
  if (gedrueckt && millis() - letzteAktion > 50)
  {
    wuerfel();
    letzteAktion = millis();
  }
  
}

void wuerfelzwei()
{
  if (digitalRead(button))
  {
    for (int i = 50; i < 500; i += 25)
    {
      wuerfel();
      delay(i);    
    }
    digitalWrite(segment[7], HIGH);
  }
}  
