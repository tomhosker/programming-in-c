#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW_SIZE 5

void initialise(char array[ROW_SIZE][ROW_SIZE]);

void print_grid(char array[ROW_SIZE][ROW_SIZE]);

int fill(int x, int y, int n, char array[ROW_SIZE][ROW_SIZE]);

int main(void)
{
  char grid[ROW_SIZE][ROW_SIZE];
  
  initialise(grid);
  print_grid(grid);
  printf("\n");
  
  fill(1, 1, 1, grid);
  printf("\n");
  print_grid(grid);
  
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

int fill(int x, int y, int n, char array[ROW_SIZE][ROW_SIZE])
{
  array[y][x] = n+'0';
  if(array[y+1][x] == '.')
  {
    fill(x, y+1, n+1, array);
  }
  else if(array[y][x+1] == '.')
  {
    fill(x+1, y, n+1, array);
  }
  else if(array[y-1][x] == '.')
  {
    fill(x, y-1, n+1, array);
  }
  else if(array[y][x-1] == '.')
  {
    fill(x-1, y, n+1, array);
  }
  else
  {
    return(0);
  }
}