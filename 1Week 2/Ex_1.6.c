#include <stdio.h>

#define MAX_START 50000

long next(long n);

long hailstone_length(long n);

long hailstone_max(long n);

long longest_seq(long n);

long largest_seq(long n);

int main(void)
{
  printf("The starting value, less than %d, which produces the largest value is %d.\n", MAX_START, largest_seq(MAX_START));
  printf("The starting value, less than %d, which produces the longest sequence is %d.\n", MAX_START, longest_seq(MAX_START));
  return(0);
}

long next(long n)
{
  if(n%2 == 0)
  {
    return(n/2);
  }
  else
  {
    return((3*n)+1);
  }
}

long hailstone_length(long n)
{
  long count = 1;
  while(n != 1)
  {
    n = next(n);
    count++;
  }
  return(count);
}

long hailstone_max(long n)
{
  long max = n;
  while(n != 1)
  {
    n = next(n);
    if(n > max)
    {
      max = n;
    }
  }
  return(max);
}

long longest_seq(long n)
{
  long max = 1;
  long m = 1;
  for(long i = 1; i < n; i++)
  {
    if(hailstone_length(i) > max)
    {
      max = hailstone_length(i);
      m = i;
    }
  }
  return(m);
}

long largest_seq(long n)
{
  long max = 1;
  long m = 1;
  for(long i = 1; i < n; i++)
  {
    if(hailstone_max(i) > max)
    {
      max = hailstone_max(i);
      m = i;
    }
  }
  return(m);
}