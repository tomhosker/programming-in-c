#include <stdio.h>
#include <math.h>

int main(void)
{
  double x, y;
  while(x != EOF)
  {
    printf("Type in a number: ");
    scanf("%lf", &x);
    printf("\n");
    y = (cos(x)*cos(x))+(sin(x)*sin(x));
    printf("You entered %lf.\n", x);
    printf("cos^2(%lf) + sin^2(%lf)", x, x);
    printf(" = %.0lf.\n\n\n", y);
  }
  
  return(0);
}