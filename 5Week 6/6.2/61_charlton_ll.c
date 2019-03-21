#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define ERROR_NULLPOINTER -1
#define ERROR_OPEN -2
#define ERROR_MEMORY -3
#define ERROR_READ -4

#define WORDS_FILE "eowl_shuffle.txt"

typedef struct node{
  char* str;
  struct node* next;
} node;

int loadFileToMemory(char *fileName, char **bufferIn);
int linkedListInsert(node **start, char *str);

int main(void) {
  char *buffer = NULL;
  
  // load the entire to memory, and handle errors
  int errorCode = loadFileToMemory(WORDS_FILE, &buffer);
  if(errorCode != 0) {
    switch(errorCode) {
      case ERROR_NULLPOINTER:
        fprintf(stderr, "Null pointer passed to loadFileToMemory();\n");
        break;

      case ERROR_OPEN:
        fprintf(stderr, "Error opening the file %s\n", WORDS_FILE);
        break;

      case ERROR_MEMORY:
        fprintf(stderr, "Error allocating memory for the file buffer\n");
        break;

      case ERROR_READ:
        fprintf(stderr, "Error reading the file %s\n", WORDS_FILE);
        break;

      default:
        fprintf(stderr, "Some other error occurred\n");
        break;
     }

    exit(errorCode);
  }

  // Now we have the entire file in memory,
  // we can then process it directly, and
  // more quickly
  

  // Each word is separated by a new line, so
  // count the number of words, by counting these
  size_t numberWords = 0;
  for(char *c = buffer; *c != '\0'; c++) {
    if('\n' == *c) {
      numberWords++;
    }
  }

  // Allocate the start node of the linked list
  node *start = NULL;

  // Tokenize the buffer at newline's, and insert the resulting
  // words in to the correct place in the sortedArray
  char *token = NULL;
  size_t i = 0;
  token = strtok(buffer, "\n");
  while(NULL != token) {
    // This line prints an updating counter current progress
     printf("Inserting word %lu of %lu\r", i, numberWords);
    linkedListInsert(&start, token);

    token = strtok(NULL, "\n");  
    i++;
  }

  for(node* current = start; current != NULL; current = current->next) {
    printf("%s,", current->str);
  }

  free(buffer);

  return 0;
}

int linkedListInsert(node **startIn, char *str) {
  // Create a new node
  node *new = (node *)malloc(sizeof(node));
  if(NULL == new) {
    return ERROR_MEMORY;
  }
  new->str = str;
  new->next = NULL;

  // Initialise the list if necessary
  if(*startIn == NULL) {
    *startIn = new;
    return 0;
  }

  node *start = *startIn;
  
  // Check if the node should be inserted as the start
  if(strcmp(start->str, str) > 0) {
    new->next = start;
    start = new;
    return 0;
  }

  // Scan through the list to find the correct
  // alphabetic position for str
  // Check if new should be placed *after* the current
  // node by checking if next->str after str
  node *current = NULL;
  for(current = start; NULL != current->next; current = current->next) {
    if(strcmp(current->next->str, str) > 0) {
      break;
    }
  }

  new->next = current->next;
  current->next = new;

  return 0;
}

int loadFileToMemory(char *fileName, char **bufferIn) {
  if(NULL == bufferIn) {
    return ERROR_NULLPOINTER;
  }

  // Open the file, or fail with an error
  FILE *pFile = fopen(fileName, "r");
  if(NULL == pFile) {
      return ERROR_OPEN;
  }

  // Determine the total file size by seeking to the end,
  // and getting the end position
  fseek(pFile, 0, SEEK_END);
  size_t lSize = ftell(pFile);
  rewind(pFile);

  // Allocate a buffer with enough space to store the entire
  // file, or fail with an error
  char *buffer = (char *)malloc(sizeof(char) * lSize);
  if(NULL == buffer) {
    fclose(pFile);
    return ERROR_MEMORY;   
  }

  // Read the entire file into memory, check that the entire
  // file has been read, otherwise an error has occured
  size_t result = fread(buffer, 1, lSize, pFile);
  if(result != lSize) {
      fclose(pFile);
      free(buffer);
      buffer = NULL;
      return ERROR_READ;
  }

  // Now close the file and return success
  *bufferIn = buffer;
  fclose(pFile);
  return SUCCESS;
}
