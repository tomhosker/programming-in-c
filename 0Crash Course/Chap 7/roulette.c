#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STARTING_SUM 10
#define RED 1
#define BLACK 2

int cash = STARTING_SUM;

void rb_bet_or_numbered_bet(void);

void number_bet(void);

void red_or_black_bet(void);

int main(void)
{
  srand (time(NULL));
  printf("Cash: £%d\n\n", cash);
  
  while(cash > 0)
  {
    rb_bet_or_numbered_bet();
  }
  printf("Ha! You lost all your cash, moron!");
  
  return(0);
}

void rb_bet_or_numbered_bet()
{
  int choice;
  
  printf("Would you like to bet on a specific number, sir? (1)\n");
  printf("Or would you prefer to bet on red or black? (2)");
  
  scanf("%d", &choice);
  if(choice == 1 || choice == 2)
  {
    if(choice == 1)
    {
      printf("\n");
      number_bet();
    }
    else
    {
      printf("\n");
      red_or_black_bet();
    }
  }
  else
  {
    printf("Please choose one of the two options, sir.\n\n");
    rb_bet_or_numbered_bet();
  }
}

void number_bet(void)
{
  cash = cash-1;
  printf("Cash: £%d\n", cash);
  
  int number, result = rand()%36;
  
  printf("What number would you like to bet on, sir? (1 to 35)");
  scanf("%d", &number);
  
  if(number >= 1 && number <= 35)
  {
    printf("%d!\n", result);
    if(number == result)
    {
      cash = cash+36;
      printf("Well done, sir!\n");
      printf("Cash: £%d\n\n", cash);
    }
    else
    {
      printf("Bad luck, sir.\n");
      printf("Cash: £%d\n\n", cash);
    }
  }
  else
  {
    cash = cash+1;
    printf("Please choose a number between 1 and 35, sir.\n\n");
    number_bet();
  }
}

void red_or_black_bet(void)
{
  cash = cash-1;
  printf("Cash: £%d\n", cash);
  
  int rb, result = rand()%36;
  
  printf("Red or black, sir? (Type 1 for red, and 2 for black.)");
  scanf("%d", &rb);
  
  if(rb == RED || rb == BLACK)
  {
    printf("%d!\n", result);
    if(result%2 == rb%2 && result != 0)
    {
      cash = cash+2;
      printf("Well done, sir!\n");
      printf("Cash: £%d\n\n", cash);
    }
    else
    {
      printf("Bad luck, sir.\n");
      printf("Cash: £%d\n\n", cash);
    }
  }
  else
  {
    printf("Please select red or black, sir.\n\n");
    cash = cash+1;
    red_or_black_bet();
  }
}