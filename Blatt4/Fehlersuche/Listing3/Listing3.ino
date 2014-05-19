int led = 3;
int naechsterWechsel = 0;
void setup() {
  pinMode(led,OUTPUT); 
  naechsterWechsel = millis() + 300; 
}
void loop() {
  if
    (millis() > naechsterWechsel) {
    digitalWrite(led, !digitalRead(led));
    naechsterWechsel = millis() + 300;
  }
}


/*
-millis klammern fehlen überall
 -beim digitalWrite fehlt die led
 -pinMode fehlt
 */
