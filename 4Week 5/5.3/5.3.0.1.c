#include <stdio.h>
#include <string.h>

#define WORD_LENGTH 4

int comparison(char *str_1, char *str_2);

int main(void)
{
  
  
  printf("%d", comparison("helo", "hero"));
  
  return(0);
}

int comparison(char *str_1, char *str_2)
{
  int count = 0;
  int i;
  
  for(i = 0; i < WORD_LENGTH; i++)
  {
    if(*(str_1+i) == *(str_2+i))
    {
      count++;
    }
  }
  
  return(count);
}