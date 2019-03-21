#include <stdio.h>

int next(int x);

int main(void)
{
  int x = 77;
  
  while(x != 17)
  {
    printf("%d\n", x);
    x = next(x);
  }
  
  return(0);
}

int next(int x)
{
  if(x%2 == 0)
  {
    return(x/2);
  }
  else
  {
    return((3*x)+1);
  }
}