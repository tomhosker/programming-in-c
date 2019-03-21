#include <stdio.h>
#include <string.h>

#define MAX_LET 20
#define TRUE 1
#define FALSE 0
#define LIST_SIZE 128773
#define LIST_SIZE_DASH 100
#define SORTED_LIST_FILE_NAME "sorted_list.txt"
#define UNSORTED_LIST_FILE_NAME "eowl_suffle.txt"

char *get_word(int line_number, char filename[]);

int is_after_dash(char *word_1, char *word_2, int letter);

int is_after(char *word_1, char *word_2);

void make_space(char array[LIST_SIZE][MAX_LET], int i);

void insert_string(char array[LIST_SIZE][MAX_LET], char str[], int i);

void print_array_to_file(char array[LIST_SIZE][MAX_LET]);

int find_position(char array[LIST_SIZE][MAX_LET], char str[]);

void find_and_insert(char array[LIST_SIZE][MAX_LET], char str[]);

void initialise_word_list(char array[LIST_SIZE][MAX_LET]);

void read_in(char *s);

void generate_sorted(char array[LIST_SIZE][MAX_LET]);

int find_in_sorted(char small_array[MAX_LET], char big_array[LIST_SIZE][MAX_LET]);

int main(int argc, char **argv)
{
  char word_list[LIST_SIZE][MAX_LET];
  int x, i;  
  char word[MAX_LET];

  printf("Would you like to\n");
  printf("build a sorted list (0),\n");
  printf("or check the spelling of a word (1)?\n");
  
  scanf("%d", &x);

  if(x == 0)
  {
    initialise_word_list(word_list);
    for(i = 0; i < LIST_SIZE_DASH; i++)
    {
      find_and_insert(word_list, get_word(i, UNSORTED_LIST_FILE_NAME));
    }
    print_array_to_file(word_list);
  }
  else
  {
    if(argc != 2)
    {
      printf("You need to enter the word via the command line. Try again.");
    }

    generate_sorted(word_list);
    strcpy(word, argv[1]);
    
    if(find_in_sorted(word, word_list) == 1)
    {
      printf("\nYes, %s is spelled correctly.\n", word);
    }
    else
    {
      printf("\nNo, %s is not spelled correctly.\n", word);
    }
  }

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

void generate_sorted(char array[LIST_SIZE][MAX_LET])
{
  static char line[MAX_LET];
  char *token;
  int i = 0;
  FILE *file = fopen(SORTED_LIST_FILE_NAME, "r");

  if(file != NULL)
  {
    while(fgets(line, MAX_LET, file) != NULL)
    {
      token = strtok(line, "\n");
      strcpy(array[i], token);
      i++;
    }
  }
  else
  {
    printf("Failed to open file.");
    return;
  }
  fclose(file);
}

int find_in_sorted(char small_array[MAX_LET], char big_array[LIST_SIZE][MAX_LET])
{
  int i;
  for(i = 0; i < LIST_SIZE; i++)
  {
    if(strcmp(small_array, big_array[i]) == 0)
    {
      return(TRUE);
    }
  }
  return(FALSE);
}
