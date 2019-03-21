#include <stdio.h>

int no_c_presses(int time, int c);

int no_b_presses(int time, int b, int c);

int no_a_presses(int time, int a, int b, int c);

int main(void)
{
  int buttons[3] = {10, 60, 600};
  int time;
  
  while(time != EOF)
  {
    printf("Type the time required:");
    if(scanf("%d", &time) != 1)
    {
      printf("You should have entered an integer! Try again.");
      return(0);
    }
    
    int min_presses = no_c_presses(time, buttons[2])+no_b_presses(time, buttons[1], buttons[2])+no_a_presses(time, buttons[0], buttons[1], buttons[2]);
    
    printf("Button presses required: %d\n\n", min_presses);
  }
  
  return(0);
}

int no_c_presses(int time, int c)
{
  int c_presses = (time-(time%c))/c;
  return(c_presses);
}

int no_b_presses(int time, int b, int c)
{
  int c_presses = (time-(time%c))/c;
  int time_dash = time-(c_presses*c);
  int b_presses = (time_dash-(time_dash%b))/b;
  return(b_presses);
}

int no_a_presses(int time, int a, int b, int c)
{
  int c_presses = (time-(time%c))/c;
  int time_dash = time-(c_presses*c);
  int b_presses = (time_dash-(time_dash%b))/b;
  int time_ddash = time_dash-(b_presses*b);
  
  int a_presses;
  if(time_ddash%a == 0)
  {
    a_presses = time_ddash/a;
  }
  else
  {
    a_presses = (time_ddash/a)+1;
  }
  
  return(a_presses);
}