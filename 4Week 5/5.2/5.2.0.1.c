#include <stdio.h>

#define BOARD_SIZE 20

int *make_triple(int *array, int i);

long long assess(int *array);

int main(void)
{
  int board[BOARD_SIZE] = {20, 1, 18, 4, 13, 6, 10, 15, 2, 17, 3, 19, 7, 16, 8, 11, 14, 9, 12, 5};
  
  printf("%d", assess(board));
  
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

long long assess(int *array)
{
  long long result = 0;
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