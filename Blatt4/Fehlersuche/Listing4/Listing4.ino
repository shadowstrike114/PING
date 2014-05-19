int taster = 2;
int led = 3;

void setup(){
  pinMode(led,OUTPUT);
  pinMode(taster,INPUT);
}

void loop()
{
  if (digitalRead(taster))
  {
    digitalWrite(led,HIGH);
  }else
  {
    digitalWrite(led,LOW);
  }
}






/*
-setup fehlt
-pinMode fehlt
-digitalWrite und read fehlt
 */
