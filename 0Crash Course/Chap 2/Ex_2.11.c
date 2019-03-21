#include <stdio.h>

int main(void)
{
  int a = 0, b = 0, c = 0; /* Predictions in the comments... */
  
  a = ++b + ++c;
  printf("%d %d %d\n", a, b, c); /* a will be 2; b and c will be 1. */
  
  a = b++ + c++;
  printf("%d %d %d\n", a, b, c); /* a will be 2; b and c will be 2. */
  
  a = ++b + c++;
  printf("%d %d %d\n", a, b, c); /* a will be 5; b and c will be 3. */
  
  a = b-- + --c;
  printf("%d %d %d\n", a, b, c); /* a will be 5; b and c will be 2. */
  
  return(0);
}