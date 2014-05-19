int  taster = 2;
int led = 3;
int tasterGedrueckt = 0;
int zaehler = 0;
// Gewuenschtes Verhalten: LED leuchtet, wenn Taster
// zwischen einschl. 6x und einschl.9xgedrueckt
void setup()
{
  pinMode(led,OUTPUT);
  pinMode(taster,INPUT);
}

void loop() {
  tasterGedrueckt = digitalRead(taster);
  if
    (tasterGedrueckt = 1) { 
    zaehler++; 
  }
  if
    (5 < zaehler < 10) {
    digitalWrite(led, HIGH);
  }
else
{
  digitalWrite(led, LOW);
}
}


/*
-zaehler nicht deklariert
-setup fehlt
-pinModes fehlen
*/
