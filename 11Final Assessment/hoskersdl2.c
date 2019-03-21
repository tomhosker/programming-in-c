/* ######################################################
   # This is a modified version of Dr Neill Campbell's  #
   # file "neillsdl2.c", created by me. TJH             #
   ###################################################### */

#include "hoskersdl2.h"

void Neill_SDL_Init(SDL_Simplewin *sw)
{

   if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      fprintf(stderr, "\nUnable to initialize SDL:  %s\n", SDL_GetError());
      SDL_Quit();
      exit(1);
   } 

   sw->finished = 0;
   
   sw->win= SDL_CreateWindow("SDL Window",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          WWIDTH, WHEIGHT,
                          SDL_WINDOW_SHOWN);
   if(sw->win == NULL){
      fprintf(stderr, "\nUnable to initialize SDL Window:  %s\n", SDL_GetError());
      SDL_Quit();
      exit(1);
   }

   sw->renderer = SDL_CreateRenderer(sw->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
   if(sw->renderer == NULL){
      fprintf(stderr, "\nUnable to initialize SDL Renderer:  %s\n", SDL_GetError());
      SDL_Quit();
      exit(1);
   }

   SDL_SetRenderDrawBlendMode(sw->renderer,SDL_BLENDMODE_BLEND);

   /* Create texture for display */
   sw->display = SDL_CreateTexture(sw->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WWIDTH, WHEIGHT);
   if(sw->display == NULL){
      fprintf(stderr, "\nUnable to initialize SDL texture:  %s\n", SDL_GetError());
      SDL_Quit();
      exit(1);
   }
   SDL_SetRenderTarget(sw->renderer, sw->display);

   /* Clear screen, & set draw colour to black */
   SDL_SetRenderDrawColor(sw->renderer, 0, 0, 0, 255);
   SDL_RenderClear(sw->renderer);

}

/* Housekeeping to do with the render buffer & updating the screen */
void Neill_SDL_UpdateScreen(SDL_Simplewin *sw)
{
   SDL_SetRenderTarget(sw->renderer, NULL);
   SDL_RenderCopy(sw->renderer, sw->display, NULL, NULL);
   SDL_RenderPresent(sw->renderer);
   SDL_SetRenderTarget(sw->renderer, sw->display);
}

/* Gobble all events & ignore most */
void Neill_SDL_Events(SDL_Simplewin *sw)
{
   SDL_Event event;
   while(SDL_PollEvent(&event)) 
   {      
       switch (event.type){
          case SDL_QUIT:
          case SDL_MOUSEBUTTONDOWN:
          case SDL_KEYDOWN:
             sw->finished = 1;
       }
    }
}

/* Trivial wrapper to avoid complexities of renderer & alpha channels */
void Neill_SDL_SetDrawColour(SDL_Simplewin *sw, Uint8 r, Uint8 g, Uint8 b)
{
   SDL_SetRenderDrawColor(sw->renderer, r, g, b, SDL_ALPHA_OPAQUE);
}

/* MY FUNCTION */
/* A modified version of "Neill_SDL_SetDrawColour". */
void Hosker_SDL_SetDrawColour(SDL_Simplewin *sw, long ebc)
{
  int red, green, blue;

  red = unpack_colour_red(ebc);
  green = unpack_colour_green(ebc);
  blue = unpack_colour_blue(ebc);

  Neill_SDL_SetDrawColour(sw, red, green, blue);
}

/* Filled Circle centred at (cx,cy) of radius r, see :
   http://content.gpwiki.org/index.php/SDL:Tutorials:Drawing_and_Filling_Circles */
void Neill_SDL_RenderFillCircle(SDL_Renderer *rend, int cx, int cy, int r)
{
   double dy;
   for (dy = 1; dy <= r; dy += 1.0) {
        double dx = floor(sqrt((2.0 * r * dy) - (dy * dy)));
        SDL_RenderDrawLine(rend, cx-dx, cy+r-dy, cx+dx, cy+r-dy);
        SDL_RenderDrawLine(rend, cx-dx, cy-r+dy, cx+dx, cy-r+dy);
   }
}

/* Circle centred at (cx,cy) of radius r, see :
   http://content.gpwiki.org/index.php/SDL:Tutorials:Drawing_and_Filling_Circles */
void Neill_SDL_RenderDrawCircle(SDL_Renderer *rend, int cx, int cy, int r)
{
   double dx, dy;
   dx = floor(sqrt((2.0 * r ) ));
   SDL_RenderDrawLine(rend, cx-dx, cy+r, cx+dx, cy+r);
   SDL_RenderDrawLine(rend, cx-dx, cy-r, cx+dx, cy-r);
   for (dy = 1; dy <= r; dy += 1.0) {
        dx = floor(sqrt((2.0 * r * dy) - (dy * dy)));
        SDL_RenderDrawPoint(rend, cx+dx, cy+r-dy);
        SDL_RenderDrawPoint(rend, cx+dx, cy-r+dy);
        SDL_RenderDrawPoint(rend, cx-dx, cy+r-dy);
        SDL_RenderDrawPoint(rend, cx-dx, cy-r+dy);
   }
}

void Neill_SDL_DrawString(SDL_Simplewin *sw, fntrow fontdata[FNTCHARS][FNTHEIGHT], char *str, int ox, int oy)
{
   int i=0;
   unsigned char chr;
   do{
      chr = str[i++];
      Neill_SDL_DrawChar(sw, fontdata, chr, ox+i*FNTWIDTH, oy, WHITE, BLACK);
   }while(str[i]);
}

