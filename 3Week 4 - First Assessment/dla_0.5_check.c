#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW_SIZE 50
#define TRUE 1
#define FALSE 0

void initialise(char *array);
/* Initialises the grid. */

void print_grid(char *array);
/* Prints the grid. */

void generate_p(char *array);
/* Generates the moving particle. */

int find_p(char *array);
/* Gives the address of character p within array. */

int find_q(char *array);
/* Gives the address of character q within array. */

void next_up(char *array);
/* Sub-function of next. */

void next_right(char *array);
/* Sub-function of next. */

void next_down(char *array);
/* Sub-function of next. */

void next_left(char *array);
/* Sub-function of next. */

void next(char *array);
/* Randomly moves p by one. */

int check_up(char *array);
/* Sub-function of check. */

int check_right(char *array);
/* Sub-function of check. */

int check_down(char *array);
/* Sub-function of check. */

int check_left(char *array);
/* Sub-function of check. */

int check(char *array);
/* Sub-function of check. */

int main(void)
{
  srand(time(NULL));
  char grid[ROW_SIZE*ROW_SIZE];
  initialise(grid);
  generate_p(grid);
  printf("%d", check(grid));
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

int find_p(char *array)
{
  for(int i = 0; i < ROW_SIZE; i++)
  {
    for(int j = 0; j < ROW_SIZE; j++)
    {
      if(*(array+(i*ROW_SIZE)+j) == 'p')
      {
        return((i*ROW_SIZE)+j);
      }
    }
  }
}

int find_q(char *array)
{
  for(int i = 0; i < ROW_SIZE; i++)
  {
    for(int j = 0; j < ROW_SIZE; j++)
    {
      if(*(array+(i*ROW_SIZE)+j) == 'q')
      {
        return((i*ROW_SIZE)+j);
      }
    }
  }
}

void next_up(char *array)
{
  if(find_p(array) > ROW_SIZE-1)
  {
    *(array+find_p(array)-ROW_SIZE) = 'q';
    *(array+find_p(array)) = ' ';
    *(array+find_q(array)) = 'p';
  }
  else
  {
    *(array+find_p(array)+((ROW_SIZE-1)*ROW_SIZE)) = 'q';
    *(array+find_p(array)) = ' ';
    *(array+find_q(array)) = 'p';
  }
}

void next_right(char *array)
{
  if(find_p(array)%ROW_SIZE != ROW_SIZE-1)
  {
    *(array+find_p(array)+1) = 'q';
    *(array+find_p(array)) = ' ';
    *(array+find_q(array)) = 'p';
  }
  else
  {
    *(array+find_p(array)-ROW_SIZE+1) = 'q';
    *(array+find_p(array)) = ' ';
    *(array+find_q(array)) = 'p';
  }
}

void next_down(char *array)
{
  if(find_p(array) < (ROW_SIZE-1)*ROW_SIZE)
  {
    *(array+find_p(array)+ROW_SIZE) = 'q';
    *(array+find_p(array)) = ' ';
    *(array+find_q(array)) = 'p';
  }
  else
  {
    *(array+find_p(array)-((ROW_SIZE-1)*ROW_SIZE)) = 'q';
    *(array+find_p(array)) = ' ';
    *(array+find_q(array)) = 'p';
  }
}

void next_left(char *array)
{
  if(find_p(array)%ROW_SIZE != 0)
  {
    *(array+find_p(array)-1) = 'q';
    *(array+find_p(array)) = ' ';
    *(array+find_q(array)) = 'p';
  }
  else
  {
    *(array+find_p(array)+ROW_SIZE-1) = 'q';
    *(array+find_p(array)) = ' ';
    *(array+find_q(array)) = 'p';
  }
}

void next(char *array)
{
  int random_n = rand()%4;
  if(random_n == 0)
  {
    next_up(array);
  }
  else if(random_n == 1)
  {
    next_right(array);
  }
  else if(random_n == 2)
  {
    next_down(array);
  }
  else
  {
    next_left(array);
  }
}

int check_up(char *array)
{
  if(find_p(array) > ROW_SIZE-1)
  {
    if(*(array+find_p(array)-ROW_SIZE) == '#')
    {
      return(TRUE);
    }
  }
  return(FALSE);
}

int check_right(char *array)
{
  if((find_p(array)%ROW_SIZE) != ROW_SIZE-1)
  {
    if(*(array+find_p(array)+1) == '#')
    {
      return(TRUE);
    }
  }
  return(FALSE);
}

int check_down(char *array)
{
  if(find_p(array) < ((ROW_SIZE-1)*ROW_SIZE))
  {
    if(*(array+find_p(array)+ROW_SIZE) == '#')
    {
      return(TRUE);
    }
  }
  return(FALSE);
}

int check_left(char *array)
{
  if((find_p(array)%ROW_SIZE) != 0)
  {
    if(*(array+find_p(array)-1) == '#')
    {
      return(TRUE);
    }
  }
  return(FALSE);
}

int check(char *array)
{
  if(check_up(array) == TRUE)
  {
    return(TRUE);
  }
  else if(check_right(array) == TRUE)
  {
    return(TRUE);
  }
  else if(check_down(array) == TRUE)
  {
    return(TRUE);
  }
  else if(check_left(array) == TRUE)
  {
    return(TRUE);
  }
  else
  {
    return(FALSE);
  }
}