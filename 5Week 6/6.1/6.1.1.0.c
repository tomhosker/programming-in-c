#include <stdio.h>
#include <string.h>

#define MAX_LET 20
#define TRUE 1
#define FALSE 0
#define LIST_SIZE 128773
#define LIST_SIZE_DASH 100
#define SORTED_LIST_FILE_NAME "sorted_list.txt"

char *get_word(int line_number, char filename[]);

int is_after_dash(char *word_1, char *word_2, int letter);

int is_after(char *word_1, char *word_2);

void make_space(char array[LIST_SIZE][MAX_LET], int i);

void insert_string(char array[LIST_SIZE][MAX_LET], char str[], int i);

void print_array_to_file(char array[LIST_SIZE][MAX_LET]);

int find_position(char array[LIST_SIZE][MAX_LET], char str[]);

void find_and_insert(char array[LIST_SIZE][MAX_LET], char str[]);

void initialise_word_list(char array[LIST_SIZE][MAX_LET]);

int main(int argc, char **argv)
{
  char word_list[LIST_SIZE][MAX_LET];
  int i;  

  initialise_word_list(word_list);
  for(i = 0; i < LIST_SIZE_DASH; i++)
  {
    find_and_insert(word_list, get_word(i, argv[1]));
  }
  print_array_to_file(word_list);

  return(0);
}

char *get_word(int line_number, char filename[])
{
  static char line[MAX_LET];
  char *token;
  int count = 0;
  FILE *file = fopen(filename, "r");

  if(file != NULL)
  {
    while(fgets(line, MAX_LET, file) != NULL)
    {
      if(count == line_number)
      {
        token = strtok(line, "\n");
        fclose(file);
        return(token);
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

int is_after_dash(char *word_1, char *word_2, int letter)
{
  if(*(word_1+letter) > *(word_2+letter))
  {
    return(TRUE);
  }
  else if(*(word_1+letter) < *(word_2+letter))
  {
    return(FALSE);
  }
  else
  {
    return(is_after_dash(word_1, word_2, letter+1));
  }
}

int is_after(char *word_1, char *word_2)
{
  return(is_after_dash(word_1, word_2, 0));
}

void make_space(char array[LIST_SIZE][MAX_LET], int i)
{
  int j, k;

  for(j = LIST_SIZE-1; j > i; j--)
  {
    for(k = 0; k < MAX_LET; k++)
    {
      array[j][k] = array[j-1][k];
    } 
  }
}

void insert_string(char array[LIST_SIZE][MAX_LET], char str[], int i)
{
  int j = 0;

  while(str[j] != '\0')
  {
    array[i][j] = str[j];
    j++;
  }
  array[i][j] = '\0';
}

void print_array_to_file(char array[LIST_SIZE][MAX_LET])
{
  int i;
  static const char filename[] = SORTED_LIST_FILE_NAME;
  FILE *file = fopen(filename, "w");

  for(i = 0; i < LIST_SIZE; i++)
  {
    fprintf(file, "%s\n", array[i]);
  }

  fclose(file);
}

int find_position(char array[LIST_SIZE][MAX_LET], char str[])
{
  int i;
  for(i = 0; i < LIST_SIZE; i++)
  {
    if(is_after(str, array[i]) == FALSE)
    {
      return(i);
    }
  }
  return(-1);
}

void find_and_insert(char array[LIST_SIZE][MAX_LET], char str[])
{
  int i;
  
  i = find_position(array, str);
  make_space(array, i);
  insert_string(array, str, i);
  print_array_to_file(array);
}

void initialise_word_list(char array[LIST_SIZE][MAX_LET])
{
  int i;

  for(i = 0; i < LIST_SIZE; i++)
  {
    array[i][0] = '{';
    array[i][1] = '\0';
  }
}
