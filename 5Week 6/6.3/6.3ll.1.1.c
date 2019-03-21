#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LET 20
#define TRUE 1
#define FALSE 0
#define LIST_SIZE 128773
#define CORRECT 1
#define NOT_CORRECT 0
#define WORD_BANK "eowl_shuffle.txt"

struct node{
  char *word;
  struct node *next;
};

typedef struct node Node;

void generate_unsorted(char array[LIST_SIZE][MAX_LET], char filename[]);

Node *allocate_node(char *s);

int spell_check(char *str, Node *l);

int main(int argc, char **argv)
{
  int i;
  Node *start, *current;
  char unsorted[LIST_SIZE][MAX_LET];

  generate_unsorted(unsorted, WORD_BANK);
  start = current = allocate_node("START");
  
  while(i < LIST_SIZE)
  {
    current->next = allocate_node(unsorted[i]);
    current = current->next;
    i++;
  }

  if(spell_check(argv[1], start) == CORRECT)
  {
    printf("Yes, %s is spelled correctly.\n", argv[1]);
  }
  else
  {
    printf("No, %s is not spelled correctly.\n", argv[1]);
  }

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

Node *allocate_node(char *s)
{
  Node *p;
  p = (Node *)malloc(sizeof(Node));
  if(p == NULL)
  {
    printf("Cannot allocate node\n");
    exit(2);
  }

  p->word = s;
  p->next = NULL;

  return(p);
}

int spell_check(char *str, Node *l)
{
  do{
    if(strcmp(l->word, str) == 0)
    {
      return(CORRECT);
    }
    l = l->next;
  }while(l != NULL);

  return(NOT_CORRECT);
}
