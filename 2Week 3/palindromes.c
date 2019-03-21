#include <stdio.h>
#include <ctype.h>

#define MAXLINE 26

void read_in(char s[]);

char *change(char *s);

int length(char *string);

int is_palindrome(char *string);

int main(void)
{
  char line[MAXLINE];
  
  printf("Type some text.\n");
  read_in(line);
  
  if(is_palindrome(change(line)) == 0)
  {
    printf("Sorry, that isn't a palindrome.\n\n");
  }
  else
  {
    printf("Yes! That's a palindrome!");
  }
  
  return(0);
}

void read_in(char *s)
{
  int c, i = 0;
  
  while ((c = getchar()) != EOF && c != '\n')
  {
    *(s+i) = c;
    i++;
  }
  *(s+i) = '\0';
}

char *change(char *s)
{
  static char new_string[MAXLINE];
  char *p = new_string;
  
  for( ; *s != '\0'; ++s)
  {
    if(isupper(*s) != 0)
    {
      *p++ = tolower(*s);
    }
    else if(*s == ' ' || *s == ',' || *s == '.' || *s == '?')
    {
      ;
    }
    else
    {
      *p++ = *s;
      *p = '\0';
    }
  }
  
  return(new_string);
}

int length(char *string)
{
  int count = 0;
  for(int i = 0; *(string+i) != '\0'; i++)
  {
    count++;
  }
  return(count);
}

int is_palindrome(char *string)
{
  int count = 0;
  for(int i = 0; i < length(string)/2; i++)
  {
    if(*(string+i) != *(string+length(string)-1-i))
    {
      return(0);
    }
  }
  return(1);
}