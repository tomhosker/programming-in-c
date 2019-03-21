#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define MAX_RANDOM 200
#define RADIUS 100
#define CALC_LENGTH 10000

int is_in_circle(int x, int y);

int is_in_square(int x, int y);

int main(void)
{
  srand(time(NULL));
  int x, y;
  double rough_pi;
  int count = 0;
  int count_a = 1;
  int count_c = 1;
  
  while(count < CALC_LENGTH)
  {
    x = rand()%MAX_RANDOM;
    y = rand()%MAX_RANDOM;
    
    if(is_in_square(x, y) == TRUE)
    {
      count_a++;
    }
    if(is_in_circle(x, y) == TRUE)
    {
      count_c++;
    }
    
    rough_pi = (4*(double)count_c)/(double)count_a;
    count++;
    
    printf("%lf, ", rough_pi);
  }
  
  return(0);
}

int is_in_circle(int x, int y)
{
  if((x*x)+(y*y) <= (RADIUS*RADIUS))
  {
    return(TRUE);
  }
  else
  {
    return(FALSE);
  }
}

int is_in_square(int x, int y)
{
  if(x <= RADIUS && y <= RADIUS)
  {
    return(TRUE);
  }
  else
  {
    return(FALSE);
  }
}