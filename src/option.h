/**
 * @file option.h
 * @author Les Mixtes
 * @date 18/04/2016
 * @brief Header du fichier option.c
 * @details Prend en charge le menu des options
 */

#ifndef _option_h_
#define _option_h_

#include "../lib/SDL/include/SDL/SDL.h"

/** Niveau facile : 200 ms entre chaque déplacement des serpents */
#define SPEED_EASY 2000
/** Niveau moyen : 120 ms entre chaque déplacement des serpents */
#define SPEED_MEDIUM 120
/** Niveau difficile : 80 ms entre chaque déplacement des serpents */
#define SPEED_HARD 60

/** Plateau de base */
#define BOARD_BASE 1
/** Plateau 1 contre 1 */
#define BOARD_1V1 2
/** Grand plateau */
#define BIG_BOARD 3

/** Pas de murs au milieu */
#define BOARD_WITHOUT_WALLS 2
/** Murs au milieu */
#define BOARD_WITH_WALLS 1

void option(SDL_Surface* sdlScreen, int* pNbSnakes, int* pBoard, int* pSpeedInit, int* pWalls);
void aide(SDL_Surface* sdlScreen);

#endif
