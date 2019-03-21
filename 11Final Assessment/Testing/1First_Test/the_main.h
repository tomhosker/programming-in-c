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
