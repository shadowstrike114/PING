int leds[] = {7, 8, 9};

void setup() {
  int  i = 0;
  while (i < 2) {
    pinMode(leds[i++], OUTPUT);
  }
}

void loop()
{
  
}

/*
-loop fehlt
-die schleife muss die array indizes verwenden nicht den inhalt
*/
