#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 20
#define MAX_COUNT 500000

int *make_triple(int *array, int i);

int assess(int *array);

int *swap_two(int *array);

void print_board(int *array);

void array_copy(int *array, int *new_array);

int make_devilish(int *array);

int main(void)
{
  int board[BOARD_SIZE] = {20, 1, 18, 4, 13, 6, 10, 15, 2, 17, 3, 19, 7, 16, 8, 11, 14, 9, 12, 5};
  
  srand(time(NULL));
  
  make_devilish(board);
  
  return(0);
}

int *make_triple(int *array, int i)
{
  static int triple[3];
  int *p = triple;
  
  if(i == 0)
  {
    *p++ = *(array+BOARD_SIZE-1);
  }
  else
  {
    *p++ = *(array+i-1);
  }
  
  *p++ = *(array+i);
  
  if(i == BOARD_SIZE-1)
  {
    *p = *array;
  }
  else
  {
    *p = *(array+i+1);
  }
  
  return(triple);
}

int assess(int *array)
{
  int result = 0;
  int j;
  int square;
  
  for(j = 0; j < BOARD_SIZE; j++)
  {
    square = 0;
    square = square+*(make_triple(array,j));
    square = square+*(make_triple(array,j)+1);
    square = square+*(make_triple(array,j)+2);
    result = result+(square*square);
  }
  return(result);
}

int *swap_two(int *array)
{
  static int new_array[BOARD_SIZE];
  int *p = new_array;
  int random_a = rand()%BOARD_SIZE;
  int random_b = rand()%BOARD_SIZE;
  int j;
  
  for(j = 0; j < BOARD_SIZE; j++)
  {
    *(p+j) = *(array+j);
  }
  
  *(p+random_a) = *(array+random_b);
  *(p+random_b) = *(array+random_a);
  
  return(new_array);
}

void print_board(int *array)
{
  int i;
  for(i = 0; i < BOARD_SIZE; i++)
  {
    printf("%d ", *(array+i));
  }
  printf("\n");
}

void array_copy(int *array, int *new_array)
{
  int i;
  for(i = 0; i < BOARD_SIZE; i++)
  {
    *(new_array+i) = *(array+i);
  }
}

int make_devilish(int *array)
{
  int count = 1;
  int swapped_array[BOARD_SIZE];
  
  while(count < MAX_COUNT)
  {
    array_copy(swap_two(array), swapped_array);
    if(assess(swapped_array) < assess(array))
    {
      printf("%d\n", assess(array));
      array_copy(swapped_array, array);
    }
    count++;
  }
  printf("Max count reached. ");
  printf("Board difficulty: %d.\n", assess(array));
  printf("Board: ");
  print_board(array);
}