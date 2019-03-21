#include <stdio.h>
#include <stdlib.h>

#define BOARD_HEIGHT 8
#define BOARD_WIDTH 7

struct step{
  char board_at_step[BOARD_HEIGHT][BOARD_WIDTH];
  struct step *previous;
};
typedef struct step Step;

void initialise(char array[BOARD_HEIGHT][BOARD_WIDTH]);

void print_board(char array[BOARD_HEIGHT][BOARD_WIDTH]);

void board_copy(char array_1[BOARD_HEIGHT][BOARD_WIDTH], char array_2[BOARD_HEIGHT][BOARD_WIDTH]);

Step *allocate_step(char array[BOARD_HEIGHT][BOARD_WIDTH]);

int is_movable_up(char array[BOARD_HEIGHT][BOARD_WIDTH], int i, int j);

int is_movable_right(char array[BOARD_HEIGHT][BOARD_WIDTH], int i, int j);

int is_movable_left(char array[BOARD_HEIGHT][BOARD_WIDTH], int i, int j);

char *move_up(char array[BOARD_HEIGHT][BOARD_WIDTH], int i, int j);

char *move_right(char array[BOARD_HEIGHT][BOARD_WIDTH], int i, int j);

char *move_left(char array[BOARD_HEIGHT][BOARD_WIDTH], int i, int j);

int main(void)
{
  char board[BOARD_HEIGHT][BOARD_WIDTH];
  
  initialise(board);
  
  print_board(board);
  
  return(0);
}

void initialise(char array[BOARD_HEIGHT][BOARD_WIDTH])
{
  int i, j;
  
  for(i = 0; i < (BOARD_HEIGHT/2); i++)
  {
    for(j = 0; j < BOARD_WIDTH; j++)
    {
      array[i][j] = ' ';
    }
  }
  
  for(i = (BOARD_HEIGHT/2); i < BOARD_HEIGHT; i++)
  {
    for(j = 0; j < BOARD_WIDTH; j++)
    {
      array[i][j] = '#';
    }
  }
}

void print_board(char array[BOARD_HEIGHT][BOARD_WIDTH])
{
  int i, j;
  
  printf("|");
  for(i = 0; i < (BOARD_WIDTH*2)-1; i++)
  {
    printf("|");
  }
  printf("|\n");
  
  for(i = 0; i < BOARD_HEIGHT; i++)
  {
    printf("|");
    for(j = 0; j < BOARD_WIDTH-1; j++)
    {
      printf("%c.", array[i][j]);
    }
    printf("%c|\n", array[i][BOARD_WIDTH-1]);
  }
  
  printf("|");
  for(i = 0; i < (BOARD_WIDTH*2)-1; i++)
  {
    printf("|");
  }
  printf("|\n");
}

void board_copy(char array_1[BOARD_HEIGHT][BOARD_WIDTH], char array_2[BOARD_HEIGHT][BOARD_WIDTH])
{
  int i, j;
  
  for(i = 0; i < BOARD_HEIGHT; i++)
  {
    for(j = 0; j <BOARD_WIDTH; j++)
    {
      array_2[i][j] = array_1[i][j];
    }
  }
}

Step *allocate_step(char array[BOARD_HEIGHT][BOARD_WIDTH])
{
  Step *p;
  
  p = (Step *)malloc(sizeof(Step));
  if(p == NULL)
  {
    printf("Cannot allocate node\n");
    exit(2);
  }
  board_copy(array, p->board_at_step);
  p->previous = NULL;
  
  return(p);
}

int is_movable_up(char array[BOARD_HEIGHT][BOARD_WIDTH], int i, int j)
{
  if(array[i][j] != '#')
  {
    return(0);
  }
  
  if(i > 1)
  {
    if((array[i-1][j] == '#') && (array[i-2][j] == ' '))
    {
      return(1);
    }
  }
  return(0);
}

int is_movable_right(char array[BOARD_HEIGHT][BOARD_WIDTH], int i, int j)
{
  if(array[i][j] != '#')
  {
    return(0);
  }
  
  if(j < BOARD_WIDTH-2)
  {
    if((array[i][j+1] == '#') && (array[i][j+2] == ' '))
    {
      return(1);
    }
  }
  return(0);
}

int is_movable_left(char array[BOARD_HEIGHT][BOARD_WIDTH], int i, int j)
{
  if(array[i][j] != '#')
  {
    return(0);
  }
  
  if(j > 1)
  {
    if((array[i][j-1] == '#') && (array[i][j-2] == ' '))
    {
      return(1);
    }
  }
  return(0);
}

char *move_up(char array[BOARD_HEIGHT][BOARD_WIDTH], int i, int j)
{
  static char new_array[BOARD_HEIGHT][BOARD_WIDTH];
  
  board_copy(array, new_array);
  new_array[i][j] = ' ';
  new_array[i-1][j] = ' ';
  new_array[i-2][j] = '#';
  
  return(new_array);
}

char *move_right(char array[BOARD_HEIGHT][BOARD_WIDTH], int i, int j)
{
  static char new_array[BOARD_HEIGHT][BOARD_WIDTH];
  
  board_copy(array, new_array);
  new_array[i][j] = ' ';
  new_array[i][j+1] = ' ';
  new_array[i][j+2] = '#';
  
  return(new_array);
}

char *move_left(char array[BOARD_HEIGHT][BOARD_WIDTH], int i, int j)
{
  static char new_array[BOARD_HEIGHT][BOARD_WIDTH];
  
  board_copy(array, new_array);
  new_array[i][j] = ' ';
  new_array[i][j-1] = ' ';
  new_array[i][j-2] = '#';
  
  return(new_array);
}