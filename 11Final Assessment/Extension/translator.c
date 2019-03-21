/*##########################################################
############################################################
###################### A Program in C ######################
################## to Allow for the More ###################
###################### Rapid Creation ######################
#################### of Teletext Pages #####################
########################## v 1.6 ###########################
############################################################
###################### by TOM HOSKER #######################
############################################################
####################### 22 Jan 2018 ########################
############################################################
############# nisi Dominus aedificaverit domum #############
############################################################
############################################################
############### Znl gur fbhy bs Qnivq Pbbx, ################
################### Puvrs Bssvpre Eblny ####################
################# Syrrg Nhkvyvnel Freivpr, #################
##################### jevgur va ntbal ######################
################## orgjrra Fngna'f grrgu. ##################
############################################################
##########################################################*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "controlstrings.h"

#define CHARS_ACROSS 40
#define CHARS_DOWN 25
#define GRID_SIZE CHARS_ACROSS*CHARS_DOWN
#define BUFFER_SIZE CHARS_ACROSS*CHARS_DOWN*10

void translate(unsigned char *assembly, char *machine);

void command_parser(unsigned char *token, FILE *file, int count);

void weirdness_parser(unsigned char *token, FILE *file);

void extra_symbols_parser(unsigned char *token, FILE *file);

void sixels_parser(unsigned char *token, FILE *file);

int main(int argc, char *argv[])
{
  unsigned char buffer[BUFFER_SIZE];
  unsigned char buffer_dash[BUFFER_SIZE];
  unsigned char *buffer_ddash;
  FILE *file;

  buffer[0] = '\0';
  buffer_dash[0] = '\0';

  if(argc != 2)
  {
    exit(-1);
  }

  file = fopen(argv[1], "r");
  if(file == NULL)
  {
    exit(-1);
  }
  while(fgets((char*)buffer_dash, BUFFER_SIZE, file) != NULL)
  {
    buffer_ddash = (unsigned char*)strtok((char*)buffer_dash, "\n");
    strcat((char*)buffer, " ");
    strcat((char*)buffer, (char*)buffer_ddash);
  }

  translate(buffer, "translated.txt");

  fclose(file);
  return(0);
}

void translate(unsigned char *assembly, char *machine)
{
  FILE *file;
  int count = 0;
  unsigned char *token;
  const char s[2] = " ";

  file = fopen(machine, "w");
  if(file == NULL)
  {
    exit(-1);
  }

  token = (unsigned char*)strtok((char*)assembly, s);
  
  while(token != NULL)
  {
    if(strlen((char*)token) == 1)
    {
      token[0] = token[0]+0x80;
      fprintf(file, "%x ", (int)token[0]);
    }
    else if((token[0] == 'S') && (token[2] == 'X'))
    {
      sixels_parser(token, file);
    }
    else if(strcmp((char*)token, "NEWLINE") == 0)
    {
      command_parser(token, file, count);
      count = count-(count%CHARS_ACROSS)+CHARS_ACROSS-1;
    }
    else
    {
      command_parser(token, file, count);
    }

    token = (unsigned char*)strtok(NULL, s);
    count++;
  }
}

void command_parser(unsigned char *token, FILE *file, int count)
{
  if(strcmp((char*)token, "SPACE") == 0)
  {
    fprintf(file, "%s ", SPACE_STR);
  }
  else if(strcmp((char*)token, "NEWLINE") == 0)
  {
    while(count%CHARS_ACROSS != 0)
    {
      fprintf(file, "%s ", "a0");
      count++;
    }
  }
  else if(strcmp((char*)token, "END") == 0)
  {
    while(GRID_SIZE-count > 0)
    {
      fprintf(file, "%s ", "a0");
      count++;
    }
  }
  else
  {
    weirdness_parser(token, file);
  }
}

void weirdness_parser(unsigned char *token, FILE *file)
{
  if(strcmp((char*)token, "REDAN") == 0)
  {
    fprintf(file, "%s ", REDAN_STR);
  }
  else if(strcmp((char*)token, "GREENAN") == 0)
  {
    fprintf(file, "%s ", GREENAN_STR);
  }
  else if(strcmp((char*)token, "YELLOWAN") == 0)
  {
    fprintf(file, "%s ", YELLOWAN_STR);
  }
  else if(strcmp((char*)token, "BLUEAN") == 0)
  {
    fprintf(file, "%s ", BLUEAN_STR);
  }
  else if(strcmp((char*)token, "MAGENTAAN") == 0)
  {
    fprintf(file, "%s ", MAGENTAAN_STR);
  }
  else if(strcmp((char*)token, "CYANAN") == 0)
  {
    fprintf(file, "%s ", CYANAN_STR);
  }
  else if(strcmp((char*)token, "WHITEAN") == 0)
  {
    fprintf(file, "%s ", WHITEAN_STR);
  }
  else if(strcmp((char*)token, "SINGLEHT") == 0)
  {
    fprintf(file, "%s ", SINGLEHT_STR);
  }
  else if(strcmp((char*)token, "DOUBLEHT") == 0)
  {
    fprintf(file, "%s ", DOUBLEHT_STR);
  }
  else if(strcmp((char*)token, "REDGR") == 0)
  {
    fprintf(file, "%s ", REDGR_STR);
  }
  else if(strcmp((char*)token, "GREENGR") == 0)
  {
    fprintf(file, "%s ", GREENGR_STR);
  }
  else if(strcmp((char*)token, "YELLOWGR") == 0)
  {
    fprintf(file, "%s ", YELLOWGR_STR);
  }
  else if(strcmp((char*)token, "BLUEGR") == 0)
  {
    fprintf(file, "%s ", BLUEGR_STR);
  }
  else if(strcmp((char*)token, "MAGENTAGR") == 0)
  {
    fprintf(file, "%s ", MAGENTAGR_STR);
  }
  else if(strcmp((char*)token, "CYANGR") == 0)
  {
    fprintf(file, "%s ", CYANGR_STR);
  }
  else if(strcmp((char*)token, "WHITEGR") == 0)
  {
    fprintf(file, "%s ", WHITEGR_STR);
  }
  else if(strcmp((char*)token, "CONTIGR") == 0)
  {
    fprintf(file, "%s ", CONTIGR_STR);
  }
  else if(strcmp((char*)token, "SEPARGR") == 0)
  {
    fprintf(file, "%s ", SEPARGR_STR);
  }
  else if(strcmp((char*)token, "BLKBACK") == 0)
  {
    fprintf(file, "%s ", BLKBACK_STR);
  }
  else if(strcmp((char*)token, "NEWBACK") == 0)
  {
    fprintf(file, "%s ", NEWBACK_STR);
  }
  else if(strcmp((char*)token, "HOLDGR") == 0)
  {
    fprintf(file, "%s ", HOLDGR_STR);
  }
  else if(strcmp((char*)token, "RELSGR") == 0)
  {
    fprintf(file, "%s ", RELSGR_STR);
  }
  else
  {
    extra_symbols_parser(token, file);
  }
}

void extra_symbols_parser(unsigned char *token, FILE *file)
{
  if(strcmp((char*)token, "QUARTER") == 0)
  {
    fprintf(file, "%s ", QUARTER_STR);
  }
  else if(strcmp((char*)token, "HALF") == 0)
  {
    fprintf(file, "%s ", HALF_STR);
  }
  else if(strcmp((char*)token, "THREEQUARTERS") == 0)
  {
    fprintf(file, "%s ", THREEQUARTERS_STR);
  }
  else if(strcmp((char*)token, "LEFT") == 0)
  {
    fprintf(file, "%s ", LEFT_STR);
  }
  else if(strcmp((char*)token, "RIGHT") == 0)
  {
    fprintf(file, "%s ", RIGHT_STR);
  }
  else if(strcmp((char*)token, "UP") == 0)
  {
    fprintf(file, "%s ", UP_STR);
  }
  else if(strcmp((char*)token, "OBELUS") == 0)
  {
    fprintf(file, "%s ", OBELUS_STR);
  }
  else if(strcmp((char*)token, "BAR") == 0)
  {
    fprintf(file, "%s ", BAR_STR);
  }
  else if(strcmp((char*)token, "POUND") == 0)
  {
    fprintf(file, "%s ", POUND_STR);
  }
  else if(strcmp((char*)token, "HYPHEN") == 0)
  {
    fprintf(file, "%s ", HYPHEN_STR);
  }
  else if(strcmp((char*)token, "BLOCK") == 0)
  {
    fprintf(file, "%s ", BLOCK_STR);
  }
  else
  {
    fprintf(file, "%s ", SPACE_STR);
  }
}

void sixels_parser(unsigned char *token, FILE *file)
{
  if(strcmp((char*)token, "SIX000000") == 0)
  {
    fprintf(file, "%s ", S000000);
  }
  else if(strcmp((char*)token, "SIX000001") == 0)
  {
    fprintf(file, "%s ", S000001);
  }
  else if(strcmp((char*)token, "SIX000010") == 0)
  {
    fprintf(file, "%s ", S000010);
  }
  else if(strcmp((char*)token, "SIX000011") == 0)
  {
    fprintf(file, "%s ", S000011);
  }
  else if(strcmp((char*)token, "SIX000100") == 0)
  {
    fprintf(file, "%s ", S000100);
  }
  else if(strcmp((char*)token, "SIX000101") == 0)
  {
    fprintf(file, "%s ", S000101);
  }
  else if(strcmp((char*)token, "SIX000110") == 0)
  {
    fprintf(file, "%s ", S000110);
  }
  else if(strcmp((char*)token, "SIX000111") == 0)
  {
    fprintf(file, "%s ", S000111);
  }
  else if(strcmp((char*)token, "SIX001000") == 0)
  {
    fprintf(file, "%s ", S001000);
  }
  else if(strcmp((char*)token, "SIX001001") == 0)
  {
    fprintf(file, "%s ", S001001);
  }
  else if(strcmp((char*)token, "SIX001010") == 0)
  {
    fprintf(file, "%s ", S001010);
  }
  else if(strcmp((char*)token, "SIX001011") == 0)
  {
    fprintf(file, "%s ", S001011);
  }
  else if(strcmp((char*)token, "SIX001100") == 0)
  {
    fprintf(file, "%s ", S001100);
  }
  else if(strcmp((char*)token, "SIX001101") == 0)
  {
    fprintf(file, "%s ", S001101);
  }
  else if(strcmp((char*)token, "SIX001110") == 0)
  {
    fprintf(file, "%s ", S001110);
  }
  else if(strcmp((char*)token, "SIX001111") == 0)
  {
    fprintf(file, "%s ", S001111);
  }
  else if(strcmp((char*)token, "SIX010000") == 0)
  {
    fprintf(file, "%s ", S010000);
  }
  else if(strcmp((char*)token, "SIX010001") == 0)
  {
    fprintf(file, "%s ", S010001);
  }
  else if(strcmp((char*)token, "SIX010010") == 0)
  {
    fprintf(file, "%s ", S010010);
  }
  else if(strcmp((char*)token, "SIX010011") == 0)
  {
    fprintf(file, "%s ", S010011);
  }
  else if(strcmp((char*)token, "SIX010100") == 0)
  {
    fprintf(file, "%s ", S010100);
  }
  else if(strcmp((char*)token, "SIX010101") == 0)
  {
    fprintf(file, "%s ", S010101);
  }
  else if(strcmp((char*)token, "SIX010110") == 0)
  {
    fprintf(file, "%s ", S010110);
  }
  else if(strcmp((char*)token, "SIX010111") == 0)
  {
    fprintf(file, "%s ", S010111);
  }
  else if(strcmp((char*)token, "SIX011000") == 0)
  {
    fprintf(file, "%s ", S011000);
  }
  else if(strcmp((char*)token, "SIX011001") == 0)
  {
    fprintf(file, "%s ", S011001);
  }
  else if(strcmp((char*)token, "SIX011010") == 0)
  {
    fprintf(file, "%s ", S011010);
  }
  else if(strcmp((char*)token, "SIX011011") == 0)
  {
    fprintf(file, "%s ", S011011);
  }
  else if(strcmp((char*)token, "SIX011100") == 0)
  {
    fprintf(file, "%s ", S011100);
  }
  else if(strcmp((char*)token, "SIX011101") == 0)
  {
    fprintf(file, "%s ", S011101);
  }
  else if(strcmp((char*)token, "SIX011110") == 0)
  {
    fprintf(file, "%s ", S011110);
  }
  else if(strcmp((char*)token, "SIX011111") == 0)
  {
    fprintf(file, "%s ", S011111);
  }
  else if(strcmp((char*)token, "SIX100000") == 0)
  {
    fprintf(file, "%s ", S100000);
  }
  else if(strcmp((char*)token, "SIX100001") == 0)
  {
    fprintf(file, "%s ", S100001);
  }
  else if(strcmp((char*)token, "SIX100010") == 0)
  {
    fprintf(file, "%s ", S100010);
  }
  else if(strcmp((char*)token, "SIX100011") == 0)
  {
    fprintf(file, "%s ", S100011);
  }
  else if(strcmp((char*)token, "SIX100100") == 0)
  {
    fprintf(file, "%s ", S100100);
  }
  else if(strcmp((char*)token, "SIX100101") == 0)
  {
    fprintf(file, "%s ", S100101);
  }
  else if(strcmp((char*)token, "SIX100110") == 0)
  {
    fprintf(file, "%s ", S100110);
  }
  else if(strcmp((char*)token, "SIX100111") == 0)
  {
    fprintf(file, "%s ", S100111);
  }
  else if(strcmp((char*)token, "SIX101000") == 0)
  {
    fprintf(file, "%s ", S101000);
  }
  else if(strcmp((char*)token, "SIX101001") == 0)
  {
    fprintf(file, "%s ", S101001);
  }
  else if(strcmp((char*)token, "SIX101010") == 0)
  {
    fprintf(file, "%s ", S101010);
  }
  else if(strcmp((char*)token, "SIX101011") == 0)
  {
    fprintf(file, "%s ", S101011);
  }
  else if(strcmp((char*)token, "SIX101100") == 0)
  {
    fprintf(file, "%s ", S101100);
  }
  else if(strcmp((char*)token, "SIX101101") == 0)
  {
    fprintf(file, "%s ", S101101);
  }
  else if(strcmp((char*)token, "SIX101110") == 0)
  {
    fprintf(file, "%s ", S101110);
  }
  else if(strcmp((char*)token, "SIX101111") == 0)
  {
    fprintf(file, "%s ", S101111);
  }
  else if(strcmp((char*)token, "SIX110000") == 0)
  {
    fprintf(file, "%s ", S110000);
  }
  else if(strcmp((char*)token, "SIX110001") == 0)
  {
    fprintf(file, "%s ", S110001);
  }
  else if(strcmp((char*)token, "SIX110010") == 0)
  {
    fprintf(file, "%s ", S110010);
  }
  else if(strcmp((char*)token, "SIX110011") == 0)
  {
    fprintf(file, "%s ", S110011);
  }
  else if(strcmp((char*)token, "SIX110100") == 0)
  {
    fprintf(file, "%s ", S110100);
  }
  else if(strcmp((char*)token, "SIX110101") == 0)
  {
    fprintf(file, "%s ", S110101);
  }
  else if(strcmp((char*)token, "SIX110110") == 0)
  {
    fprintf(file, "%s ", S110110);
  }
  else if(strcmp((char*)token, "SIX110111") == 0)
  {
    fprintf(file, "%s ", S110111);
  }
  else if(strcmp((char*)token, "SIX111000") == 0)
  {
    fprintf(file, "%s ", S111000);
  }
  else if(strcmp((char*)token, "SIX111001") == 0)
  {
    fprintf(file, "%s ", S111001);
  }
  else if(strcmp((char*)token, "SIX111010") == 0)
  {
    fprintf(file, "%s ", S111010);
  }
  else if(strcmp((char*)token, "SIX111011") == 0)
  {
    fprintf(file, "%s ", S111011);
  }
  else if(strcmp((char*)token, "SIX111100") == 0)
  {
    fprintf(file, "%s ", S111100);
  }
  else if(strcmp((char*)token, "SIX111101") == 0)
  {
    fprintf(file, "%s ", S111101);
  }
  else if(strcmp((char*)token, "SIX111110") == 0)
  {
    fprintf(file, "%s ", S111110);
  }
  else if(strcmp((char*)token, "SIX111111") == 0)
  {
    fprintf(file, "%s ", S111111);
  }
  else
  {
    fprintf(file, "%s ", S000000);
  }
}
