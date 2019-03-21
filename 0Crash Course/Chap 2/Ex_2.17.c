#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int median = RAND_MAX/2;
  int count;
  int minus_count = 0, plus_count = 0;
  
  for(count = 0; count < 500; count++)
  {
    if(rand() >= median)
    {
      plus_count++;
    }
    else
    {
      minus_count++;
    }
    printf("%d ", plus_count-minus_count);
  }
  
  return(0);
}