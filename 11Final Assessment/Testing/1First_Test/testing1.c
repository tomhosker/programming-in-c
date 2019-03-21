#include "the_main.h"

void first_round(void);

void second_round(void);

void third_round(void);

void fourth_round(void);

void fifth_round(void);

void sixth_round(void);

void seventh_round(void);

int main(void)
{
  first_round();
  second_round();
  third_round();
  fourth_round();
  fifth_round();
  sixth_round();
  seventh_round();

  printf("Tests passed!\n");
  return(0);
}

void first_round(void)
{
  /* decode_non_ascii_code("bird");
  decode_non_ascii_code(300); */
  decode_ascii_code(129);
  decode_ascii_code(29);
  /* is_non_ascii_code("!£%^&*()"); */
  is_ascii_code(130);
}

void second_round(void)
{
  SDL_Simplewin sw;
  fntrow fd[FNTCHARS][FNTHEIGHT];
  fntrow sixels_c[FNTCHARS][FNTHEIGHT];
  fntrow sixels_s[FNTCHARS][FNTHEIGHT];
  int x = 1;
  int y = 2;
  long f = 333333333;
  long b = 333333333;
  int dh_mode = 1;
  int graphics_mode = 0;
  int hold_graphics = 1;

  Neill_SDL_ReadFont(fd, NORMAL_FONT_FILE);
  Neill_SDL_ReadFont(sixels_c, CONTIGUOUS_GRAPHICS_FONT_FILE);
  Neill_SDL_ReadFont(sixels_s, SEPARATED_GRAPHICS_FONT_FILE);

  char_parser(3, sw, fd, x, y, f, b);
  /* char_parser(sw, 3, fd, x, y, f, b); */
  char_parser(3, sw, fd, b, f, y, x);

  dh_parser(3, sw, fd, x, y, f, b, dh_mode);
  /* dh_parser(sw, 3, fd, x, y, f, b, dh_mode); */
  dh_parser(3, sw, fd, dh_mode, b, f, y, x);

  graphics_parser(3, sw, sixels_c, sixels_s, x, y, f, b, graphics_mode);
  /* graphics_parser(sw, 3, sixels_c, sixels_s, x, y, f, b, graphics_mode); */
  graphics_parser(3, sw, sixels_c, sixels_s, graphics_mode, b, f, y, x);

  graphics_pre_parser(3, sw, sixels_c, sixels_s, x, y, f, b, graphics_mode, hold_graphics);
  /* graphics_pre_parser(3, sw, sixels_c, sixels_s, x, y, f, b, graphics_mode, hold_graphics); */
  graphics_pre_parser(3, sw, sixels_c, sixels_s, hold_graphics, graphics_mode, b, f, y, x);
}

void third_round(void)
{
  decode_graphics_colour_code(3);
  decode_anfbc_code(3);
  is_anbgc_code(3);
  is_anfgc_code(3);
  is_graphics_colour_code(3);
  is_graphics_code(3);
}

void fourth_round(void)
{
  int hold_graphics = 0;
  int graphics_mode = 1;
  int dh_mode = 0;
  int c_above = 5;
  int c_next = 7;
  int c_above_next = 11;
  long f = 333333333;
  long b = 333333333;

  toggle_hold_graphics(3, hold_graphics);
  toggle_dh_mode(3, c_above, c_next, c_above_next, dh_mode);
  toggle_graphics_mode(3, graphics_mode);
  toggle_bg_colour(3, b, f);
  toggle_fg_colour(3, f);
}

void fifth_round(void)
{
  int i = 3;
  unsigned char c_above = 0;
  unsigned char c_next = 0;
  unsigned char c_above_next = 0;
  unsigned char m7file[3] = {0, 1, 2};

  toggle_c_above_next(i, m7file, c_above_next);
  toggle_c_next(i, m7file, c_next);
  toggle_c_above(i, m7file, c_above);
}

void sixth_round(void)
{
  unsigned char m7file[3] = {0, 1, 2};
  SDL_Simplewin sw;
  fntrow fd[FNTCHARS][FNTHEIGHT];
  fntrow sixels_c[FNTCHARS][FNTHEIGHT];
  fntrow sixels_s[FNTCHARS][FNTHEIGHT];

  Neill_SDL_ReadFont(fd, NORMAL_FONT_FILE);
  Neill_SDL_ReadFont(sixels_c, CONTIGUOUS_GRAPHICS_FONT_FILE);
  Neill_SDL_ReadFont(sixels_s, SEPARATED_GRAPHICS_FONT_FILE);

  print_m7(m7file, sw, fd, sixels_c, sixels_s);
}

void seventh_round(void)
{
  char buffer[(CHARS_ACROSS*CHARS_DOWN)+1];
  FILE *file;

  file = fopen("kremlin.mp4", "r");
  if(file == NULL)
  {
    exit(-1);
  }

  if(strcmp(fgets(buffer, (CHARS_ACROSS*CHARS_DOWN)+1, file),
     buffer) != 0)
  {
    printf("Error reading file.\n");
  }
}
