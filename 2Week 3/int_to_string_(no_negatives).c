#include <stdio.h>
#include <math.h>

int width(int n);

int shrink_left(int n, int i);

int shrink_right(int n, int i);

int digit(int n, int i);

char *int2string(int i);

int main(void)
{
  int i;
  
  while(i != EOF)
  {
    printf("Type in a number:");
    if(scanf("%d", &i) == 1)
    {
      printf("%s\n\n", int2string(i));
    }
    else
    {
      printf("You should have typed an integer! Try again.");
    }
  }
  
  return(0);
}

int width(int n)
{
  int i = 0;
  while(pow(10,i) < n)
  {
    i++;
  }
  return(i);
}

int shrink_left(int n, int i)
{
  if(i == 0 || i == 1)
  {
    if(i == 0)
    {
      return(n);
    }
    else
    {
      return(n%(int)(pow(10,width(n)-1)));  
    }
  }
  else
  {
    return(shrink_left(shrink_left(n,i-1), 1));
  }
}

int shrink_right(int n, int i)
{
  return(floor(n/pow(10,i)));
}

int digit(int n, int i)
{
  if(n < 0)
  {
    n = n*(-1);
  }
  
  int shrunk_right = shrink_right(n, width(n)-1-i);
  int shrunk_twice = shrink_left(shrunk_right, i);
  return(shrunk_twice);
}

char *int2string(int i)
{
  static char new_string[256];
  char *p = new_string;
  
  int j = 0;
  while(j < width(i))
  {
    *(p+j) = digit(i,j)+'0';
    j++;
  }
  
  return(new_string);
}