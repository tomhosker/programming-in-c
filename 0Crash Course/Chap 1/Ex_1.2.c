#include <stdio.h>

int main(void)
{
  int a, b, c, result;
  
  printf("Input three integers: ");
  
  while(scanf("%d %d %d", &a, &b, &c) == 3)
  {
    result = (2*(a+b+c))+7;
    printf("Twice the sum of the three integers plus seven is %d !", result);
  }
  
  return(0);
}