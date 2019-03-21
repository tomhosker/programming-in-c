#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_LET 20
#define TRUE 1
#define FALSE 0

char *get_word(int line_number);

int is_after(char *word_1, char *word_2, int letter);

int main(void)
{
  printf("%s\n", get_word(0));
  printf("%d\n", is_after("daa", "dave", 0));
  
  return(0);
}

char *get_word(int line_number)
{
  static const char filename[] = "eowl_shuffle.txt";
  static char line[MAX_LET];
  int count = 0;
  FILE *file = fopen(filename, "r");

  if(file != NULL)
  {
    while(fgets(line, MAX_LET, file) != NULL)
    {
      if(count == line_number)
      {
        fclose(file);
        return(line);
      }
      else
      {
        count++;
      }
    }
    fclose(file);
    return(NULL);
  }
  else
  {
    return(NULL);
  }
}

int is_after(char *word_1, char *word_2, int letter)
{
  if(*(word_1+letter) > *(word_2+letter))
  {
    return(TRUE);
  }
  else if(*(word_1+letter) > *(word_2+letter))
  {
    return(FALSE);
  }
  else
  {
    return(is_after(word_1, word_2, letter+1));
  }
}
