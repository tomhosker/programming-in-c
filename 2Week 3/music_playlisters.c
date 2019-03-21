#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shuffle(int *array, int n);

void print_song_list(int songs);

int main(void)
{
  srand(time(NULL));
  int songs = 1;
  
  while(songs != EOF)
  {
    printf("How many songs are required?");
    
    if((scanf("%d", &songs) == 1) && (songs > 0))
    {
      print_song_list(songs);
      printf("\n");
    }
    else
    {
      printf("You were supposed to enter a positive integer! Try again.");
      return(0);
    }
  }
  return(0);
}

void shuffle(int *array, int n)
{
  if (n > 1) 
  {
    int i;
    for(i = 0; i < n-1; i++) 
    {
      int j = i+(rand()/(RAND_MAX/(n-i)+1));
      int t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
  }
}

void print_song_list(int songs)
{
  int song_list[songs];
  
  for(int i = 0; i < songs; i++)
  {
    song_list[i] = i+1;
  }
  
  shuffle(song_list, songs);
  
  for(int j = 0; j < songs; j++)
  {
    printf("%d ", song_list[j]);
  }
}