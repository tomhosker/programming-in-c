#include <stdio.h>

#define ALPHABET_SIZE 26

int scode(int a);

int main(void)
{
  char a;
  
  printf("Type some text, and I shall convert it into my mysterious code!");
  while(a != EOF)
  {
    a = getchar();
    putchar(scode(a));
  }
  return(0);
}

int scode(int a)
{
  if((('A' <= a) && (a <= 'Z'))||(('a' <= a) && (a <= 'z')))
  {
    if(('A' <= a) && (a <= 'Z'))
    {
      int Alpha = ((ALPHABET_SIZE-1)+(2*'A'))-a;
      return(Alpha);
    }
    else
    {
      int alpha = ((ALPHABET_SIZE-1)+(2*'a'))-a;
      return(alpha);
    }
  }
  else
  {
    return(a);
  }
}