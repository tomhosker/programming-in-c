#include <stdio.h>

int kind_of_triangle(int a, int b, int c);

int maximum(int a, int b, int c);

int is_right_angled(int a, int b, int c);

int main(void)
{
  int a, b, c;
  
  printf("Type in the lengths of the sides of a triangle, in integer units, leaving the largest of the three to the end.");
  scanf("%d%d%d", &a, &b, &c);
  
  if(c >= a && c >= b)
  {
    if(kind_of_triangle(a, b, c) == 0)
    {
      printf("The triangle is scalene.\n");
    }
    if(kind_of_triangle(a, b, c) == 1)
    {
      printf("The triangle is isosceles.\n");
    }
    if(kind_of_triangle(a, b, c) == 2)
    {
      printf("The triangle is equilateral.\n");
    }
    if(is_right_angled(a, b, c) == 1)
    {
      printf("The triangle is right-angled.\n");
    }
    if(is_right_angled(a, b, c) == 0)
    {
      printf("The triangle is not right-angled.\n");
    }
  }
  else
  {
    printf("You were meant to leave the largest till last! Start again.\n");
  }
}

int kind_of_triangle(int a, int b, int c)
{
  if(a == b)
  {
    if(b == c)
    {
      return(2);
    }
    else
    {
      return(1);
    }
  }
  else
  {
    if(b == c)
    {
      return(1);
    }
    else
    {
      return(0);
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