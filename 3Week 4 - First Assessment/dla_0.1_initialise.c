#include <stdio.h>

#define ROW_SIZE 50

void initialise(char *array);

void print_grid(char *array);

int main(void)
{
  char grid[ROW_SIZE*ROW_SIZE];
  initialise(grid);
  print_grid(grid);
  return(0);
}

void initialise(char *array)
{
  for(int i = 0; i < (ROW_SIZE*ROW_SIZE); i++)
  {
    if(i == ((ROW_SIZE/2)*50)+(ROW_SIZE/2))
    {
      *array++ = '#';
    }
    else
    {
      *array++ = ' ';
    }
  }
}

void print_grid(char *array)
{
  printf("|");
  for(int i = 0; i < (ROW_SIZE*ROW_SIZE); i++)
  {
    if((i+1)%ROW_SIZE == 0)
    {
      if(i == (ROW_SIZE*ROW_SIZE)-1)
      {
        printf("%c|", *(array+i));
      }
      else
      {
        printf("%c|\n|", *(array+i));
      }
    }
    else
    {
      printf("%c.", *(array+i));
    }
  }
}