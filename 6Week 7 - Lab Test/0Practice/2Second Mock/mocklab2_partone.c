#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 4
#define MAX_DIGIT_PLUS_ONE 10

void fill_list(int array[N]);

void print_list(int array[N]);

int check_for_ascending(int array[N]);

int main(void)
{
  int list[N];
  int count = 0;
  
  srand(time(NULL));
  
  while(count < 1000)
  {
    fill_list(list);
    print_list(list);
    if(check_for_ascending(list) == 0)
    {
      printf(" Not Ascending\n");
    }
    else
    {
      printf(" Ascending\n");
    }
    count++;
  }
  
  return(0);
}

void fill_list(int array[N])
{
  int i;
  
  for(i = 0; i < N; i++)
  {
    array[i] = rand()%MAX_DIGIT_PLUS_ONE;
  }
}

void print_list(int array[N])
{
  int i;
  
  for(i = 0; i < N; i++)
  {
    printf("%d", array[i]);
  }
}

int check_for_ascending(int array[N])
{
  int i;

  for(i = 0; i < N-1; i++)
  {
    if(array[i] > array[i+1])
    {
      return(0);
    }
  }
  return(1);
}
