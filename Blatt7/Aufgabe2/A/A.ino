int a[] = {3, 1, 2, 5, 8, 4};
int b[] = {0, 0, 0, 0, 0, 0};

void setup(){
  Serial.begin(9600);
  arrayCopy(a, b, 3); printAry(b, 6);//=>[3,1,2,0,0,0]
  arrayCopy(a, b, 6); printAry(b, 6);//=>[3,1,2,5,8,4]
}

void loop(){}

void arrayCopy(int *fromAry,int *toAry,int numElements){
  for (int i = 0; i < numElements;i++){
    toAry[i] = fromAry[i];
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
