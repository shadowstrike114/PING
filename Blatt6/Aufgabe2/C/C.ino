int a[] = {3,1,3,1,3,8,8,4};

void setup()
{
   Serial.begin(9600); 
   printAry(a,0);
   printAry(a,8);
}


void loop()
{}

void printAry(int a[],int size)
{
  Serial.print("[");
  for (int i = 0;i < size;i++)
  {
    Serial.print(a[i]);
    if (i < size - 1)
      Serial.print(", ");    
  }
  Serial.println("]"); 
}
