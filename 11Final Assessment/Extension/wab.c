/*##########################################################
# A short program I wrote for transforming a plain text    #
# machine code file into a binary file.                    #
##########################################################*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHARS_ACROSS 40
#define CHARS_DOWN 25
#define GRID_SIZE CHARS_ACROSS*CHARS_DOWN
#define BUFFER_SIZE CHARS_ACROSS*CHARS_DOWN*10
#define NO_WIDTH 2
#define MACHINE_FILE "translated.txt"
#define BINARY_FILE "translated.m7"

void write_as_binary(void);

int main(void)
{
  write_as_binary();
  return(0);
}

void write_as_binary(void)
{
  FILE *mch;
  FILE *bin;
  char buffer[BUFFER_SIZE*(NO_WIDTH+1)];
  unsigned char second_buffer[BUFFER_SIZE];
  int count = 0;
  const char s[2] = " ";
  char *token;
  int u, v;
  int i;

  mch = fopen(MACHINE_FILE, "r");
  if(mch == NULL)
  {
    exit(-1);
  }
  if(fgets(buffer, BUFFER_SIZE*3, mch) == NULL)
  {
    printf("Error reading file.");
    return;
  }

  token = strtok(buffer, s);
  while(token != NULL)
  {
    if((token[0] >= 'a') && (token[0] <= 'f'))
    {
      u = token[0]-'a'+0xa;
    }
    else
    {
      u = token[0]-'0';
    }

    if((token[1] >= 'a') && (token[1] <= 'f'))
    {
      v = token[1]-'a'+0xa;
    }
    else
    {
      v = token[1]-'0';
    }
    second_buffer[count] = (16*u)+v;    

    token = strtok(NULL, s);
    count++;
  }

  bin = fopen(BINARY_FILE, "wb");
  if(bin == NULL)
  {
    exit(-1);
  }

  for(i = 0; i < BUFFER_SIZE; i++)
  {
    fwrite(second_buffer+i, sizeof(char), 1, bin);
  }
}