void Neill_SDL_DrawChar(SDL_Simplewin *sw, fntrow fontdata[FNTCHARS][FNTHEIGHT], unsigned char chr, int ox, int oy, long fg_colour, long bg_colour)
{
  int red_fg, green_fg, blue_fg, red_bg, green_bg, blue_bg;

   unsigned x, y;

  red_fg = unpack_colour_red(fg_colour);
  green_fg = unpack_colour_green(fg_colour);
  blue_fg = unpack_colour_blue(fg_colour);
  red_bg = unpack_colour_red(bg_colour);
  green_bg = unpack_colour_green(bg_colour);
  blue_bg = unpack_colour_blue(bg_colour);

   for(y = 0; y < FNTHEIGHT; y++){
      for(x = 0; x < FNTWIDTH; x++){
         if(fontdata[chr-FNT1STCHAR][y] >> (FNTWIDTH - 1 - x) & 1){
            Neill_SDL_SetDrawColour(sw, red_fg, green_fg, blue_fg);
            SDL_RenderDrawPoint(sw->renderer, x + ox, y+oy);
         }
         else{
            Neill_SDL_SetDrawColour(sw, red_bg, green_bg, blue_bg);
            SDL_RenderDrawPoint(sw->renderer, x + ox, y+oy);
         }
      }
   }
}

/* MY FUNCTION */
/* Ronseal. */
void draw_upper_dh(SDL_Simplewin *sw, fntrow fontdata[FNTCHARS][FNTHEIGHT], unsigned char chr, int ox, int oy, long fg_colour, long bg_colour)
{
  int red_fg, green_fg, blue_fg, red_bg, green_bg, blue_bg;

   unsigned x, y;

  red_fg = unpack_colour_red(fg_colour);
  green_fg = unpack_colour_green(fg_colour);
  blue_fg = unpack_colour_blue(fg_colour);
  red_bg = unpack_colour_red(bg_colour);
  green_bg = unpack_colour_green(bg_colour);
  blue_bg = unpack_colour_blue(bg_colour);

   for(y = 0; y < FNTHEIGHT; y++){
      for(x = 0; x < FNTWIDTH; x++){
         if(fontdata[chr-FNT1STCHAR][y/2] >> (FNTWIDTH - 1 - x) & 1){
            Neill_SDL_SetDrawColour(sw, red_fg, green_fg, blue_fg);
            SDL_RenderDrawPoint(sw->renderer, x + ox, y+oy);
         }
         else{
            Neill_SDL_SetDrawColour(sw, red_bg, green_bg, blue_bg);
            SDL_RenderDrawPoint(sw->renderer, x + ox, y+oy);
         }
      }
   }
}

/* MY FUNCTION */
/* Ronseal. */
void draw_lower_dh(SDL_Simplewin *sw, fntrow fontdata[FNTCHARS][FNTHEIGHT], unsigned char chr, int ox, int oy, long fg_colour, long bg_colour)
{
  int red_fg, green_fg, blue_fg, red_bg, green_bg, blue_bg;

   unsigned x, y;

  red_fg = unpack_colour_red(fg_colour);
  green_fg = unpack_colour_green(fg_colour);
  blue_fg = unpack_colour_blue(fg_colour);
  red_bg = unpack_colour_red(bg_colour);
  green_bg = unpack_colour_green(bg_colour);
  blue_bg = unpack_colour_blue(bg_colour);

   for(y = 0; y < FNTHEIGHT; y++){
      for(x = 0; x < FNTWIDTH; x++){
         if(fontdata[chr-FNT1STCHAR][(y+FNTHEIGHT)/2] >> (FNTWIDTH - 1 - x) & 1){
            Neill_SDL_SetDrawColour(sw, red_fg, green_fg, blue_fg);
            SDL_RenderDrawPoint(sw->renderer, x + ox, y+oy);
         }
         else{
            Neill_SDL_SetDrawColour(sw, red_bg, green_bg, blue_bg);
            SDL_RenderDrawPoint(sw->renderer, x + ox, y+oy);
         }
      }
   }
}

void Neill_SDL_ReadFont(fntrow fontdata[FNTCHARS][FNTHEIGHT], char *fname)
{
    FILE *fp = fopen(fname, "rb");
    size_t itms;
    if(!fp){
       fprintf(stderr, "Can't open Font file %s\n", fname);
       exit(1);
   }
   itms = fread(fontdata, sizeof(fntrow), FNTCHARS*FNTHEIGHT, fp);
   if(itms != FNTCHARS*FNTHEIGHT){
       fprintf(stderr, "Can't read all Font file %s (%d) \n", fname, (int)itms);
       exit(1);
   }
   fclose(fp);
}

/* MY FUNCTION */
/* Ronseal. */
int unpack_colour_red(long ebc)
{
  int red;
  long first_three;

  first_three = ebc-(ebc%1000000);
  first_three = first_three/1000000;
  red = first_three;

  return(red);
}

/* MY FUNCTION */
/* Ronseal. */
int unpack_colour_green(long ebc)
{
  int green;
  long middle_three;

  middle_three = ebc%1000000;
  middle_three = middle_three-(middle_three%1000);
  middle_three = middle_three/1000;
  green = middle_three;
  
  return(green);
}

/* MY FUNCTION */
/* Ronseal. */
int unpack_colour_blue(long ebc)
{
  int blue;
  long last_three;

  last_three = ebc%1000;
  blue = last_three;

  return(blue);
}
