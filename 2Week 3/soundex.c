#include <stdio.h>
#include <string.h>

#define MAXLINE 100

void read_in(char s[]);

char encode_char(char c);

char *remove_letters_1(char *s);

char *encode(char *s);

char *remove_doubles(char *s);

char *remove_letters_2(char *s);

char *ensure_length(char *s);

char *soundex_dash(char *s);

char *soundex_ddash(char *s);

char *shrink_right(char *s);

char *soundex(char *s);

int main(void)
{
  char line[MAXLINE];
  
  printf("Type a surname:");
  read_in(line);
  
  printf("The soundex code for this surname is: %s", soundex(line));
  
  return(0);
}

void read_in(char *s)
{
  int c, i = 0;
  
  while((c = getchar()) != EOF && c != '\n')
  {
    *(s+i) = c;
    i++;
  }
  *(s+i) = '\0';
}

char encode_char(char c)
{
  if(c == 'B' || c == 'P' || c == 'F' || c == 'B' || c == 'V' || c == 'b' || c == 'p' || c == 'f' || c == 'b' || c == 'v')
  {
    return('1');
  }
  else if(c == 'C' || c == 'G' || c == 'J' || c == 'K' || c == 'Q' || c == 'S' || c == 'X' || c == 'Z' || c == 'c' || c == 'g' || c == 'j' || c == 'k' || c == 'q' || c == 's' || c == 'x' || c == 'z')
  {
    return('2');
  }
  else if(c == 'D' || c == 'T' || c == 'd' || c == 't')
  {
    return('3');
  }
  else if(c == 'L' || c == 'l')
  {
    return('4');
  }
  else if(c == 'M' || c == 'N' || c == 'm' || c == 'n')
  {
    return('5');
  }
  else if(c == 'R' || c == 'r')
  {
    return('6');
  }
  else
  {
    return('0');
  }
}

char *remove_letters_1(char *s)
{
  static char new_string[MAXLINE];
  char *p = new_string;
  
  for( ; *s != '\0'; ++s)
  {
    if(*s == 'h' || *s == 'w')
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

char *encode(char *s)
{
  static char new_string[MAXLINE];
  char *p = new_string;
  
  for( ; *s != '\0'; ++s)
  {
    if(*s == 'b' || *s == 'f' || *s == 'p' || *s == 'v')
    {
      *p++ = '1';
    }
    else if(*s == 'c' || *s == 'g' || *s == 'j' || *s == 'k' || *s == 'q' || *s == 's' || *s == 'x' || *s == 'z')
    {
      *p++ = '2';
    }
    else if(*s == 'd' || *s == 't')
    {
      *p++ = '3';
    }
    else if(*s == 'l')
    {
      *p++ = '4';
    }
    else if(*s == 'm' || *s == 'n')
    {
      *p++ = '5';
    }
    else if(*s == 'r')
    {
      *p++ = '6';
    }
    else
    {
      *p++ = *s;
      *p = '\0';
    }
  }
  
  return(new_string);
}

char *remove_doubles(char *s)
{
  static char new_string[MAXLINE];
  char *p = new_string;
  
  for( ; *s != '\0'; ++s)
  {
    if(*s == *(s+1))
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

char *remove_letters_2(char *s)
{
  static char new_string[MAXLINE];
  char *p = new_string;
  
  for( ; *s != '\0'; ++s)
  {
    if(*s == 'a' || *s == 'e' || *s == 'i' || *s == 'o' || *s == 'u' || *s == 'y')
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

char *ensure_length(char *s)
{
  while(strlen(s) < 5)
  {
    strcat(s, "0");
  }
  return(s);
}

char *soundex_dash(char *s)
{
  return(ensure_length(remove_letters_2(remove_doubles(encode(remove_letters_1(s))))));
}

char *soundex_ddash(char *s)
{
  static char new_string[4];
  if(encode_char(soundex_dash(s)[0]) == soundex_dash(s)[1])
  {
    new_string[0] = soundex_dash(s)[0];
    new_string[1] = soundex_dash(s)[2];
    new_string[2] = soundex_dash(s)[3];
    new_string[3] = soundex_dash(s)[4];
    return(new_string);
  }
  else
  {
    return(soundex_dash(s));
  }
}

char *shrink_right(char *s)
{
  static char new_string[MAXLINE];
  char *p = new_string;
  
  for(int i = 0; i < 4; i++)
  {
    *p++ = *(s+i);
    *p = '\0';
  }
  
  return(new_string);  
}

char *soundex(char *s)
{
  return(shrink_right(soundex_ddash(s)));
}