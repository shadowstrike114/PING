#include <Tone.h> //für intel Galileo
#include <Wire.h>



#define TRIGPIN 2
#define ECHOPIN 3
#define PIEZO 10
#define RECBUTTON  7
#define PLAYBUTTON 8
#define STATUSLED  6

boolean recordAvailable = false;
int reclen = 0;
boolean recording =       false;
boolean play =            false;
uint32_t letzterDruck = 0;

//Töne und Frequenzen
#define C2  523
#define F2  698
#define G   392
#define NULL 0
#define A2  880
#define G2  783
#define E2  659
#define D2  587
#define BD2 554


// C: Jeopardy Theme Music
uint16_t wartemelodie[31] = { 
  C2,C2,F2,F2,C2,C2,G,G,C2,C2,F2,F2,C2,C2,G,G,
  C2,C2,F2,F2,C2,C2,F2,F2,A2,NULL,G2,F2,E2,D2,BD2};

uint16_t aufzeichnung[500]; //alle 1/150 s ein Wert ,festgelegt durch die interpoliertAusgeben Funktion

void sendTrigger();
void alles();
long fetchPulse();
double getDist();
void interpoliertAusgeben();

void setup()
{
  pinMode(STATUSLED, OUTPUT);
  pinMode(RECBUTTON ,INPUT_PULLUP);
  pinMode(PLAYBUTTON,INPUT_PULLUP);
  //pinMode(PIEZO,     OUTPUT);
  pinMode(TRIGPIN,   OUTPUT_FAST);
  pinMode(ECHOPIN,   INPUT_FAST);
  //Serial.begin(9600);
}


void loop()
{
  alles();
}

void alles()
{
    if (!digitalRead(RECBUTTON) && millis() - letzterDruck > 250){
    Serial.println("REC");
    recording = !recording;
    play = false;
    digitalWrite(STATUSLED,LOW);
    if (recording){
      for (int i = 0; i < reclen;i++)
      {
         aufzeichnung[i] = 0; 
      }
      reclen = 0;
    }else{
      recordAvailable = true;
      //Serial.println(reclen);
    }
    letzterDruck = millis();
  }
  if (!digitalRead(PLAYBUTTON) && millis() - letzterDruck > 250){
    Serial.println("PLAY");
    play = !play;
    if (!play)
      digitalWrite(STATUSLED,LOW);
    letzterDruck = millis();
  }
  
  if (play){
    digitalWrite(STATUSLED,HIGH);
    if (recordAvailable)
    {
      static int pos = 0;
      static int alterTon = 0;
      static int ton = 0;
      alterTon = ton;
      ton = aufzeichnung[pos];
      if (++pos > reclen)
      {
        pos = 0;
      }
      interpoliertAusgeben(alterTon,ton);    
    }
    else{
      static int pos = 0;
      tone(PIEZO,wartemelodie[pos]);
      if (++pos > 30){
        pos = 0;
      }
      delay(250);
    }
  }

  if (!play)
  {
    static double tonvorher = 1000;
    static double ton = 100;
    ton = (1000/50)*getDist();
    if (recording){
      aufzeichnung[reclen++] = ton;
      digitalWrite(STATUSLED,!digitalRead(STATUSLED));
    }
    interpoliertAusgeben(tonvorher,ton);
    tonvorher = ton;
  }
  
  if (!play && !recording)
    digitalWrite(STATUSLED,LOW);
}


void interpoliertAusgeben(double startwert,double endwert)
{
  double differenz = (startwert - endwert)/50;
  if (startwert < endwert)
  {
    while (startwert < endwert)
    {
      tone(PIEZO,startwert);
      startwert -= differenz;
      delay(2);
    }
  }
  else if (startwert > endwert)
  {
    while (startwert > endwert)
    {
      tone(PIEZO,startwert);
      startwert -= differenz;
      delay(2);
    }

  }


}

void sendTrigger()
{
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
}

long fetchPulse()
{
  uint32_t zeit = micros();
  while (!digitalRead(ECHOPIN)) 
  {
    if (micros() - zeit > 23324) //8m (4 hin 4 zurück) /343 m/s = 0.0233236s also ~23324 us
    {
      return -1;
    } 
  }

  zeit = micros();
  while (digitalRead(ECHOPIN))
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


