#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hoskersdl2.h"
#include "controlcodes.h"

#define NORMAL_FONT_FILE "m7fixed.fnt"
#define CONTIGUOUS_GRAPHICS_FONT_FILE "sixels_c.fnt"
#define SEPARATED_GRAPHICS_FONT_FILE "sixels_s.fnt"

#define OFF 0
#define ON 1

#define CONTIGUOUS 1
#define SEPARATED 2

#define UPPER 1
#define LOWER 2

/* Takes the m7 array generated in "main", along with the
   font arrays, and prints an SDL window. */
void print_m7(unsigned char *m7file, SDL_Simplewin sw,
              fntrow fd[FNTCHARS][FNTHEIGHT],
              fntrow sixels_c[FNTCHARS][FNTHEIGHT],
              fntrow sixels_s[FNTCHARS][FNTHEIGHT]);

/* Subfunction of "print_m7". Updates "c_above". */
unsigned char toggle_c_above(int i, unsigned char *m7file,
                             unsigned char c_above);

/* Subfunction of "print_m7". Updates "c_next". */
unsigned char toggle_c_next(int i, unsigned char *m7file,
                            unsigned char c_next);

/* Subfunction of "print_m7". Updates "c_above_next". */
unsigned char toggle_c_above_next(int i,
                                  unsigned char *m7file,
                                  unsigned char c_above_next);

/* Subfunction of "print_m7". Updates "f". */
long toggle_fg_colour(unsigned char c, long f);

/* Subfunction of "print_m7". Updates "b". */
long toggle_bg_colour(unsigned char c, long b, long f);

/* Subfunction of "print_m7". Updates "f". */
int toggle_graphics_mode(unsigned char c,
                         int graphics_mode);

/* Subfunction of "print_m7". Updates "dh_mode". */
int toggle_dh_mode(unsigned char c, unsigned char c_above,
                   unsigned char c_next,
                   unsigned char c_above_next,
                   int dh_mode);

/* Subfunction of "print_m7". Updates "hold_graphics". */
int toggle_hold_graphics(unsigned char c,
                         int hold_graphics);

/* Subfunction of "toggle_graphics_mode". Determines
   whether "c" is a graphics control code. */
bool is_graphics_code(unsigned char c);

/* Used in various functions. Determines whether "c" is
   a graphics colour code or not. */
bool is_graphics_colour_code(unsigned char c);

/* Used in various functions. Determines whether "c" is
   an Alpha-Numeric ForeGround Colour code. */
bool is_anfgc_code(unsigned char c);

/* Used in various functions. Determines whether "c" is
   an Alpha-Numeric BackGround Colour code. */
bool is_anbgc_code(unsigned char c);

/* Subfunction of "toggle_fg_colour". Translates a
   control code, in this case an Alpha-Numeric
   Foreground/Background Colour code, into a nine-digit
   red-green-blue colour code. */
long decode_anfbc_code(unsigned char c);

/* Subfunction of "toggle_fg_colour". Translates a
   control code, in this case an graphics colour code,
   into a nine-digit red-green-blue colour code. */
long decode_graphics_colour_code(unsigned char c);

/* Subfunction of "print_m7". Takes a byte of graphics code
   and determines whether to send it to "graphics_parser",
   to print a blob of background colour, or to print a blob
   of foreground colour. */
void graphics_pre_parser(unsigned char c, SDL_Simplewin sw,
                         fntrow sixels_c[FNTCHARS][FNTHEIGHT],
                         fntrow sixels_s[FNTCHARS][FNTHEIGHT],
                         int x, int y, long f, long b,
                         int graphics_mode,
                         int hold_graphics);

/* Subfunction of "graphics_pre_parser". Takes a byte of
   graphics code and prints a graphics character. */
void graphics_parser(unsigned char c, SDL_Simplewin sw,
                     fntrow sixels_c[FNTCHARS][FNTHEIGHT],
                     fntrow sixels_s[FNTCHARS][FNTHEIGHT],
                     int x, int y, long f, long b,
                     int graphics_mode);

/* Subfunction of "print_m7". Prints half of a double-
   heighted character. */
void dh_parser(unsigned char c, SDL_Simplewin sw,
               fntrow fd[FNTCHARS][FNTHEIGHT], int x, int y,
               long f, long b, int dh_mode);

/* Subfunction of "print_m7". Prints a single-heighted
   character. */
