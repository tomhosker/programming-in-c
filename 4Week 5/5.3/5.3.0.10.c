#include <stdio.h>
#include <string.h>

#define WORD_LENGTH 4
#define ALPHABET_LENGTH 26
#define WORD_BANK "34words.txt"
#define WORD_LENGTH_FACTORIAL 24
#define HUNDRED 100

int comparison(char *str_1, char *str_2);

int search_in_file(char *fname, char *str);

char *swap_one(char *str, int i);

char *swap_eno(char *str, int i);

char *ladder_ddash(char *str_1, char *str_2, int p, int q);

int ladder_dash(char *str_1, char *str_2, int p, int e, int r, int m);

void swap(char *x, char *y);

void permute(char *a, int l, int r, char *perms);

int ladder(char *str_1, char *str_2);

int are_valid(char *str_1, char *str_2);

void read_in(char *s);

void print_intro(void);

int main(void)
{
  char str_1[WORD_LENGTH];
  char str_2[WORD_LENGTH];
  int c;

  print_intro();
  
  while(are_valid(str_1, str_2) != 1)
  {
    read_in(str_1);
    read_in(str_2);
    printf("\n");
    if(are_valid(str_1, str_2) != 1)
    {
      printf("That isn't a valid pair of words. Try again.\n\n");
    }
  }
  ladder(str_1, str_2);
  
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

  for(j = 1; j < HUNDRED; j++)
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
  for(j = 1; j < HUNDRED; j++)
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

char *ladder_ddash(char *str_1, char *str_2, int p, int q)
{
  static char new_str[WORD_LENGTH+1];
  int count = 0;
  
  strcpy(new_str, str_1);

  while((comparison(new_str, str_2) != q) && (count < HUNDRED))
  {
    if(swap_one(new_str, p) == NULL)
    {
      return(NULL);
    }
    else if(count < ALPHABET_LENGTH)
    {
      strcpy(new_str, swap_one(new_str, p));
      count++;
    }
    else
    {
      strcpy(new_str, swap_eno(new_str, p));
      count++;
    }
  }
  
  if(comparison(new_str, str_2) == q)
  {
    return(new_str);
  }
  else
  {
    return(NULL);
  }
}

int ladder_dash(char *str_1, char *str_2, int p, int e, int r, int m)
{
  static char new_str[WORD_LENGTH+1];
  
  strcpy(new_str, str_1);
  printf("%s\n", new_str);
  
  if(ladder_ddash(new_str, str_2, p, 1) != NULL)
  {
    strcpy(new_str, ladder_ddash(new_str, str_2, p, 1));
    printf("%s\n", new_str);
  }
  else
  {
    printf("Wrong path!\n\n");
    return(0);
  }

  if(ladder_ddash(new_str, str_2, e, 2) != NULL)
  {
    strcpy(new_str, ladder_ddash(new_str, str_2, e, 2));
    printf("%s\n", new_str);
  }
  else
  {
    printf("Wrong path!\n\n");
    return(0);
  }

  if(ladder_ddash(new_str, str_2, r, 3) != NULL)
  {
    strcpy(new_str, ladder_ddash(new_str, str_2, r, 3));
    printf("%s\n", new_str);
  }
  else
  {
    printf("Wrong path!\n\n");
    return(0);
  }

  if(ladder_ddash(new_str, str_2, m, 4) != NULL)
  {
    strcpy(new_str, ladder_ddash(new_str, str_2, m, 4));
    printf("%s\n", new_str);
  }
  else
  {
    printf("Wrong path!\n\n");
    return(0);
  }

  return(1);
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

int ladder(char *str_1, char *str_2)
{
  int i, p, e, r, m;
  char o[] = "1234";
  char perm[WORD_LENGTH*WORD_LENGTH_FACTORIAL];
  permute(o, 0, strlen(o)-1, perm);

  for(i = 0; i < WORD_LENGTH_FACTORIAL; i++)
  {
    p = perm[0+(i*WORD_LENGTH)]-'0';
    e = perm[1+(i*WORD_LENGTH)]-'0';
    r = perm[2+(i*WORD_LENGTH)]-'0';
    m = perm[3+(i*WORD_LENGTH)]-'0';
    printf("Path: %d%d%d%d\n", p, e, r, m);
    if(ladder_dash(str_1, str_2, p, e, r, m) != 0)
    {
      return(1);
    }
  }
  
  return(0);
}

int are_valid(char *str_1, char *str_2)
{
  if(strlen(str_1) != WORD_LENGTH)
  {
    return(0);
  }
  if(strlen(str_2) != WORD_LENGTH)
  {
    return(0);
  }
  if(search_in_file(WORD_BANK, str_1) == 0)
  {
    return(0);
  }
  if(search_in_file(WORD_BANK, str_2) == 0)
  {
    return(0);
  }
  if(comparison(str_1, str_2) != 0)
  {
    return(0);
  }

  return(1);
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

void print_intro(void)
{
  printf("Type in two words below, separated by a new lines.\n");
  printf("These two words must:\n");
  printf("# Be all in lower case;\n");
  printf("# Be of four letters each;\n");
  printf("# Be in the word bank;\n");
  printf("# Have no letters in common.\n\n");
}
