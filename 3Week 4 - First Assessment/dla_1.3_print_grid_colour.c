/*##########################################################
############################################################
###################### A Program in C ######################
####################### to Simulate ########################
#################### Diffusion Limited #####################
####################### Aggregation ########################
########################## v 1.3 ###########################
############################################################
###################### by TOM HOSKER #######################
############################################################
####################### 19 Oct 2017 ########################
############################################################
############# nisi Dominus aedificaverit domum #############
############################################################
############################################################
############### Znl gur fbhy bs Qnivq Pbbx, ################
################### Puvrs Bssvpre Eblny ####################
################# Syrrg Nhkvyvnel Freivpr, #################
##################### jevgur va ntbal ######################
################## orgjrra Fngna'f grrgu. ##################
############################################################
##########################################################*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "neillncurses.h"

#define ROW_SIZE 50
#define TRUE 1
#define FALSE 0
#define CRYSTAL_SIZE 250
#define GRID_SIZE 2500

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
/* Checks the cells adjacent to p for a #. */

void run_p(char *array);
/* Moves the particle around until it hits a #. */

void run_simulation(char *array);
/* Runs run_p until there are CRYSTAL_SIZE #s. */

void print_grid_colour(char *array);
/* Prints the grid in colour. */

int main(void)
{
  char grid[GRID_SIZE];

  srand(time(NULL));
  
  initialise(grid);
  run_simulation(grid);
  print_grid_colour(grid);
  
  return(0);
}

void initialise(char *array)
{
  int i, j;
  for(i = 0; i < ROW_SIZE; i++)
  {
    for(j = 0; j < ROW_SIZE; j++)
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
  int i, j;
  for(i = 0; i < ROW_SIZE; i++)
  {
    printf("|");
    for(j = 0; j < ROW_SIZE; j++)
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
  int i, j;
  for(i = 0; i < ROW_SIZE; i++)
  {
    for(j = 0; j < ROW_SIZE; j++)
    {
      if(*(array+(i*ROW_SIZE)+j) == 'p')
      {
        return((i*ROW_SIZE)+j);
      }
    }
  }
  return(0);
}

int find_q(char *array)
{
int i, j;
  for(i = 0; i < ROW_SIZE; i++)
  {
    for(j = 0; j < ROW_SIZE; j++)
    {
      if(*(array+(i*ROW_SIZE)+j) == 'q')
      {
        return((i*ROW_SIZE)+j);
      }
    }
  }
  return(0);
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
  if(find_p(array) < ROW_SIZE)
  {
    if(*(array+find_p(array)+((ROW_SIZE-1)*ROW_SIZE)) == '#')
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
  if((find_p(array)%ROW_SIZE) == ROW_SIZE-1)
  {
    if(*(array+find_p(array)-ROW_SIZE+1) == '#')
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
  if(find_p(array) >= ((ROW_SIZE-1)*ROW_SIZE))
  {
    if(*(array+find_p(array)-((ROW_SIZE-1)*ROW_SIZE)) == '#')
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
  if((find_p(array)%ROW_SIZE) == 0)
  {
    if(*(array+find_p(array)+ROW_SIZE-1) == '#')
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

void run_p(char *array)
{
  generate_p(array);
  while(check(array) != TRUE)
  {
    next(array);
  }
  *(array+find_p(array)) = '#';
}

void run_simulation(char *array)
{
  int count = 1;
  while(count < (CRYSTAL_SIZE+1))
  {
    run_p(array);
    count++;
  }
}

void print_grid_colour(char *array)
{
  NCURS_Simplewin sw;
  
  Neill_NCURS_Init(&sw);
  /* For the character '#' use red foreground colour, red background. */
  Neill_NCURS_CharStyle(&sw, "#", COLOR_RED, COLOR_RED, A_NORMAL);
  /* For the character ' ' use black foreground colour, black background. */
  Neill_NCURS_CharStyle(&sw, " ", COLOR_BLACK, COLOR_BLACK, A_NORMAL);

  do{
    Neill_NCURS_PrintArray(&array[0], ROW_SIZE, ROW_SIZE, &sw);
    Neill_NCURS_Delay(500.0);
    Neill_NCURS_Events(&sw);
  }while(!sw.finished);

  /* Call this function if we exit() anywhere in the code. */
  atexit(Neill_NCURS_Done);

  exit(EXIT_SUCCESS);
}
