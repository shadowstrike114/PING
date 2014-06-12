int a[] = {
  3,1,3,1,3};

void setup()
{
  Serial.begin(9600); 
  elementReplace(a,5,3,30);printAry(a,5);
  elementReplace(a,4,30,35);printAry(a,5);
  elementReplace(a,5,1,0);printAry(a,5);
}


void loop()
{
}

void printAry(int a[],int size)
{
  Serial.print("[");
  for (int i = 0;i < size;i++)
  {
    Serial.print(a[i]);
    if (i != size - 1)
      Serial.print(", ");
  }
  Serial.println("]"); 
}


void elementReplace(int a[], int size, int replaceElem, int replaceWith)
{
  for (int i = 0;i < size;i++)
 {
   if (a[i] == replaceElem)
     a[i] = replaceWith;
 } 
}
