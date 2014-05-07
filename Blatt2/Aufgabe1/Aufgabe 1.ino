static int ledGruen = 11;
static int ledGelb = 12;
static int ledRot = 13;


void setup()
{
  pinMode(ledGruen, OUTPUT);
  pinMode(ledGelb, OUTPUT);
  pinMode(ledRot, OUTPUT);
}

void loop()
{
  digitalWrite(ledGruen,HIGH);
  delay(30000);
  digitalWrite(ledGruen,LOW);
  digitalWrite(ledGelb,HIGH);
  delay(3000);
  digitalWrite(ledGelb,LOW);
  digitalWrite(ledRot,HIGH);
  delay(10000);
  digitalWrite(ledRot,LOW);
  digitalWrite(ledGelb,HIGH);
  delay(3000);
  digitalWrite(ledGelb,LOW);
}