void char_parser(unsigned char c, SDL_Simplewin sw,
                 fntrow fd[FNTCHARS][FNTHEIGHT],
                 int x, int y, long f, long b);

/* Used in various functions. Determines whether "c" is an
   ASCII code. */
bool is_ascii_code(unsigned char c);

/* Subfunction of "char_parser". Determines whether "c" is
   an ASCII code. */
bool is_non_ascii_code(unsigned char c);

/* Used in various function. Takes off 0x80 as necessary. */
unsigned char decode_ascii_code(unsigned char c);

/* Subfunction of "char_parser". Takes of 0x80. */
unsigned char decode_non_ascii_code(unsigned char c);

int main(int argc, char *argv[])
{
  SDL_Simplewin sw;
  fntrow fd[FNTCHARS][FNTHEIGHT];
  fntrow sixels_c[FNTCHARS][FNTHEIGHT];
  fntrow sixels_s[FNTCHARS][FNTHEIGHT];
  char buffer[(CHARS_ACROSS*CHARS_DOWN)+1];
  FILE *file;

  if(argc != 2)
  {
    exit(-1);
  }

  Neill_SDL_ReadFont(fd, NORMAL_FONT_FILE);
  Neill_SDL_ReadFont(sixels_c, CONTIGUOUS_GRAPHICS_FONT_FILE);
  Neill_SDL_ReadFont(sixels_s, SEPARATED_GRAPHICS_FONT_FILE);

  file = fopen(argv[1], "r");
  if(file == NULL)
  {
    exit(-1);
  }
  if(strcmp(fgets(buffer, (CHARS_ACROSS*CHARS_DOWN)+1, file),
     buffer) != 0)
  {
    printf("Error reading file.\n");
    return(0);
  }

  /* Neill's code for making an SDL window, adapted. */
  Neill_SDL_Init(&sw);
  do{
     SDL_Delay(1);
     print_m7((unsigned char *)buffer, sw, fd, sixels_c,
              sixels_s);
     Neill_SDL_UpdateScreen(&sw);
     Neill_SDL_Events(&sw);
  }while(!sw.finished);
  atexit(SDL_Quit);

  return(0);
}

void print_m7(unsigned char *m7file, SDL_Simplewin sw,
              fntrow fd[FNTCHARS][FNTHEIGHT],
              fntrow sixels_c[FNTCHARS][FNTHEIGHT],
              fntrow sixels_s[FNTCHARS][FNTHEIGHT])
{
  unsigned char c;
  unsigned char c_above = 0x00;
  unsigned char c_next = 0x00;
  unsigned char c_above_next = 0x00;
  long f = WHITE; long b = BLACK;
  int graphics_mode = OFF;
  int dh_mode = OFF;
  int hold_graphics = OFF;
  int i;
  int x = 0; int y = 0;

  /* Walk through each character. */
  for(i = 0; i <= (CHARS_ACROSS*CHARS_DOWN); i++)
  {
    c = m7file[i];

    /* Update various variables. */
    c_above = toggle_c_above(i, m7file, c_above);
    c_next = toggle_c_next(i, m7file, c_next);
    c_above_next = toggle_c_above_next(i, m7file, c_above_next);
    f = toggle_fg_colour(c, f);
    b = toggle_bg_colour(c, b, f);
    graphics_mode = toggle_graphics_mode(c, graphics_mode);
    hold_graphics = toggle_hold_graphics(c, hold_graphics);

    /* Parse either graphics, double heighted text, or
       normal text, as appropriate. */
    if(graphics_mode != OFF)
    {
      graphics_pre_parser(c, sw, sixels_c, sixels_s, x, y,
                          f, b, graphics_mode, hold_graphics);
    }
    else if(dh_mode != OFF)
    {
      dh_parser(c, sw, fd, x, y, f, b, dh_mode);
    }
    else
    {
      char_parser(c, sw, fd, x, y, f, b);
    }

    /* Either end the line or move right, as appropriate. */
    if((i%CHARS_ACROSS) == (CHARS_ACROSS-1))
    {
      f = WHITE; b = BLACK;
      x = 0; y = y+FNTHEIGHT;
      dh_mode = OFF; graphics_mode = OFF;
    }
    else
    {
      dh_mode = toggle_dh_mode(c, c_above, c_next,
                               c_above_next, dh_mode);
      x = x+FNTWIDTH;
    }
  }
}

long toggle_fg_colour(unsigned char c, long f)
{
  if(is_anfgc_code(c))
  {
    f = decode_anfbc_code(c);
  }
  else if(is_graphics_colour_code(c))
  {
    f = decode_graphics_colour_code(c);
  }
  return(f);
}

