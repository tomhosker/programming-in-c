#include <stdio.h>

#define MAXLINE 100

void read_in(char s[]);

char *remove_iv_ix(char *s);

char *remove_xl_xc(char *s);

char *remove_cd_cm(char *s);

char *remove_non_additive(char *s);

int sum_additive(char *s);

int main(void)
{
  char line[MAXLINE];
  
  printf("Type a Roman numeral:");
  read_in(line);
  
  printf("%s is equal to %d.", line, roman_to_arabic(line));
  
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

char *remove_iv_ix(char *s)
{
  static char new_string[MAXLINE];
  char *p = new_string;
  
  for( ; *s != '\0'; ++s)
  {
    if(*s == 'I' && *(s+1) == 'V')
    {
      *p = '4';
      p++;
      *p = '0';
      p = p+2;
    }
    else if(*s == 'I' && *(s+1) == 'X')
    {
      *p = '9';
      p++;
      *p = '0';
      p = p+2;
    }
    else
    {
      *p++ = *s;
      *p = '\0';
    }
  }
  
  return(new_string);
}

char *remove_xl_xc(char *s)
{
  static char new_string[MAXLINE];
  char *p = new_string;
  
  for( ; *s != '\0'; ++s)
  {
    if(*s == 'X' && *(s+1) == 'L')
    {
      *p = 'Q';
      p++;
    }
    else if(*s == 'X' && *(s+1) == 'C')
    {
      *p = 'W';
      p++;
    }
    else
    {
      *p++ = *s;
      *p = '\0';
    }
  }
  
  return(new_string);
}

char *remove_cd_cm(char *s)
{
  static char new_string[MAXLINE];
  char *p = new_string;
  
  for( ; *s != '\0'; ++s)
  {
    if(*s == 'C' && *(s+1) == 'D')
    {
      *p = 'E';
      p++;
    }
    else if(*s == 'C' && *(s+1) == 'M')
    {
      *p = 'R';
      p++;
    }
    else
    {
      *p++ = *s;
      *p = '\0';
    }
  }
  
  return(new_string);
}

char *remove_non_additive(char *s)
{
  return(remove_cd_cm(remove_xl_xc(remove_iv_ix(s))));
}

int sum_additive(char *s)
{
  int sum = 0;
  int i = 0;
  
  while(s[i] != '\0')
  {
    if(s[i] == '0' || s[i] == '4' || s[i] == '9')
    {
      sum = sum + s[i] - '0';
      i++;
    }
    else if(s[i] == 'Q')
    {
      sum = sum - 10;
      i++;
    }
    else if(s[i] == 'W')
    {
      sum = sum - 10;
      i++;
    }
    else if(s[i] == 'E')
    {
      sum = sum - 100;
      i++;
    }
    else if(s[i] == 'R')
    {
      sum = sum - 100;
      i++;
    }
    else if(s[i] == 'I')
    {
      sum = sum + 1;
      i++;
    }
    else if(s[i] == 'V')
    {
      sum = sum + 5;
      i++;
    }
    else if(s[i] == 'X')
    {
      sum = sum + 10;
      i++;
    }
    else if(s[i] == 'L')
    {
      sum = sum + 50;
      i++;
    }
    else if(s[i] == 'C')
    {
      sum = sum + 100;
      i++;
    }
    else if(s[i] == 'D')
    {
      sum = sum + 500;
      i++;
    }
    else if(s[i] == 'M')
    {
      sum = sum + 1000;
      i++;
    }
    else
    {
      i++;
    }
  }
  
  return(sum);
}

int roman_to_arabic(char *s)
{
  return(sum_additive(remove_non_additive(s)));
}