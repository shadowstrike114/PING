int g(char* str) {
  int len = strlen(str);
  int n = 0;
  for (int I = 0; I <= len – 1;i++)
  {
    if(str[i] == ‘ ‘)
      n++;  
  }
  return n;
}
