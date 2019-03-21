#include <stdio.h>

int is_prime(int n);

int main(void)
{
  int n, integer = 2, count = 0;
  
  printf("Type how many primes, beginning with 2, in increasing size, and without missing any, that you'd like to see: ");
  scanf("%d", &n);
  
  while(count < n)
  {
    if(is_prime(integer) == 1)
    {
      printf("%d ", integer);
      integer++;
      count++;
    }
    
    else
    {
      integer++;
    }
  }
  
  return(0);
}

int is_prime(int p)
{
  int i;
  
  if(p == 2)
  {
    return(1);
  }
  if(p != 2 && p%2 == 0)
  {
    return(0);
  }
  else
  {
    for(i = 3; i < (p/2); i = i+2)
    {
      if(p%i == 0)
      {
        return(0);
      }
    }
    return(1);
  }
}