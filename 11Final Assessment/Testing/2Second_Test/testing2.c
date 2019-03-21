#include "the_main.h"
#include <assert.h>

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
  unsigned char n;
  n = decode_ascii_code(129);
  assert(n == 1);
  n = decode_ascii_code(29);
  assert(n == 29);
  n = decode_non_ascii_code(129);
  assert(n == 1);
  n = decode_non_ascii_code(29);
  assert(n == (256+(29-128)));
  n = is_ascii_code('\0');
  assert(n == 1);
  n = is_ascii_code('z');
  assert(n == 1);
  n = is_ascii_code('\0'+1);
  assert(n == 1);
  n = is_ascii_code('\0'+1);
  assert(n == 1);
  n = is_ascii_code('\0'-1);
  assert(n == 0);
  n = is_ascii_code('z'-1);
  assert(n == 1);
  n = is_ascii_code('\0'+128);
  assert(n == 0);
  n = is_ascii_code('z'+128+1);
  assert(n == 0);
  n = is_ascii_code('z'+128-1);
  assert(n == 1);
}

void second_round(void)
{
  
}

void third_round(void)
{
  unsigned int n;
  n = decode_graphics_colour_code(3);
  assert(n == WHITE);
  n = decode_anfbc_code(3);
  assert(n == WHITE);
  n = is_anbgc_code(BLACK_BG);
  assert(n == 1);
  n = is_anbgc_code(BLACK_BG-1);
  assert(n == 0);
  n = is_anfgc_code(FIRST_ANFGC);
  assert(n == 1);
  n = is_anfgc_code(FIRST_ANFGC-1);
  assert(n == 0);
  n = is_anfgc_code(FIRST_ANFGC+1);
  assert(n == 1);
  n = is_anfgc_code(LAST_ANFGC);
  assert(n == 1);
  n = is_anfgc_code(LAST_ANFGC-1);
  assert(n == 1);
  n = is_anfgc_code(LAST_ANFGC+1);
  assert(n == 0);
  n = is_anfgc_code(RED_AN);
  assert(n == 1);
  n = is_anfgc_code(RED_GR);
  assert(n == 0);
  n = is_graphics_colour_code(FIRST_GR_CC);
  assert(n == 1);
  n = is_graphics_colour_code(FIRST_GR_CC-1);
  assert(n == 0);
  n = is_graphics_colour_code(FIRST_GR_CC+1);
  assert(n == 1);
  n = is_graphics_colour_code(LAST_GR_CC);
  assert(n == 1);
  n = is_graphics_colour_code(LAST_GR_CC-1);
  assert(n == 1);
  n = is_graphics_colour_code(LAST_GR_CC+1);
  assert(n == 0);
  n = is_graphics_colour_code(RED_AN);
  assert(n == 0);
  n = is_graphics_code(RED_GR);
  assert(n == 1);
  n = is_graphics_code(FIRST_GR);
  assert(n == 1);
  n = is_graphics_code(FIRST_GR-1);
  assert(n == 0);
  n = is_graphics_code(FIRST_GR+1);
  assert(n == 1);
  n = is_graphics_code(LAST_GR);
  assert(n == 1);
  n = is_graphics_code(LAST_GR-1);
  assert(n == 1);
  n = is_graphics_code(LAST_GR+1);
  assert(n == 0);
  n = is_graphics_code(RED_AN);
  assert(n == 0);
  n = is_graphics_code(RED_GR);
  assert(n == 1);
}

void fourth_round(void)
{
  int n;
  long g;
  long f = 555555555;
  long b = 333333333;

  n = toggle_hold_graphics(HOLD_GR, 0);
  assert(n == 1);
  n = toggle_hold_graphics(RELEASE_GR, 1);
  assert(n == 0);
  n = toggle_hold_graphics(3, 0);
  assert(n == 0);
  n = toggle_hold_graphics(3, 1);
  assert(n == 1);
  n = toggle_graphics_mode(SEPARATED_GR, 3);
  assert(n == SEPARATED);
  n = toggle_graphics_mode(CONTIGUOUS_GR, 3);
  assert(n == CONTIGUOUS);
  n = toggle_graphics_mode(RED_AN, 3);
  assert(n == OFF);
  n = toggle_graphics_mode(5, 3);
  assert(n == 3);
  n = toggle_dh_mode(DOUBLE_HEIGHT, SPACE, SPACE, SPACE, OFF);
  assert(n == UPPER);
  n = toggle_dh_mode(DOUBLE_HEIGHT, DOUBLE_HEIGHT, SPACE, SPACE, OFF);
  assert(n == LOWER);
  g = toggle_bg_colour(SPACE, b, f);
  assert(g == b);
  g = toggle_bg_colour(RED_AN, b, f);
  assert(g == b);
  g = toggle_bg_colour(NEW_BG, b, f);
  assert(g == f);
  g = toggle_bg_colour(BLACK_BG, b, f);
  assert(g == BLACK);
  g = toggle_fg_colour(SPACE, f);
  assert(g == f);
  g = toggle_fg_colour(RED_AN, f);
  assert(g == RED);
  g = toggle_fg_colour(RED_GR, f);
  assert(g == RED);
}

void fifth_round(void)
{
  unsigned char n;
  unsigned char c_above = 0;
  unsigned char c_next = 0;
  unsigned char c_above_next = 0;
  unsigned char m7file[3] = {3, 5, 7};

  n = toggle_c_above_next(1, m7file, c_above_next);
  assert(n == 0);
  n = toggle_c_next(1, m7file, c_next);
  assert(n == 7);
  n = toggle_c_above(1, m7file, c_above);
  assert(n == 0);
}

void sixth_round(void)
{
  
}

void seventh_round(void)
{
  
}
