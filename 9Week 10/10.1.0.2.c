#include <stdio.h>
#include <stdlib.h>

#define BOARD_HEIGHT 8
#define BOARD_WIDTH 7

struct step{
  char board_at_step[BOARD_HEIGHT][BOARD_WIDTH];
  struct step *previous;
};
typedef struct step Step;

struct node{
  char board_at_node[BOARD_HEIGHT][BOARD_WIDTH];
  struct node *next;
  struct Step *tree_pointer;
};
typedef struct node Node;

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

Step *add_step(char array[BOARD_HEIGHT][BOARD_WIDTH], Step *s, Node *n);

Node *allocate_node(Step *s);

Node *add_node(Step *s, Node *previous_node);

Step *search_tree(Node *n, char array[BOARD_HEIGHT][BOARD_WIDTH]);

void make_tree(char *array, Step *s, Node *n);

int main(void)
{
  char board[BOARD_HEIGHT][BOARD_WIDTH];
  Step *s_0;
  Node *n_0;
  
  initialise(board);
  s_0 = add_step(board, NULL, NULL);
  make_tree(board, NULL, n_0);
  
  print_board(n_0->next->next->board_at_node);
  
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
  Step *p;
  
  p = (Step *)malloc(sizeof(Step));
  if(p == NULL)
  {
    printf("Cannot allocate step.\n");
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

Step *add_step(char array[BOARD_HEIGHT][BOARD_WIDTH], Step *s, Node *n)
{
  Step *array_pointer;
  
  if(n != NULL)
  {
    if(search_tree(n, array) != NULL)
    {
      return(s);
    }
  }

  array_pointer = allocate_step(array);

  array_pointer->previous = s;
  
  return(array_pointer);
}

Node *allocate_node(Step *s)
{
  Node *n;
  
  n = (Node *)malloc(sizeof(Node));
  if(n == NULL)
  {
    printf("Cannot allocate node.\n");
    exit(2);
  }
  board_copy(s->board_at_step, n->board_at_node);
  n->next = NULL;
  n->tree_pointer = s;
  
  return(n);
}

Node *add_node(Step *s, Node *previous_node)
{
  static Node *previous_one;
  Node *n;
  
  n = allocate_node(s);
  
  if(previous_node != NULL)
  {
    previous_node->next = n;
  }
  
  return(n);
}

Step *search_tree(Node *n, char array[BOARD_HEIGHT][BOARD_WIDTH])
{
  int i, j;
  
  while((n->next != NULL) && (board_compare(n->board_at_node, array) != 0))
  {
    if(board_compare(n->board_at_node, array) == 1)
    {
      return(n);
    }
    else
    {
      n = n->next;
    }
  }
  return(NULL);
}

void make_tree(char *array, Step *s, Node *n)
{
  int i, j;
  
  s = add_step(array, s, n);
  n = add_node(s, n);
  
  for(i = 0; i < BOARD_HEIGHT; i++)
  {
    for(j = 0; j < BOARD_WIDTH; j++)
    {
      if(is_movable_up(array, i, j) == 1)
      {
        make_tree(move_up(array, i, j), s, n);
      }
      if(is_movable_right(array, i, j) == 1)
      {
        make_tree(move_right(array, i, j), s, n);
      }
      if(is_movable_left(array, i, j) == 1)
      {
        make_tree(move_right(array, i, j), s, n);
      }
    }
  }
}