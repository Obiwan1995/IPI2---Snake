#ifndef _game_h_
#define _game_h_

#include "../SDL/include/SDL/SDL.h"
#include "snake.h"

#define SIZE_CASE 15
#define BLACK 0x00696969
#define RED 0x00DF2020
#define GREEN 0x0000FF00
#define BLUE 0x000000FF

void play(SDL_Surface* sdlScreen);
void paint(SDL_Surface* sdlScreen, int x, int y, int nId);
void setPixel(SDL_Surface *surface, int x, int y, Uint32 color);

#endif
