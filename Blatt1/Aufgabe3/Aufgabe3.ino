/*
  Aufgabe3, Listing 1:
  a) Der compiler gibt mehrere Fehler aus und unterbricht das Übersetzen
  b) Ja: -function definition does not declare parameters
            - Die Art der Wertzuweisung bei den Variablen entspricht der in Pascal/Delphi, funktioniert so aber nicht in C
            - Void setup und void loop haben keine Klammern, der Compiler findet also keinen bereich in dem variablen an die funktion übergeben werden können
         -'led_red' was not declared in this scope, das gleiche für led_green
            - C ist Case-sensitive, die Groß- und Kleinschreibung bei Variablennamen muss also übereinstimmen
         -error: expected `)' before ';' token
            - Variablen in Funktionsaufrufen werden in C nur durch komma getrennt
         -error: 'pin_mode' was not declared in this scope, genauso auch für digital_write
            - Die benötigten Standardfunktionen heißen pinMode und digitalWrite, die verwendeten Funktionen wurden nie definiert
  c)---
  d)siehe Kommentare  
*/



/*
int led_red = 12;//led_Red -> led_red, : entfernt
int led_green = 12+1;//led_Green -> led_green, : entfernt


void setup() //Klammern hinzugefügt 
{
pinMode(led_red, OUTPUT);//pin_mode -> pinMode, ; - >,
pinMode(led_green, OUTPUT);//pin_mode -> pinMode, ; - >,
}

void loop() //Klammern hinzugefügt
{
digitalWrite(led_red, HIGH);//digital_write -> digitalWrite. ; -> ,
digitalWrite(led_green, LOW);//digital_write -> digitalWrite. ; -> ,
}

*/


/*
  Aufgabe3, Listing 2:
  a) Fehlermeldung des Compilers
  b) -error: ISO C++ forbids declaration of 'loop' with no type
       -die Funktion loop hat keinen Typ. Dieser wird gebraucht,damit der Compiler weiß,was sie zurückgibt
     -error: 'HI' was not declared in this scope, gilt auch für LO
       - HI und LO sind als Variablen nicht initialisiert worden
     -error: expected `;' before 'delay'
       - Es fehlen alle Strichpunkte. Ohne diese kann der Compiler die einzelnen Anweisungen nicht trennen
     -error: invalid suffix "s" on floating constant
       - Der compiler kennt Abkürzungen um beim Eingeben von Zahlen im Code deren Typ festzulegen (z.b 16000000UL um die Zahl mit dem typ unsigned long zu übergeben).
         Das s ist jedoch keine solche Abkürzung und kann, wenn nicht als string oder char übergeben nicht interpretiert werden
     -In function `main':C:\Program Files (x86)\Arduino\hardware\arduino\cores\arduino/main.cpp:11: undefined reference to `setup'
       - in der Arduino Umgebung müssen die Funktionen setup und loop immer aufgerufen werden 
      
  c) Nach beheben dieser Fehler kann der Code kompiliert werden. Probleme hierbei sind jedoch:
     -Pin 13 wurde nicht als Output konfiguriert, gibt also kein Signal aus
     -delay(1.0) pausiert für eine millisekunde, angedacht waren aber offenbar 1000 (=1s)
     -Der pin wird nur für wenige Bruchteile einer Sekunde ausgeschaltet,es ist aber wohl ein blinken erwünscht 
  d) siehe Kommentare
  
*/


/*
void setup(){
  pinMode(13,OUTPUT); //pin 13 als output setzen
} //void setup ergänzt

void loop() {
digitalWrite(13, HIGH); //; ergänzt, HI -> HIGH
delay(1000);//; ergänzt, s entfernt, 1.0 -> 1000
digitalWrite(13, LOW);//; ergänzt , LO -> LOW
delay(1000);//delay ergänzt
}
*/
