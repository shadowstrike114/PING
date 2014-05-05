int led = 13;
int delay_an = 1000;
int delay_aus = 1000;
/*
  Aufgabe 1:
  a) delay_an = 3000, delay_aus = 3000
  b) delay_an = 1000, delay_aus = 3000
  c) delay_an = 3000, delay_aus = 1000
*/

void setup() 
{
  pinMode(led, OUTPUT);
}


void loop() {
digitalWrite(led, HIGH);
delay(delay_an);  //Variable um die Zeit leichter verändern zu können
digitalWrite(led, LOW);
delay(delay_aus); //Diese Zeile muss hinzugefügt werden,um die LED zum blinken zu bringen
}
