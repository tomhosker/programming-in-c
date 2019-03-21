#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW_SIZE 5

void initialise(char array[ROW_SIZE][ROW_SIZE]);

void print_grid(char array[ROW_SIZE][ROW_SIZE]);

void top_left(char array[ROW_SIZE][ROW_SIZE]);

int main(void)
{
  char grid[ROW_SIZE][ROW_SIZE];
  
  initialise(grid);
  top_left(grid);
  print_grid(grid);
  printf("\n");
  
  explore(3, 3, grid);
  
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

void top_left(char array[ROW_SIZE][ROW_SIZE])
{
  array[1][1] = 'X';
}

int explore(int x, int y, char array[ROW_SIZE][ROW_SIZE])
{
  if(array[y][x] == 'X')
  {
    return(1);
  }
  else
  {
    printf("(%d,%d) ", x, y);
    array[y][x] = 'o';
    if(array[y+1][x] == '.')
    {
      explore(x, y+1, array);
    }
    else if(array[y][x+1] == '.')
    {
      explore(x+1, y, array);
    }
    else if(array[y-1][x] == '.')
    {
      explore(x, y-1, array);
    }
    else if(array[y][x-1] == '.')
    {
      explore(x-1, y, array);
    }
    else
    {
      return(0);
    }
  }
}