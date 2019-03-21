#include <stdio.h>
#include <string.h>

#define WORD_LENGTH 4
#define ALPHABET_LENGTH 26
#define WORD_BANK "34words.txt"
#define WORD_LENGTH_FACTORIAL 24

int comparison(char *str_1, char *str_2);

int search_in_file(char *fname, char *str);

char *swap_one(char *str, int i);

char *find_comparison(char *fname, char *str, int c);

char *ladder_ddash(char *str_1, char *str_2, int p, int q);

int ladder_dash(char *str_1, char *str_2, int p, int e, int r, int m);

void swap(char *x, char *y);

void permute(char *a, int l, int r, char *perms);

int main(void)
{
  ladder_dash("cube", "tons", 4, 1, 3, 2);

  char string[] = "1234";
  char perms_0[WORD_LENGTH*WORD_LENGTH_FACTORIAL];
  permute(string, 0, strlen(string)-1, perms_0);
  printf("%s\n", perms_0);
  
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
  static char new_str[WORD_LENGTH+1];
  int j;
  
  i = i-1;
  strcpy(new_str, str);

  for(j = 1; j < ALPHABET_LENGTH; j++)
  {
    *(new_str+i) = *(new_str+i)+j;
    if(search_in_file(WORD_BANK, new_str) != 0)
    {
      return(new_str);
    }
    else
    {
      strcpy(new_str, str);
    }
  }
  for(j = 1; j < ALPHABET_LENGTH; j++)
  {
    *(new_str+i) = *(new_str+i)-j;
    if(search_in_file(WORD_BANK, new_str) != 0)
    {
      return(new_str);
    }
    else
    {
      strcpy(new_str, str);
    }
  }
  
  return(NULL);
}

char *swap_eno(char *str, int i)
{
  static char new_str[WORD_LENGTH+1];
  int j;
  
  i = i-1;
  strcpy(new_str, str);

  for(j = 1; j < ALPHABET_LENGTH; j++)
  {
    *(new_str+i) = *(new_str+i)-j;
    if(search_in_file(WORD_BANK, new_str) != 0)
    {
      return(new_str);
    }
    else
    {
      strcpy(new_str, str);
    }
  }
  for(j = 1; j < ALPHABET_LENGTH; j++)
  {
    *(new_str+i) = *(new_str+i)+j;
    if(search_in_file(WORD_BANK, new_str) != 0)
    {
      return(new_str);
    }
    else
    {
      strcpy(new_str, str);
    }
  }
  
  return(NULL);
}

char *find_comparison(char *fname, char *str, int c)
{
  static char new_str[WORD_LENGTH+1];
  FILE *fp;
  char temp[WORD_LENGTH+1];

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

char *ladder_ddash(char *str_1, char *str_2, int p, int q)
{
  static char new_str[WORD_LENGTH+1];
  int count = 0;
  
  strcpy(new_str, str_1);

  while(comparison(new_str, str_2) != q)
  {
    strcpy(new_str, swap_one(new_str, p));
    count++;
    if(count == ALPHABET_LENGTH)
    {
      strcpy(new_str, swap_eno(new_str, p));
      count++;
      if(count == ALPHABET_LENGTH*ALPHABET_LENGTH)
      {
        printf("Sorry. No path was found.");
        return(NULL);
      }
    }
  }
  count = 0;

  return(new_str);
}

int ladder_dash(char *str_1, char *str_2, int p, int e, int r, int m)
{
  static char new_str[WORD_LENGTH+1];
  
  strcpy(new_str, str_1);
  printf("%s\n", new_str);
  
  strcpy(new_str, ladder_ddash(new_str, str_2, p, 1));
  printf("%s\n", new_str);

  strcpy(new_str, ladder_ddash(new_str, str_2, e, 2));
  printf("%s\n", new_str);

  strcpy(new_str, ladder_ddash(new_str, str_2, r, 3));
  printf("%s\n", new_str);

  strcpy(new_str, ladder_ddash(new_str, str_2, m, 4));
  printf("%s\n", new_str);

  return(0);
}

void swap(char *x, char *y)
{
  char temp;
  temp = *x;
  *x = *y;
  *y = temp;
}

void permute(char *a, int l, int r, char *perms)
{
  static char new_str[WORD_LENGTH*WORD_LENGTH_FACTORIAL];
  int i;
  
  if (l == r)
  {
    strcat(new_str, a);
  }
  else
  {
    for (i = l; i <= r; i++)
    {
      swap((a+l), (a+i));
      permute(a, l+1, r, perms);
      swap((a+l), (a+i));
    }
  }

  strcpy(perms, new_str);
}
