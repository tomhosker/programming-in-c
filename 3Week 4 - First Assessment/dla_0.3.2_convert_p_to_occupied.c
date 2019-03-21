#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW_SIZE 50
#define TRUE 1
#define FALSE 0

void initialise(char *array); /* Initialises the grid. */

void print_grid(char *array); /* Prints the grid. */

void generate_p(char *array); /* Generates the moving particle. */

int check_up(char *array); /* Sub-function of check. */

int check_right(char *array); /* Sub-function of check. */

int check_down(char *array); /* Sub-function of check. */

int check_left(char *array); /* Sub-function of check. */

int check(char *array); /* Checks the cells adjacent to the moving particle for occupied cells. */

void convert_p_to_occupied(char *array); /* Converts the moving particle to an occupied cell. */

int main(void)
{
  srand(time(NULL));
  char grid[ROW_SIZE][ROW_SIZE];
  initialise(grid);
  generate_p(grid);
  convert_p_to_occupied(grid);
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
    *(array+random_b) = 'p';
  }
  else if(random_a == 1)
  {
    *(array+(ROW_SIZE-1)+(ROW_SIZE*random_b)) = 'p';
  }
  else if(random_a == 2)
  {
    *(array+random_b+(ROW_SIZE*(ROW_SIZE-1))) = 'p';
  }
  else
  {
    *(array+(ROW_SIZE*random_b)) = 'p';
  }
}

int check_up(char *array)
{
  for(int i = 0; i < ROW_SIZE; i++)
  {
    for(int j = 0; j < ROW_SIZE; j++)
    {
      if(*(array+i+j) == 'p')
      {
        if(i+j > ROW_SIZE-1)
        {
          if(*(array+i+j-ROW_SIZE) == '#')
          {
            return(TRUE);
          }
        }
      }
    }
  }
  return(FALSE);
}

int check_right(char *array)
{
  for(int i = 0; i < ROW_SIZE; i++)
  {
    for(int j = 0; j < ROW_SIZE; j++)
    {
      if(*(array+i+j) == 'p')
      {
        if((i+j)%ROW_SIZE != ROW_SIZE-1)
        {
          if(*(array+i+j+1) == '#')
          {
            return(TRUE);
          }
        }
      }
    }
  }
  return(FALSE);
}

int check_down(char *array)
{
  for(int i = 0; i < ROW_SIZE; i++)
  {
    for(int j = 0; j < ROW_SIZE; j++)
    {
      if(*(array+i+j) == 'p')
      {
        if((i+j) < ((ROW_SIZE-1)*ROW_SIZE))
        {
          if(*(array+i+j+ROW_SIZE) == '#')
          {
            return(TRUE);
          }
        }
      }
    }
  }
  return(FALSE);
}

int check_left(char *array)
{
  for(int i = 0; i < ROW_SIZE; i++)
  {
    for(int j = 0; j < ROW_SIZE; j++)
    {
      if(*(array+i+j) == 'p')
      {
        if((i+j)%ROW_SIZE != 0)
        {
          if(*(array+i+j-1) == '#')
          {
            return(TRUE);
          }
        }
      }
    }
  }
  return(FALSE);
}

int check(char *array)
{
  if(check_up(array) == 1)
  {
    return(1);
  }
  else if(check_right(array) == 1)
  {
    return(1);
  }
  else if(check_down(array) == 1)
  {
    return(1);
  }
  else if(check_left(array) == 1)
  {
    return(1);
  }
  else
  {
    return(0);
  }
}

void convert_p_to_occupied(char *array)
{
  for(int i = 0; i < ROW_SIZE; i++)
  {
    for(int j = 0; j < ROW_SIZE; j++)
    {
      if(*(array+i+j) == 'p')
      {
        *(array+i+j) = '#';
      }
    }
  }
}