int a[] = {3,1,2,5,8,4};

void setup()
{
   Serial.begin(9600); 
   Serial.println(arrayMax(a,6));
   Serial.println(arrayMax(a,4));
   Serial.println(arrayMax(a,2));
}


void loop()
{}

int arrayMax(int a[],int size)
{
  int wert = 0;
  for (int i = 0;i < size;i++)
  {
    if (a[i] > wert)
      wert = a[i];
  }
  return wert;  
}
