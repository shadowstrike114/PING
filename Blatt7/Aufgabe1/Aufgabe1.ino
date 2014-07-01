#include <LiquidCrystal.h>

const int INF = 30000;
const int CITIES = 6;
const char *name[CITIES] = {
  "SB","DO","F","HB","H","HH"};
const int dist[CITIES][CITIES] = {
  { 
    0, 354, 177, 593, 532, 692       }
  ,
  { 
    354, 0, 220, 239, 212, 360       }
  ,
  { 
    177, 220, 0, 459, 355, 515       }
  ,
  { 
    593, 239, 459, 0, 130, 121       }
  ,
  { 
    532, 212, 355, 130, 0, 160       }
  ,
  { 
    692, 360, 515, 121, 160, 0       }
};
const int via[CITIES][CITIES] = {
  { 
    0, 0, 0, 1, 2, 4       }
  ,
  { 
    1, 1, 1, 1, 1, 3       }
  ,
  { 
    2, 2, 2, 1, 2, 4       }
  ,
  { 
    1, 3, 1, 3, 3, 3       }
  ,
  { 
    2, 4, 4, 4, 4, 4       }
  ,
  { 
    2, 3, 4, 5, 5, 5       }
};

#define OK   8
#define PREV 9
#define NEXT 10

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void schritt(int von,int zu,int danach,int ziel);
int entfernung(int von,int zu);
void navigation(int von,int zu);
void auswahl();
void abbruch();

uint32_t letzterDruck = 0;
int start;
int ziel;
int pos = 0;
boolean weiter  = false;
boolean zurueck = false;
boolean abbr = false;
boolean navigationAktiv = false;
boolean zeigen = false;

void setup() {
  lcd.begin(16, 2);

  pinMode(OK ,INPUT);
  pinMode(PREV ,INPUT);
  pinMode(NEXT ,INPUT);
}

void loop() {
  if (digitalRead(NEXT) && millis() - letzterDruck > 250){
    weiter = true;
    letzterDruck = millis();
  }
  if (digitalRead(PREV) && millis() - letzterDruck > 250){
    zurueck = true;
    letzterDruck = millis();
  }
  if (digitalRead(OK) && millis() - letzterDruck > 250){
    abbr = true;
    letzterDruck = millis();
  }
  
  if (navigationAktiv){
    navigation(start,ziel);
    abbruch();
  }
  else if (!navigationAktiv){
    auswahl();
    navigationAktiv = true;
    zeigen = true;
  }

}

void abbruch(){
  if (abbr){
    lcd.clear();
    lcd.print("Abbrechen? (y/n)");
    lcd.setCursor(0,1);
    lcd.print("Nein");

    boolean abbrechen = false;
    
    while (digitalRead(OK));
    delay(250);
    while (!digitalRead(OK))
    {
      if ((digitalRead(PREV) || digitalRead(NEXT)) && millis() - letzterDruck > 250){
        abbrechen = !abbrechen;
        letzterDruck = millis();
      }
      if (abbrechen){
        lcd.setCursor(0,1);
        lcd.print("Ja  ");  
      }else{
        lcd.setCursor(0,1);
        lcd.print("Nein"); 
      }
    }
    if (abbrechen)
      navigationAktiv = false;
    
    abbr = false;
    zeigen = true;
    delay(250);
  }  
}

void auswahl(){
  static int wahl = 0;

  lcd.clear();
  lcd.print("Start ausw\341hlen");
  lcd.setCursor(0,1);

  lcd.print(name[wahl]);
  lcd.print(" ");//2ten buchstaben löschen
  Serial.println(digitalRead(OK));

  while(!digitalRead(OK)){
    if ( digitalRead(NEXT) && millis() - letzterDruck > 250)
    {
      if (wahl < CITIES - 1)
      {
        wahl++;
        lcd.setCursor(0,1);
        lcd.print(name[wahl]);
        lcd.print(" ");//2ten buchstaben löschen
      }
      letzterDruck = millis();
    }
    if ( digitalRead(PREV) && millis() - letzterDruck > 250)
    {
      if (wahl > 0)
      {
        wahl--;
        lcd.setCursor(0,1);
        lcd.print(name[wahl]);
        lcd.print(" ");//2ten buchstaben löschen
      }
      letzterDruck = millis();
    } 
  }
  start = wahl; 

  lcd.clear();
  lcd.print("Ziel ausw\341hlen");
  lcd.setCursor(0,1);

  lcd.print(name[wahl]);
  lcd.print(" ");//2ten buchstaben löschen
  
  delay(250);

  while(!digitalRead(OK)){
    if ( digitalRead(NEXT) && millis() - letzterDruck > 250)
    {
      if (wahl < CITIES - 1)
      {
        wahl++;
        lcd.setCursor(0,1);
        lcd.print(name[wahl]);
        lcd.print(" ");//2ten buchstaben löschen
        Serial.println("test");
      }
      letzterDruck = millis();
    }
    if ( digitalRead(PREV) && millis() - letzterDruck > 250)
    {
      if (wahl > 0)
      {
        wahl--;
        lcd.setCursor(0,1);
        lcd.print(name[wahl]);
        lcd.print(" ");//2ten buchstaben löschen
      }
      letzterDruck = millis();
    } 
  }
  ziel = wahl;
  pos = 0;
  delay(250);
  letzterDruck = millis();

}


void navigation(int von, int zu){
  int ort = von;
  
  if (weiter || zurueck || zeigen){
    zeigen = false;
    for (int i = 0; i < pos; i++)
    {
      ort = via[zu][ort];
    }
    int nxt = via[zu][ort];
    int dann = via[zu][nxt];

    if (ort != zu && weiter){
      pos++;
      zeigen = true;
    }
    if (ort >= 0 && zurueck){
      zeigen = true;
      pos--;
    }   
    
    schritt(ort,nxt,dann,zu);
    
    weiter  = false;
    zurueck = false;
  }  
}

int entfernung(int von,int zu){
  int strecke = 0;
  while (von != zu){
    int start = von;
    von = via[zu][von];
    strecke += dist[start][von];
  }
  return strecke; 
}


void schritt(int von,int zu,int danach,int ziel){
  if (von == zu){
    lcd.clear();
    lcd.print("Ziel erreicht");
    lcd.setCursor(0,1);
    char buffer[32];
    sprintf(buffer,"0 km bis %s", name[zu]);
    lcd.print(buffer);    
  }
  else{
    lcd.clear();
    char buffer[32];
    sprintf(buffer, "%s\176%s! Danach\176%s", name[von],name[zu],name[danach]);
    lcd.print(buffer);
    lcd.setCursor(0,1);
    sprintf(buffer, "Zu Fahren: %d",entfernung(von,ziel));
    lcd.print(buffer);
  }

}



