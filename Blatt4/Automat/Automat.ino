#include <LiquidCrystal.h>

// Getraenke
int DRINKS = 3;

// Namen der Getraenke
char *drink_name[] = { 
  "Wasser", "Limo", "Bier" };

// Preise der Getraenke (in Euro)
double drink_price[] = { 
  1.00, 1.50, 2.00 };

// LCD-Anzeige
int rsPin = 2;
int ePin  = 3;
int d4Pin = 4;
int d5Pin = 5;
int d6Pin = 6;
int d7Pin = 7;

LiquidCrystal lcd(rsPin, ePin, d4Pin, d5Pin, d6Pin, d7Pin);

// Schalter
int turnLeftPin  = 10;
int turnRightPin = 11;
int selectPin    = 12;
int eurobutton   = 9;
int centbutton   = 8;

int led = 13;


void print_drinks() {
  char buffer[200];
  strcpy(buffer, "");

  for (int i = 0; i < DRINKS; i++)
  {
    if (i > 0)
      strcat(buffer, " ");
    strcat(buffer, drink_name[i]);
  }
  lcd.print(buffer);
}

void print_prices() {
  int x = 0;
  for (int i = 0; i < DRINKS; i++)
  {
    char buffer[100];

    lcd.setCursor(x, 1);
    //sprintf(buffer, "%.2f", drink_price[i]);
    dtostrf(drink_price[i],1,2,buffer);  //kompatibilität zum normalen Arduino
    lcd.print(buffer);
    x += strlen(drink_name[i]) + 1;
  }
}

void show_selection(int drink) {
  int x = 0;

  for (int i = 0; i < drink; i++)
  {
    x += strlen(drink_name[i]);
    x += strlen(" ");
  }
  lcd.setCursor(x, 0);
  lcd.blink();
}

// Getränk auswählen und dessen Nummer zurückgeben
int choose_drink() {
  int current_selection = 0;
  unsigned long last_select = millis();

  show_selection(current_selection);

  while (1) {
    if (millis() - last_select > 50) {

      // Drehen nach rechts
      if (digitalRead(turnRightPin) == LOW) {
        if (current_selection < DRINKS - 1) {
          current_selection++;
        }
        show_selection(current_selection);
        last_select = millis();
      }

      // Drehen nach links
      if (digitalRead(turnLeftPin) == LOW) {
        if (current_selection > 0) {
          current_selection--;
        }
        show_selection(current_selection);
        last_select = millis();
      }

      // Drücken
      if (digitalRead(selectPin) == LOW) {
        lcd.noBlink();
        return current_selection;
      }
    }
  }
}

void pay_for_drink(int selection)
{
  uint32_t letzterEinwurf = 0 ;
  char buffer[100];

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.noBlink();
  lcd.noCursor();

  sprintf(buffer,"%s:",drink_name[selection]);

  lcd.print(buffer);
  lcd.setCursor(0,1);
  lcd.print("Gezahlt: ");

  ///euro zeichen hinzugefügt, wird hier eingefügt
  lcd.setCursor(15,0);
  lcd.print(char(0));
  lcd.setCursor(15,1);
  lcd.print(char(0)); 

  double preis = drink_price[selection];
  //sprintf(buffer, "%.2f", preis);
  dtostrf(preis,1,2,buffer);  //kompatibilität zum normalen Arduino
  lcd.setCursor(11,0);
  lcd.print(buffer);

  lcd.setCursor(11,1);
  lcd.print("0.00");

  while (preis > 0)
  { 
    if (millis() - letzterEinwurf > 250 && preis >= 1 && digitalRead(eurobutton))
    {
      letzterEinwurf = millis();
      preis -= 1;

      lcd.setCursor(11,0);
      //sprintf(buffer, "%.2f",preis);
      dtostrf(preis,1,2,buffer);  //kompatibilität zum normalen Arduino
      lcd.print(buffer);

      lcd.setCursor(11,1);
      //sprintf(buffer, "%.2f", drink_price[selection] - preis);
      dtostrf(drink_price[selection] - preis,1,2,buffer);  //kompatibilität zum normalen Arduino
      lcd.print(buffer);
    }

    if (millis() - letzterEinwurf > 250 && preis >= 0.50 && digitalRead(centbutton))
    {
      letzterEinwurf = millis();
      preis -= 0.50;

      lcd.setCursor(11,0);
      //sprintf(buffer, "%.2f",preis);
      dtostrf(preis,1,2,buffer);  //kompatibilität zum normalen Arduino
      lcd.print(buffer);

      lcd.setCursor(11,1);
      //sprintf(buffer, "%.2f", drink_price[selection] - preis);
      dtostrf(drink_price[selection] - preis,1,2,buffer);  //kompatibilität zum normalen Arduino
      lcd.print(buffer);
      letzterEinwurf = millis();
    }
  }
}

void dispense_drink(int selection)
{ 
  digitalWrite(13, HIGH);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Zahlung erfolgt!");
  lcd.setCursor(0,1);
  lcd.print("Zur\365ck mit Druck");// ü ist Adresse 11111100 dez 252 oktal 374

  while (digitalRead(selectPin));

  delay(500);

  digitalWrite(13, LOW);

}

void setup() {
  // put your setup code here, to run once:
  pinMode(rsPin, OUTPUT);
  pinMode(ePin,  OUTPUT);
  pinMode(d4Pin, OUTPUT);
  pinMode(d5Pin, OUTPUT);
  pinMode(d6Pin, OUTPUT);
  pinMode(d7Pin, OUTPUT);

  pinMode(turnLeftPin,  INPUT_PULLUP);
  pinMode(turnRightPin, INPUT_PULLUP);
  pinMode(selectPin,    INPUT_PULLUP);

  pinMode(eurobutton, INPUT);
  pinMode(centbutton, INPUT);

  pinMode(led,  OUTPUT);


  byte euro[8] = { 
    B01110,
    B10001, 
    B11100, 
    B10000, 
    B11100, 
    B10001, 
    B01110, 
    B00000     };

  lcd.createChar(0,euro);
  lcd.begin(16, 2);
  lcd.cursor();  
}

void loop() {
  // put your main code here, to run repeatedly: 
  lcd.clear();
  print_drinks();
  print_prices();
  int selection = choose_drink();
  pay_for_drink(selection);
  dispense_drink(selection);

  // Weitere Funktionen, etwa:
  // pay_for_drink(selection);
  // dispense_drink(selection);
}

