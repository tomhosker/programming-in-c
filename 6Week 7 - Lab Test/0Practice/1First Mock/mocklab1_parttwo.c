#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 21
#define MAX_DIGIT_PLUS_ONE 10

void fill_square(int array[N][N]);

void print_square(int array[N][N]);

void twiddle(int array[N][N]);

int main(void)
{
  int square[N][N];
  int count;
  
  srand(time(NULL));
  
  fill_square(square);
  while(count < N*N*N*N)
  {
    twiddle(square);
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

int distance_from_centre(int x, int y)
{
  int distance;
  distance = ((x-(N/2))*(x-(N/2)))+((y-(N/2))*(y-(N/2)));
  return(distance);
}

void twiddle(int array[N][N])
{
  int x, y, u, v, a, b;
  
  x = rand()%N;
  y = rand()%N;
  u = rand()%N;
  v = rand()%N;
  
  a = array[y][x];
  b = array[v][u];
  
  if(distance_from_centre(x, y) < distance_from_centre(u, v))
  {
    if(a > b)
    {
      array[y][x] = b;
      array[v][u] = a;
    }
  }
  else
  {
    if(a < b)
    {
      array[y][x] = b;
      array[v][u] = a;
    }
  }
}