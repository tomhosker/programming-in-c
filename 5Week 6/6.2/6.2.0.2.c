#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LET 20
#define TRUE 1
#define FALSE 0
#define LIST_SIZE 128773
#define LIST_SIZE_DASH LIST_SIZE
#define SORTED_LIST_FILE_NAME "sorted_list.txt"

struct node{
  char word[MAX_LET];
  struct node *next;
};

typedef struct node Node;

char *get_word(int line_number);

Node *AllocateNode(char *s);

int is_after_dash(char *word_1, char *word_2, int letter);

int is_after(char *word_1, char *word_2);

void integrate(char *word_dash, Node *l);

void PrintList(Node *l);

int main(void)
{
  char word_dash[MAX_LET];
  int i;
  Node *start, *current;
  
  start = current = AllocateNode("(START)");
  start->next = AllocateNode("{FINISH}");

  for(i = 0; i < LIST_SIZE_DASH; i++)
  {
    integrate(get_word(i), start);
  }

  PrintList(start);
  
  return(0);
}

char *get_word(int line_number)
{
  static const char filename[] = "eowl_shuffle.txt";
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

Node *AllocateNode(char *s)
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

  word_dash_pointer = AllocateNode(word_dash);

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

void PrintList(Node *l)
{
  do{
    printf("%s\n", l->word);
    l = l->next;
  }while(l != NULL);
}
