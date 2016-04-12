/**
 * @file option.h
 * @author Les Mixtes
 * @date 01/04/2016
 * @brief Header du fichier option.c
 * @details Prend en charge le menu des options
 */

#ifndef _option_h_
#define _option_h_

#include "../lib/SDL/include/SDL/SDL.h"

/** Nombre de ms entre chaque mouvement des snakes */
#define SPEED_EASY 80
#define SPEED_MEDIUM 100
#define SPEED_HARD 120

/** Type de plateau */
#define BOARD_BASE 1
#define BOARD_1V1 2
#define BOARD_WALL 3

void option(SDL_Surface* sdlScreen, int* pNbSnakes, int* pBoard, int* pSpeedInit);
void aide(SDL_Surface* sdlScreen);

#endif
