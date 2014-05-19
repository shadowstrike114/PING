//Gewuenschtes Verhalten: Den String an sich selbst haengen
void setup() {
  char buffer[10];
  char str[] = {'a','b','c','d'};
  strcat(buffer, str);
  strcat(buffer, str); //buffer enthält str an str
  Serial.begin(9600);
}

void loop()
{
  strcat(buffer, str);
}


/*
a):Fehler
b),d):-loop fehlt
      -Stray'\' in program: mit den verwendeten zeichen können chars nicht erkannt werden. man muss ' benutzen
      -expected unqualified -id before '[' token:[] müssen hinter str
c): srtcat verlängert den string nicht


*/
