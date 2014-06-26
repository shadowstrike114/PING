int a = 5;
int b = 6;
int c = 3;
int d = 2;

void setup(){
  Serial.begin(9600);

  inlineSort2(&a, &b);
  Serial.println(a);//=>5
  Serial.println(b);//=>6

  inlineSort2(&c, &d);
  Serial.println(c);//=>2
  Serial.println(d);//=>3

  inlineSort2(&b, &d);
  Serial.println(b);//=>3
  Serial.println(d);//=>6
}


void loop(){
}

void inlineSort2(int *min, int *max){
  if (*min == *max) return ; 
  if (*min > *max) {
    int buf = *min;
    *min = *max;
    *max = buf;
  }
}




