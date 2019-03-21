#include <stdio.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

char isvowel(char c);

int main(void)
{
  char c;
  
  printf("Type a sentence in English: ");
  
  while(c != EOF)
  {
    c = getchar();
    if(isvowel(c) == TRUE)
    {
      putchar('-');
    }
    else
    {
      putchar(c);
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
