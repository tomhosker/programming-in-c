#include <stdio.h>
#define MIN_DENOMINATION 20

int main(void)
{
  int requested;
  
  printf("How much money would you like?");
  scanf("%d", &requested);
  int requested_lower = requested-(requested%MIN_DENOMINATION);
  int requested_upper = requested_lower+MIN_DENOMINATION;
  
  if(requested > 0)
  {
    while(requested%MIN_DENOMINATION != 0)
    {
      printf("I can only dispense %ds.\n", MIN_DENOMINATION);
      printf("I can offer you %d or %d.", requested_lower, requested_upper);
      scanf("%d", &requested);
    }
    
    printf("Dispensing...");
  }
  else
  {
    printf("Argh! You made me crash! Please enter a positive integer next time!");
    return(0);
  }
  
  return(0);
}