int a[] = {3, 1, 2, 5, 8, 4};
int b[] = {0, 0, 0, 0, 0, 0};

void setup(){
  Serial.begin(9600);
  arrayCopy(a, 0, b, 3, 3); printAry(b, 6);//=>[0,0,0,3,1,2]
  arrayCopy(a, 3, b, 0, 2); printAry(b, 6);//=>[5,8,0,3,1,2]
}

void loop(){}

void arrayCopy(int *fromAry,int fromStartPos,int *toAry,int toStartPos,int numElements){
  for (int i = 0; i < numElements;i++){
    toAry[i + toStartPos] = fromAry[i + fromStartPos];
  }  
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
