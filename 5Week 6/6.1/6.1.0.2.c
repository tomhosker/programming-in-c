#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_LET 20
#define TRUE 1
#define FALSE 0
#define LIST_SIZE 128773
#define SORTED_LIST_FILE_NAME "sorted_list.txt"

char *get_word(int line_number);

int is_after(char *word_1, char *word_2, int letter);

void make_space(char array[5][MAX_LET], int i);

void insert_string(char array[5][MAX_LET], char str[], int i);

void print_array_to_file(char array[5][MAX_LET]);

int main(void)
{
  char array_0[5][MAX_LET] = {"andy", "bob", "daniel", "edward"};
  make_space(array_0, 2);
  insert_string(array_0, "charlie", 2);

  print_array_to_file(array_0);

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

void make_space(char array[5][MAX_LET], int i)
{
  int j, k;

  for(j = 5-1; j > i; j--)
  {
    for(k = 0; k < MAX_LET; k++)
    {
      array[j][k] = array[j-1][k];
    } 
  }
}

void insert_string(char array[5][MAX_LET], char str[], int i)
{
  int j = 0;

  while(str[j] != '\0')
  {
    array[i][j] = str[j];
    j++;
  }
  array[i][j] = '\0';
}

void print_array_to_file(char array[5][MAX_LET])
{
  int i;
  static const char filename[] = SORTED_LIST_FILE_NAME;
  FILE *file = fopen(filename, "w");

  for(i = 0; i < 5; i++)
  {
    fprintf(file, "%s\n", array[i]);
  }
}
