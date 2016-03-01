#ifndef _game_h_
#define _game_h_

#include "../SDL/include/SDL/SDL.h"

#define SIZE_PIXEL 15
#define RED 0x00FF0000
#define GREEN 0x0000FF00
#define BLUE 0x000000FF

void play(SDL_Surface* sdlScreen);
void paint(SDL_Surface* sdlScreen, int x, int y, int nId);
void setPixel(SDL_Surface *surface, int x, int y, Uint32 color);

#endif
