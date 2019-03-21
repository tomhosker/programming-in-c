#include <stdio.h>

#define HEIGHT 17

int main(void)
{
  int i = 0;
  
  printf("\n\nCCCCCCCCCCCCCCCCCCCCCCCCCC\n");
  printf("CCCCCCCCCCCCCCCCCCCCCCCCCC\n");
  while(i < HEIGHT)
  {
    printf("CCC\n");
    i=i+1;
  }
  printf("CCCCCCCCCCCCCCCCCCCCCCCCCC\n");
  printf("CCCCCCCCCCCCCCCCCCCCCCCCCC\n\n\n");
  return(0);
}