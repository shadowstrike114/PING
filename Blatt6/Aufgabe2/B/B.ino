int a[] = {3,1,3,1,3,8,8,4};


void setup()
{
   Serial.begin(9600); 
   Serial.println(elementCount(a,8,0));
   Serial.println(elementCount(a,8,1));
   Serial.println(elementCount(a,8,3));
}


void loop()
{}

int elementCount(int a[],int size,int elem)
{
  int wert = 0;
  for (int i = 0;i < size;i++)
  {
    if (a[i] == elem)
      wert++;
  }
  return wert;  
}
