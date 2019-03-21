#include <stdio.h>
#include <limits.h>
#include <math.h>

#define SCALENE 0
#define ISOSCELES 1
#define EQUILATERAL 2

int is_correct_range(int alpha, int beta, int gamma);

int maximum(int alpha, int beta, int gamma);

int is_a_triangle(int a, int b, int c);

int kind_of_triangle(int a, int b, int c);

int is_right_angled(int a, int b, int c);

int main(void)
{
  int alpha, beta, gamma, a, b, c;
  
  while(1 == 1)
  {
    printf("Type in the lengths of the sides of a triangle in integer units.");
    
    if(scanf("%d%d%d", &alpha, &beta, &gamma) == 3 && is_correct_range(alpha, beta, gamma) == 1 )
    {
      if(maximum(alpha, beta, gamma) == alpha)
      {
        c = alpha;
        a = beta;
        b = gamma;
        if(is_a_triangle(a, b, c) == 0)
        {
          printf("That's not a triangle!");
          return(0);
        }
      }
      if(maximum(alpha, beta, gamma) == beta)
      {
        c = beta;
        a = alpha;
        b = gamma;
        if(is_a_triangle(a, b, c) == 0)
        {
          printf("That's not a triangle!");
          return(0);
        }
      }
      if(maximum(alpha, beta, gamma) == gamma)
      {
        c = gamma;
        a = alpha;
        b = beta;
        if(is_a_triangle(a, b, c) == 0)
        {
          printf("That's not a triangle!");
          return(0);
        }
      }
    }
    else
    {
      if(alpha == -999)
      {
        printf("Kay bye.");
        return(0);
      }
      else
      {
        printf("Please enter three positive integers, each of which is less than %f.\n", sqrt(INT_MAX));
      }
    }
    
    if(is_correct_range(a, b, c) == 1)
    {
      printf("You entered a triangle with side-lengths: %d, %d, %d.\n", a, b, c);
    }
  
    if(is_correct_range(a, b, c) == 1)
    {
      if(kind_of_triangle(a, b, c) == SCALENE)
      {
        printf("The triangle is scalene.\n");
      }
      if(kind_of_triangle(a, b, c) == ISOSCELES)
      {
        printf("The triangle is isosceles.\n");
      }
      if(kind_of_triangle(a, b, c) == EQUILATERAL)
      {
        printf("The triangle is equilateral.\n");
      }
      if(is_right_angled(a, b, c) == 1)
      {
        printf("The triangle is right-angled.\n\n");
      }
      else
      {
        printf("The triangle is not right-angled.\n\n");
      }
    }
    else
    {
      return(0);
    }
  }
  return(0);
}

int is_correct_range(int alpha, int beta, int gamma)
{
  if(alpha > 0 && beta > 0 && gamma > 0 && alpha < sqrt(INT_MAX) && beta < sqrt(INT_MAX) && gamma < sqrt(INT_MAX))
  {
    return(1);
  }
  else
  {
    return(0);
  }
}

int maximum(int alpha, int beta, int gamma)
{
  if(alpha >= beta)
  {
    if(alpha >= gamma)
    {
      return(alpha);
    }
    else
    {
      return(gamma);
    }
  }
  else
  {
    if(beta >= gamma)
    {
      return(beta);
    }
    else
    {
      return(gamma);
    }
  }
}

int is_a_triangle(int a, int b, int c)
{
  if(a+b > c)
  {
    return(1);
  }
  else
  {
    return(0);
  }
}

int kind_of_triangle(int a, int b, int c)
{
  if(a == b)
  {
    if(b == c)
    {
      return(EQUILATERAL);
    }
    else
    {
      return(ISOSCELES);
    }
  }
  else
  {
    if(b == c)
    {
      return(ISOSCELES);
    }
    else
    {
      return(SCALENE);
    }
  }
}

int is_right_angled(int a, int b, int c)
{
  if((a*a)+(b*b) == (c*c))
  {
    return(1);
  }
  else
  {
    return(0);
  }
}