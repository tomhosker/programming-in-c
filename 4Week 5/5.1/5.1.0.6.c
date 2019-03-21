#include <stdio.h>
#include <stdlib.h>

#define ROW_SIZE 5

void initialise(char array[ROW_SIZE][ROW_SIZE]);

void print_grid(char array[ROW_SIZE][ROW_SIZE]);

void makepaths(int length, int current, int x, int y, char array[ROW_SIZE][ROW_SIZE]);

int main(void)
{
  char grid[ROW_SIZE][ROW_SIZE];
  
  initialise(grid);
  print_grid(grid);
  printf("\n");
  
  makepaths(9, 1, 1, 1, grid);
  
  return(0);
}

void initialise(char array[ROW_SIZE][ROW_SIZE])
{
  int i,j;
  for(i = 0; i < ROW_SIZE; i++)
  {
    for(j = 0; j < ROW_SIZE; j++)
    {
      if(i == 0 || i == ROW_SIZE-1)
      {
        array[i][j] = '#';
      }
      else if(j == 0 || j == ROW_SIZE-1)
      {
        array[i][j] = '#';
      }
      else
      {
        array[i][j] = '.';
      }
    }
  }
}

void print_grid(char array[ROW_SIZE][ROW_SIZE])
{
  int i,j;
  for(i = 0; i < ROW_SIZE; i++)
  {
    for(j = 0; j < ROW_SIZE; j++)
    {
      printf("%c", array[i][j]);
    }
    printf("\n");
  }
}

void makepaths(int length, int current, int x, int y, char array[ROW_SIZE][ROW_SIZE])
{
  array[y][x] = current+'0';

  if(length == 1) /* if we have to make a path of length 1, then it is just the given point.  This is the termination condition for the recursion */
  {
    print_grid(array);
    printf("\n");
  }
  else
  {
    if(array[y][x+1] == '.')
    {
      makepaths(length-1, current+1, x+1, y, array); /* this will make all paths of length-1 starting from our new position (x+1,y) with label current+1 */
    }
    if(array[y][x-1] == '.')
    {
      makepaths(length-1, current+1, x-1, y, array);
    }
    if(array[y+1][x] == '.')
    {
      makepaths(length-1, current+1, x, y+1, array);
    }
    if(array[y-1][x] == '.')
    {
      makepaths(length-1, current+1, x, y-1, array);
    }
  }

  array[y][x] = '.';
}