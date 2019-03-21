/* ######################################################
   # This is a modified version of Dr Neill Campbell's  #
   # file "neillsdl2.h", created by me. TJH             #
   ###################################################### */

#include <SDL.h>
#include <math.h>

#define CHARS_ACROSS 40
#define CHARS_DOWN 25

/* Font stuff */
typedef unsigned short fntrow;
#define FNTWIDTH (sizeof(fntrow)*8)
#define FNTHEIGHT 18
#define FNTCHARS 96
#define FNT1STCHAR 32

#define WWIDTH FNTWIDTH*CHARS_ACROSS
#define WHEIGHT FNTHEIGHT*CHARS_DOWN

#define SDL_8BITCOLOUR 256

#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

#define WHITE 255255255
#define BLACK 0
#define RED 255000000
#define GREEN 255000
#define BLUE 255
#define YELLOW 255255000
#define MAGENTA 255000255
#define CYAN 255255

struct SDL_Simplewin {
   SDL_bool finished;
   SDL_Window *win;
   SDL_Renderer *renderer;
   SDL_Texture *display;
};
typedef struct SDL_Simplewin SDL_Simplewin;

void Neill_SDL_Init(SDL_Simplewin *sw);
void Neill_SDL_Events(SDL_Simplewin *sw);
void Neill_SDL_SetDrawColour(SDL_Simplewin *sw, Uint8 r, Uint8 g, Uint8 b);
void Hosker_SDL_SetDrawColour(SDL_Simplewin *sw, long ebc);
void Neill_SDL_RenderFillCircle(SDL_Renderer *rend, int cx, int cy, int r);
void Neill_SDL_RenderDrawCircle(SDL_Renderer *rend, int cx, int cy, int r);
void Neill_SDL_DrawChar(SDL_Simplewin *sw, fntrow fontdata[FNTCHARS][FNTHEIGHT], unsigned char chr, int ox, int oy, long fg_colour, long bg_colour);
void draw_upper_dh(SDL_Simplewin *sw, fntrow fontdata[FNTCHARS][FNTHEIGHT], unsigned char chr, int ox, int oy, long fg_colour, long bg_colour);
void draw_lower_dh(SDL_Simplewin *sw, fntrow fontdata[FNTCHARS][FNTHEIGHT], unsigned char chr, int ox, int oy, long fg_colour, long bg_colour);
void Neill_SDL_DrawString(SDL_Simplewin *sw, fntrow fontdata[FNTCHARS][FNTHEIGHT], char *str, int ox, int oy);
void Neill_SDL_ReadFont(fntrow fontdata[FNTCHARS][FNTHEIGHT], char *fname);
void Neill_SDL_UpdateScreen(SDL_Simplewin *sw);
int unpack_colour_red(long ebc);
int unpack_colour_green(long ebc);
int unpack_colour_blue(long ebc);
