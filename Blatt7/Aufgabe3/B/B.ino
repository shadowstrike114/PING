void setup(){
  Serial.begin(9600);
  int  a = 5;
  int  b = 6;
  int  c = 3;
  int  x[] = {3, 1, 2, 5, 8, 4  };
  
  inlineSort3(&a, &b, &c);
  Serial.println(a);//=>3
  Serial.println(b);//=>5
  Serial.println(c);//=>6
  
  inlineSort3(&c, &b, &a);
  Serial.println(a);//=>6
  Serial.println(b);//=>5
  Serial.println(c);//=>3
  
  inlineSort3(&x[0], &x[1], &x[2]);
  printAry(x, 6);//=>[1, 2, 3, 5, 8, 4]
    
  inlineSort3(&x[3], &x[4], &x[5]);
  printAry(x, 6);//=>[1, 2, 3, 4, 5, 8]
}


void loop(){
}

void inlineSort3(int  *min, int *mid, int *max){
  if (*min == *mid || *mid == *max) return;
  inlineSort2(min,mid);
  inlineSort2(mid,max);
  inlineSort2(min,mid);  
}

void inlineSort2(int *min, int *max){
  if (*min == *max) return ; 
  if (*min > *max) {
    int buf = *min;
    *min = *max;
    *max = buf;
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




