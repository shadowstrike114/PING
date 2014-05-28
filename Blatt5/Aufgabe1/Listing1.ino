int f(int x){
int l=1;
  if (x < 0)
    return f(-x) + 1;
  while(x>9){ 
    l++; 
    x/=10; 
  }
  return l;
}