long toggle_bg_colour(unsigned char c, long b, long f)
{
  if(is_anbgc_code(c))
  {
    if(c == BLACK_BG)
    {
      b = BLACK;
    }
    else
    {
      b = f;
    }
  }
  return(b);
}

unsigned char toggle_c_above(int i, unsigned char *m7file,
                             unsigned char c_above)
{
  if(i >= CHARS_ACROSS)
  {
    c_above = m7file[i-CHARS_ACROSS];
  }
  return(c_above);
}

unsigned char toggle_c_next(int i, unsigned char *m7file,
                            unsigned char c_next)
{
  if(i != (CHARS_ACROSS*CHARS_DOWN))
  {
    c_next = m7file[i+1];
  }
  return(c_next);
}

unsigned char toggle_c_above_next(int i,
                                  unsigned char *m7file,
                                  unsigned char c_above_next)
{
  if(i >= CHARS_ACROSS)
  {
    c_above_next = m7file[i-CHARS_ACROSS+1];
  }
  return(c_above_next);
}

int toggle_graphics_mode(unsigned char c, int graphics_mode)
{
  if(is_graphics_code(c) == true)
  {
    if(c == SEPARATED_GR)
    {
      return(SEPARATED);
    }
    else
    {
      return(CONTIGUOUS);
    }
  }
  else if(is_anfgc_code(c) == true)
  {
    return(OFF);
  }
  else if(is_anbgc_code(c) == true)
  {
    return(OFF);
  }
  else
  {
    return(graphics_mode);
  }
}

int toggle_dh_mode(unsigned char c, unsigned char c_above,
                   unsigned char c_next,
                   unsigned char c_above_next, int dh_mode)
{
  if(c == SINGLE_HEIGHT)
  {
    return(OFF);
  }
  else if(c == DOUBLE_HEIGHT)
  {
    if(c_above == DOUBLE_HEIGHT)
    {
      return(LOWER);
    }
    else
    {
      return(UPPER);
    }
  }
  else if((c == SPACE) && (c_above == DOUBLE_HEIGHT)
          && (c_next == c_above_next))
  {
    return(LOWER);
  }
  else
  {
    return(dh_mode);
  }
}

int toggle_hold_graphics(unsigned char c, int hold_graphics)
{
  if(c == HOLD_GR)
  {
    return(ON);
  }
  else if(c == RELEASE_GR)
  {
    return(OFF);
  }
  else
  {
    return(hold_graphics);
  }
}

bool is_graphics_code(unsigned char c)
{
  if((c >= FIRST_GR) && (c <= LAST_GR))
  {
    return(true);
  }
  else if((c == HOLD_GR) || (c == RELEASE_GR))
  {
    return(true);
  }
  else
  {
    return(false);
  }
}

bool is_graphics_colour_code(unsigned char c)
{
  if((c >= FIRST_GR_CC) && (c <= LAST_GR_CC))
  {
    return(true);
  }
  else
  {
    return(false);
  }
}

bool is_anfgc_code(unsigned char c)
{
  if((c >= FIRST_ANFGC) && (c <= LAST_ANFGC))
  {
    return(true);
  }
  else
  {
    return(false);
  }
}

bool is_anbgc_code(unsigned char c)
{
  if((c == BLACK_BG) || (c == NEW_BG))
  {
    return(true);
  }
  else
  {
    return(false);
  }
}

long decode_anfbc_code(unsigned char c)
{
  if(c == RED_AN)
  {
    return(RED);
  }
  else if(c == GREEN_AN)
  {
    return(GREEN);
  }
  else if(c == YELLOW_AN)
  {
    return(YELLOW);
  }
  else if(c == BLUE_AN)
  {
    return(BLUE);
  }
  else if(c == MAGENTA_AN)
  {
    return(MAGENTA);
  }
  else if(c == CYAN_AN)
  {
    return(CYAN);
  }
  else if(c == WHITE_AN)
  {
    return(WHITE);
  }
  else
  {
    return(WHITE);
  }
}

