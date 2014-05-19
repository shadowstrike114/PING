int ledLeuchtet = 0;
int naechsterWechsel = 0;
int led = 13;

void setup()
{
  pinMode(led,OUTPUT);  
}

void loop() {
    if  (millis() > naechsterWechsel ) {
      digitalWrite(led, !ledLeuchtet);
      ledLeuchtet = !ledLeuchtet;
      naechsterWechsel = millis() + 300;
    }
}

/*
-setup fehlt
-Äußere Funktion unnötig
-pinMode fehlt
-led muss initialisiert werden
-ledLeuchtet muss umgeschaltet werden
*/
