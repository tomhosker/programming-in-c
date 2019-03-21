#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW_SIZE 3
#define GRID_SIZE 9

void initialise(int *array);

void print_grid(int *array);

void top_left(int *array);

int highest(int *array);

int find_highest(int *array);

void *right(int *array);

void *left(int *array);

void *down(int *array);

void *up(int *array);

int main(void)
{
  int grid[GRID_SIZE];
  
  srand(time(NULL));
  
  initialise(grid);
  top_left(grid);
  print_grid(grid);
  printf("\n");
  
  right(grid);
  down(grid);
  down(grid);
  left(grid);
  up(grid);
  print_grid(grid);
  
  return(0);
}

void initialise(int *array)
{
  int i;
  for(i = 0; i < GRID_SIZE; i++)
  {
    *(array+i) = 0;
  }
}

void print_grid(int *array)
{
  int i;
  for(i = 0; i < GRID_SIZE; i++)
  {
    if((i+1)%ROW_SIZE == 0)
    {
      if(*(array+i) =='#')
      {
        printf("\n");
      }
      else
      {
        printf("%d\n", *(array+i));
      }
    }
    else
    {
      printf("%d", *(array+i));
    }
  }
}

void top_left(int *array)
{
  *array = 1;
}

int highest(int *array)
{
  int highest = 0;
  
  int i;
  for(i = 0; i < GRID_SIZE; i++)
  {
    if(*(array+i) > highest)
    {
      highest = *(array+i);
    }
  }
  
  return(highest);
}

int find_highest(int *array)
{
  int highest = 0;
  int highest_coord = 0;
  
  int i;
  for(i = 0; i < GRID_SIZE; i++)
  {
    if(*(array+i) > highest)
    {
      highest = *(array+i);
      highest_coord = i;
    }
  }
  
  return(highest_coord);
}

void *right(int *array)
{
  *(array+find_highest(array)+1) = highest(array)+1;
}

void *left(int *array)
{
  *(array+find_highest(array)-1) = highest(array)+1;
}

void *down(int *array)
{
  *(array+find_highest(array)+ROW_SIZE) = highest(array)+1;
}

void *up(int *array)
{
  *(array+find_highest(array)-ROW_SIZE) = highest(array)+1;
}