#include <stdio.h>
#include <string.h>

#define WORD_LENGTH 4
#define ALPHABET_LENGTH 26
#define WORD_BANK "34words.txt"
#define HUNDRED 100

int comparison(char *str_1, char *str_2);

int search_in_file(char *fname, char *str);

char *swap_one(char *str, int i);

char *find_comparison(char *fname, char *str, int c);

int main(void)
{  
  printf("%s", swap_one("uork", 1));
 
  return(0);
}

int comparison(char *str_1, char *str_2)
{
  int count = 0;
  int i;
  
  if(strlen(str_1) != strlen(str_2))
  {
    return(0);
  }

  for(i = 0; i < strlen(str_1); i++)
  {
    if(*(str_1+i) == *(str_2+i))
    {
      count++;
    }
  }
  
  return(count);
}

int search_in_file(char *fname, char *str)
{
  FILE *fp;
  int line_num = 1;
  char temp[512];
  
  if((fp = fopen(fname, "r")) == NULL)
  {
    return(-1);
  }

  while(fgets(temp, 512, fp) != NULL)
  {
    if((strstr(temp, str)) != NULL)
    {
      return(line_num);
    }
    line_num++;
  }

  if(fp)
  {
    fclose(fp);
  }

  return(0);
}

char *swap_one(char *str, int i)
{
  static char new_str[WORD_LENGTH];
  int j;
  
  i = i-1;
  strcpy(new_str, str);

  for(j = 0; j < ALPHABET_LENGTH; j++)
  {
    *(new_str+i) = j+'a';
    if(search_in_file(WORD_BANK, new_str) != 0)
    {
      return(new_str);
    }
    else
    {
      strcpy(new_str, str);
    }
  }
  
  return(0);
}

char *find_comparison(char *fname, char *str, int c)
{
  static char new_str[WORD_LENGTH];
  FILE *fp;
  char temp[WORD_LENGTH];

  if((fp = fopen(fname, "r")) == NULL)
  {
    return(NULL);
  }

  while(fgets(temp, WORD_LENGTH+1, fp) != NULL)
  {
    if(comparison(temp, str) == c)
    {
      strcpy(new_str, temp);
      return(new_str);
    }
  }

  if(fp)
  {
    fclose(fp);
  }
}
