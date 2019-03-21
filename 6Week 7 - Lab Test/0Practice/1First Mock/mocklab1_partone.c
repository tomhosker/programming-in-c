#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 20
#define MAX_DIGIT_PLUS_ONE 10

void fill_square(int array[N][N]);

void print_square(int array[N][N]);

void twiddle_1(int array[N][N]);

void twiddle_2(int array[N][N]);

int main(void)
{
  int square[N][N];
  int count;
  
  srand(time(NULL));
  
  fill_square(square);
  while(count < N*N*N)
  {
    twiddle_1(square);
    twiddle_2(square);
    count++;
  }
  print_square(square);
  
  return(0);
}

void fill_square(int array[N][N])
{
  int i, j;
  
  for(i = 0; i < N; i++)
  {
    for(j = 0; j < N; j++)
    {
      array[i][j] = rand()%MAX_DIGIT_PLUS_ONE;
    }
  }
}

void print_square(int array[N][N])
{
  int i, j;
  
  for(i = 0; i < N; i++)
  {
    for(j = 0; j < N; j++)
    {
      printf("%d", array[i][j]);
    }
    printf("\n");
  }
}

void twiddle_1(int array[N][N])
{
  int x, y, a, b;
  
  x = rand()%(N-1);
  y = rand()%N;
  
  a = array[y][x];
  b = array[y][x+1];
  
  if(a > b)
  {
    array[y][x] = b;
    array[y][x+1] = a;
  }
}

void twiddle_2(int array[N][N])
{
  int x, y, a, b;
  
  x = rand()%N;
  y = rand()%(N-1);
  
  a = array[y][x];
  b = array[y+1][x];
  
  if(a > b)
  {
    array[y][x] = b;
    array[y+1][x] = a;
  }
}