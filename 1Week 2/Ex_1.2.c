#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_RANDOM_NUMBER 1000


int main(void)
{
  srand (time(NULL));
  int random_number = rand()%MAX_RANDOM_NUMBER+1;
  int count = 0, guess;
  
  printf("You have ten chances and guessing the number I'm thinking of. It's between 1 and %d. I'll tell you if you're too low (Higher!) or too high (Lower!).\n\n", MAX_RANDOM_NUMBER);
  
  while(count < 10)
  {
    printf("What number am I thinking of?");
    scanf("%d", &guess);
    
    if(guess < random_number)
    {
      printf("Higher!\n\n");
    }
    else
    {
      if(guess == random_number)
      {
        printf("Correct! You won!");
        return(0);
      }
      else
      {
        printf("Lower!\n\n");
      }
    }
    
    count = count+1;
  }
  
  printf("Ha! You lost, moron!");
  return(0);
}