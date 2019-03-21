#include <stdio.h>
#include <stdlib.h>

#define ROW_SIZE 50

void initialise(char *array);

void print_grid(char *array);

void generate_p(char *array);

int main(void)
{
  char grid[ROW_SIZE][ROW_SIZE];
  initialise(grid);
  generate_p(grid);
  print_grid(grid);
  return(0);
}

void initialise(char *array)
{
  for(int i = 0; i < ROW_SIZE; i++)
  {
    for(int j = 0; j < ROW_SIZE; j++)
    {
      if(i == ROW_SIZE/2 && j == ROW_SIZE/2)
      {
        *array++ = '#';
      }
      else
      {
        *array++ = ' ';
      }
    }
  }
}

void print_grid(char *array)
{
  for(int i = 0; i < ROW_SIZE; i++)
  {
    printf("|");
    for(int j = 0; j < ROW_SIZE; j++)
    {
      printf("%c.", *array++);
    }
    printf("|\n");
  }
}

void generate_p(char *array)
{
  int random_a = rand()%4;
  int random_b = rand()%ROW_SIZE;
  
  if(random_a == 0)
  {
    for(int i = 0; i < (ROW_SIZE*ROW_SIZE); i++)
    {
      if(i == random_b)
      {
        *array++ = 'p';
      }
    }
  }
  else if(random_a == 1)
  {
    for(int i = 0; i < (ROW_SIZE*ROW_SIZE); i++)
    {
      if(i == (ROW_SIZE-1)+(random_b*ROW_SIZE))
      {
        *array++ = 'p';
      }
      else
      {
        *array++ = *array;
      }
    }
  }
  else if(random_a == 2)
  {
    for(int i = 0; i < (ROW_SIZE*ROW_SIZE); i++)
    {
      if(i == (ROW_SIZE*(ROW_SIZE-1))+random_b)
      {
        *array++ = 'p';
      }
      else
      {
        *array++ = *array;
      }
    }
  }
  else
  {
    for(int i = 0; i < (ROW_SIZE*ROW_SIZE); i++)
    {
      if(i == random_b*ROW_SIZE)
      {
        *array++ = 'p';
      }
      else
      {
        *array++ = *array;
      }
    }
  }
}