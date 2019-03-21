#include <stdio.h>
#include <stdlib.h>

#define BOARD_HEIGHT 8
#define BOARD_WIDTH 7

struct step{
  char board[BOARD_HEIGHT][BOARD_WIDTH];
  struct step *previous_move;
  struct step *next;
};
typedef struct step Step;

void initialise(char array[BOARD_HEIGHT][BOARD_WIDTH]);

void print_board(char array[BOARD_HEIGHT][BOARD_WIDTH]);

void board_copy(char array_1[BOARD_HEIGHT][BOARD_WIDTH], char array_2[BOARD_HEIGHT][BOARD_WIDTH]);

int board_compare(char array_1[BOARD_HEIGHT][BOARD_WIDTH], char array_2[BOARD_HEIGHT][BOARD_WIDTH]);

Step *allocate_step(char array[BOARD_HEIGHT][BOARD_WIDTH]);

int is_movable_up(char array[BOARD_HEIGHT][BOARD_WIDTH], int i, int j);

int is_movable_right(char array[BOARD_HEIGHT][BOARD_WIDTH], int i, int j);

int is_movable_left(char array[BOARD_HEIGHT][BOARD_WIDTH], int i, int j);

char *move_up(char array[BOARD_HEIGHT][BOARD_WIDTH], int i, int j);

char *move_right(char array[BOARD_HEIGHT][BOARD_WIDTH], int i, int j);

char *move_left(char array[BOARD_HEIGHT][BOARD_WIDTH], int i, int j);

Step *search_tree(Step *s, char array[BOARD_HEIGHT][BOARD_WIDTH]);

void insert_step(Step *s);

Step *moves_from(Step *s, int i, int j, Step *base);

void make_tree(Step *s, Step *base);

int main(void)
{
  char board0[BOARD_HEIGHT][BOARD_WIDTH];
  Step *s0;
  Step *base0;
  
  initialise(board0);
  s0 = allocate_step(board0);
  base0 = allocate_step(board0);
  
  make_tree(s0, base0);
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

int board_compare(char array_1[BOARD_HEIGHT][BOARD_WIDTH], char array_2[BOARD_HEIGHT][BOARD_WIDTH])
{
  int i, j;
  
  for(i = 0; i < BOARD_HEIGHT; i++)
  {
    for(j = 0; j <BOARD_WIDTH; j++)
    {
      if(array_1[i][j] != array_2[i][j])
      {
        return(0);
      }
    }
  }
  return(1);
}

Step *allocate_step(char array[BOARD_HEIGHT][BOARD_WIDTH])
{
  Step *s;
  
  s = (Step *)malloc(sizeof(Step));
  if(s == NULL)
  {
    printf("Cannot allocate step.\n");
    exit(2);
  }
  board_copy(array, s->board);
  s->previous_move = NULL;
  s->next = NULL;
  
  return(s);
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

Step *search_tree(Step *s, char array[BOARD_HEIGHT][BOARD_WIDTH])
{
  int i, j;
  
  while(!((s->next == NULL) && (board_compare(s->board, array) == 0)))
  {
    if(board_compare(s->board, array) == 1)
    {
      return(s);
    }
    else
    {
      s = s->next;
    }
  }
  return(NULL);
}

void insert_step(Step *s)
{
  static Step *previous = NULL;
  
  if(previous != NULL)
  {
    previous->next = s;
  }
  
  previous = s;
}

Step *moves_from(Step *s, int i, int j, Step *base)
{
  Step *t;

  if(is_movable_up(s->board, i, j) == 1)
  {
    if(search_tree(move_up(s->board, i, j), base) == NULL)
    {
      t = allocate_step(move_up(s->board, i, j));
      insert_step(t);
      t->previous_move = s;
      return(t);
    }
  }
  
  if(is_movable_right(s->board, i, j) == 1)
  {
    if(search_tree(move_right(s->board, i, j), base) == NULL)
    {
      t = allocate_step(move_right(s->board, i, j));
      insert_step(t);
      t->previous_move = s;
      return(t);
    }
  }
  
  if(is_movable_left(s->board, i, j) == 1)
  {
    if(search_tree(move_left(s->board, i, j), base) == NULL)
    {
      t = allocate_step(move_left(s->board, i, j));
      insert_step(t);
      t->previous_move = s;
      return(t);
    }
  }
  
  return(NULL);
}

void make_tree(Step *s, Step *base)
{
  print_board(s);
  int i, j;
  
  for(i = 0; i < BOARD_HEIGHT; i++)
  {
    for(j = 0; j < BOARD_WIDTH; j++)
    {
      if(moves_from(s, i, j, base) != NULL)
      {
        make_tree(moves_from(s, i, j, base), base);
      }
    }
  }
}