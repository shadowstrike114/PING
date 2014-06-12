int a[] = {3,1,3,1,3,8,8,4};

void setup()
{
  Serial.begin(9600); 
  Serial.println(distinctCount(a,3));
  Serial.println(distinctCount(a,4));
  Serial.println(distinctCount(a,7));
  Serial.println(distinctCount(a,8));
}


void loop()
{
}
int distinctCount(int a[],int size)
{
  //Wenn das Array sortiert ist bzw. vorher sortiert wird, wird die Aufgabe sehr einfach, 
  //da man einfach jedes Element mit dem vorherigen vergleichen und entsprechend hochzählen muss
  int anzahl = 0;
  int b[size];
  
  //array in ein anderes kopieren
  for (int i = 0; i < size;i++)
  {
    b[i] = a[i];
  } 
  //prüfen, ob die null vorkommt
  for (int i = 0; i < size; i++)
  {
    if (a[i] == 0)
    {
      anzahl++;
      break;
    }
  }
  
  //wenn eine Zahl gefunden wird hochzählen und alle anderen Vorkommen dieser zahl null setzen
  for (int i = 0; i < size; i++)
  {
    if (b[i] != 0)
    {
      anzahl++;
      elementReplace(b,size,b[i],0);
    }
  }
 return anzahl;  
}


void elementReplace(int a[], int size, int replaceElem, int replaceWith)
{
  for (int i = 0;i < size;i++)
 {
   if (a[i] == replaceElem)
     a[i] = replaceWith;
 } 
}
