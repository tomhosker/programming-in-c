#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW_SIZE 50

void initialise(char *array);

void print_grid(char *array);

void generate_p(char *array);

int main(void)
{
  srand(time(NULL));
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
    array[random_b] = 'p';
  }
  else if(random_a == 1)
  {
    array[(ROW_SIZE-1)+(ROW_SIZE*random_b)] = 'p';
  }
  else if(random_a == 2)
  {
    array[random_b+(ROW_SIZE*(ROW_SIZE-1))] = 'p';
  }
  else
  {
    array[ROW_SIZE*random_b] = 'p';
  }
}