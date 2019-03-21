#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LET 20
#define TRUE 1
#define FALSE 0
#define LIST_SIZE 128773
#define SORTED_LIST_FILE_NAME "sorted_list.txt"

struct node{
  char word[MAX_LET];
  struct node *next;
};

typedef struct node Node;

void generate_unsorted(char array[LIST_SIZE][MAX_LET], char filename[]);

char *get_word(int i, char array[LIST_SIZE][MAX_LET]);

Node *allocate_node(char *s);

int is_after_dash(char *word_1, char *word_2, int letter);

int is_after(char *word_1, char *word_2);

void integrate(char *word_dash, Node *l);

void print_list_to_file(Node *l);

int main(int argc, char **argv)
{
  int i;
  Node *start, *current;
  char unsorted[LIST_SIZE][MAX_LET];

  generate_unsorted(unsorted, argv[1]);
  start = current = allocate_node("(START)");
  start->next = allocate_node("{FINISH}");

  for(i = 0; i < LIST_SIZE; i++)
  {
    integrate(get_word(i, unsorted), start);
  }

  print_list_to_file(start);
  
  return(0);
}

void generate_unsorted(char array[LIST_SIZE][MAX_LET], char filename[])
{
  static char line[MAX_LET];
  char *token;
  int i = 0;
  FILE *file = fopen(filename, "r");

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

char *get_word(int i, char array[LIST_SIZE][MAX_LET])
{
  return(array[i]);
}

Node *allocate_node(char *s)
{
  Node *p;
  
  p = (Node *)malloc(sizeof(Node));
  if(p == NULL)
  {
    printf("Cannot allocate node\n");
    exit(2);
  }
  strcpy(p->word, s);
  p->next = NULL;
  
  return(p);
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

void integrate(char *word_dash, Node *l)
{
  Node *l_previous = NULL;
  Node *word_dash_pointer;

  word_dash_pointer = allocate_node(word_dash);

  while(l != NULL)
  {
    if(is_after(word_dash, l->word) == TRUE)
    {
      l_previous = l;
      l = l->next;
    }
    else
    {
      l_previous->next = word_dash_pointer;
      word_dash_pointer->next = l;
      return;
    }
  }
}

void print_list_to_file(Node *l)
{
  FILE *file = fopen(SORTED_LIST_FILE_NAME, "w+");

  do{
    fprintf(file, "%s\n", l->word);
    l = l->next;
  }while(l != NULL);

  fclose(file);
}
