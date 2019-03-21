#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 15
#define MAX_DIGIT_PLUS_ONE 200

void fill_list(int array[N]);

void print_list(int array[N]);

int check_for_repeats(int array[N]);

int main(void)
{
  int list[N];
  int count = 0;
  
  srand(time(NULL));
  
  while(count < 1000)
  {
    fill_list(list);
    print_list(list);
    if(check_for_repeats(list) == -1)
    {
      printf("\n");
    }
    else
    {
      printf("  (%d appears 2 times)\n", check_for_repeats(list));
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
    printf("%d ", array[i]);
  }
}

int check_for_repeats(int array[N])
{
  int count = 0;
  int i, j, repeated;

  for(i = 0; i < N-1; i++)
  {
    for(j = 1; i+j < N; j++)
    {
      if(array[i+j] == array[i])
      {
        repeated = array[i];
        count++;
      }
    }
  }
  
  if(count == 0)
  {
    return(-1);
  }
  else
  {
    return(repeated);
  }
}