long decode_graphics_colour_code(unsigned char c)
{
  if(c == RED_GR)
  {
    return(RED);
  }
  else if(c == GREEN_GR)
  {
    return(GREEN);
  }
  else if(c == YELLOW_GR)
  {
    return(YELLOW);
  }
  else if(c == BLUE_GR)
  {
    return(BLUE);
  }
  else if(c == MAGENTA_GR)
  {
    return(MAGENTA);
  }
  else if(c == CYAN_GR)
  {
    return(CYAN);
  }
  else if(c == WHITE_GR)
  {
    return(WHITE);
  }
  else
  {
    return(WHITE);
  }
}

void graphics_pre_parser(unsigned char c, SDL_Simplewin sw,
                         fntrow sixels_c[FNTCHARS][FNTHEIGHT],
                         fntrow sixels_s[FNTCHARS][FNTHEIGHT],
                         int x, int y, long f, long b,
                         int graphics_mode, int hold_graphics)
{
  if(c >= FIRST_ASCII_A)
  {
    graphics_parser(c, sw, sixels_c, sixels_s, x, y, f, b,
                    graphics_mode);
  }
  else if(is_graphics_colour_code(c))
  {
    if(hold_graphics == OFF)
    {
      Neill_SDL_DrawChar(&sw, sixels_c, ' ', x, y, f, b);
    }
    else
    {
      Neill_SDL_DrawChar(&sw, sixels_c, ' ', x, y, f, f);
    }
  }
  else if(c == HOLD_GR)
  {
    Neill_SDL_DrawChar(&sw, sixels_c, ' ', x, y, f, f);
  }
  else
  {
    Neill_SDL_DrawChar(&sw, sixels_c, ' ', x, y, f, b);
  }
}

void graphics_parser(unsigned char c, SDL_Simplewin sw,
                     fntrow sixels_c[FNTCHARS][FNTHEIGHT],
                     fntrow sixels_s[FNTCHARS][FNTHEIGHT],
                     int x, int y, long f, long b,
                     int graphics_mode)
{
  c = c-FIRST_CONTROL;
  if(graphics_mode == CONTIGUOUS)
  {
    Neill_SDL_DrawChar(&sw, sixels_c, c, x, y, f, b);
  }
  else
  {
    Neill_SDL_DrawChar(&sw, sixels_s, c, x, y, f, b);
  }
}

void dh_parser(unsigned char c, SDL_Simplewin sw,
               fntrow fd[FNTCHARS][FNTHEIGHT], int x,
               int y, long f, long b, int dh_mode)
{
  unsigned char c_dash;

  if(is_ascii_code(c) == true)
  {
    c_dash = decode_ascii_code(c);
    if(dh_mode == LOWER)
    {
      draw_lower_dh(&sw, fd, c_dash, x, y, f, b);
    }
    else
    {
      draw_upper_dh(&sw, fd, c_dash, x, y, f, b);
    }
  }
  else
  {
    Neill_SDL_DrawChar(&sw, fd, ' ', x, y, f, b);
  }
}

void char_parser(unsigned char c, SDL_Simplewin sw,
                 fntrow fd[FNTCHARS][FNTHEIGHT],
                 int x, int y, long f, long b)
{
  if(is_ascii_code(c))
  {
    c = decode_ascii_code(c);
    Neill_SDL_DrawChar(&sw, fd, c, x, y, f, b);
  }
  else if(is_non_ascii_code(c))
  {
    c = decode_non_ascii_code(c);
    Neill_SDL_DrawChar(&sw, fd, c, x, y, f, b);
  }
  else
  {
    /* Unknown character; print a space. */
    Neill_SDL_DrawChar(&sw, fd, ' ', x, y, f, b);
  }
}

bool is_ascii_code(unsigned char c)
{
  if(c < FIRST_CONTROL)
  {
    return(true);
  }
  else if((c >= FIRST_ASCII_A) && (c <= LAST_ASCII_A))
  {
    return(true);
  }
  else if((c >= FIRST_ASCII_B) && (c <= LAST_ASCII_B))
  {
    return(true);
  }
  else
  {
    return(false);
  }
}

bool is_non_ascii_code(unsigned char c)
{
  if((c >= FIRST_NON_ASCII_A) && (c <= LAST_NON_ASCII_A))
  {
    return(true);
  }
  else if(c >= FIRST_NON_ASCII_B)
  {
    return(true);
  }
  else
  {
    return(false);
  }
}

unsigned char decode_ascii_code(unsigned char c)
{
  if(c >= FIRST_CONTROL)
  {
    return(c-FIRST_CONTROL);
  }
  else
  {
    return(c);
  }
}

unsigned char decode_non_ascii_code(unsigned char c)
{
  return(c-FIRST_CONTROL);
}
