#include <stdio.h>
#define HOUR_LENGTH 60
#define DAY_LENGTH 24

void intro(void);

int minutes_diff(int min_a, int min_b);

int hours_diff(int hrs_a, int hrs_b, int min_a, int min_b);

int main(void)
{
  int hrs_a, hrs_b, min_a, min_b;
  
  intro();
  
  while(hrs_a != EOF)
  {
    printf("Enter the first time: ");
    scanf("%d%d", &hrs_a, &min_a);
    printf("Enter the second time: ");
    scanf("%d%d", &hrs_b, &min_b);
    if(hrs_a < 24 && hrs_b < 24 && min_a < 60 && min_b < 60)
    {
      printf("You entered: First time: %02d:%02d and Second time: %02d:%02d.\n", hrs_a, min_a, hrs_b, min_b);
    }
    else
    {
      printf("One (or both) of those isn't a valid time! Try again.\n\n");
      return(0);
    }
    printf("The difference between the two times is ");
    printf("%d hours and %d minutes.\n\n", hours_diff(hrs_a, hrs_b, min_a, min_b), minutes_diff(min_a, min_b));
  }
  
  return(0);
}

void intro(void)
{
  printf("Welcome to Tom's Time Calculator (TM)!\n");
  printf("This program will calculate the hours and minutes\n");
  printf("between two times no more than 24 hours apart.\n");
  printf("But be careful to enter times in 24-hour format,\n");
  printf("e.g. 13:28.\n\n");
}

int minutes_diff(int min_a, int min_b)
{
  if(min_b > min_a)
  {
    return(min_b-min_a);
  }
  if(min_b == min_a)
  {
    return(0);
  }
  if(min_b < min_a)
  {
    return(min_b+(HOUR_LENGTH-min_a));
  }
}
  
int hours_diff(int hrs_a, int hrs_b, int min_a, int min_b)
{
  if(hrs_b > hrs_a)
  {
    if(min_b >= min_a)
    {
      return(hrs_b-hrs_a);
    }
    else
    {
      return(hrs_b-hrs_a-1);
    }
  }
  if(hrs_b == hrs_a)
  {
    if(min_b >= min_a)
    {
      return(0);
    }
    else
    {
      return(DAY_LENGTH-1);
    }
  }
  if(hrs_b < hrs_a)
  {
    if(min_b >= min_a)
    {
      return(hrs_b+(DAY_LENGTH-hrs_a));
    }
    else
    {
      return(hrs_b+(DAY_LENGTH-hrs_a)-1);
    }
  }
}
