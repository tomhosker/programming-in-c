#include <stdio.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

char isvowel(char c);

int main(void)
{
  char c;
  
  printf("Type a character: ");
  
  while(c != EOF)
  {
    c = getchar();
    if(isvowel(c) == TRUE)
    {
      putchar(toupper(c));
    }
    else
    {
      putchar(tolower(c));
    }
  }
  
  return(0);
}

char isvowel(char c)
{
  if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
  {
    return(TRUE);
  }
  else
  {
    return(FALSE);
  }
}