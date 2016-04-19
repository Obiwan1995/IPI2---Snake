/**
 * @file game.h
 * @author Les Mixtes
 * @date 18/04/2016
 * @brief Header du fichier game.c
 * @details Contient les déclarations des fonctions utiles dans la gestion du jeu
 */

#ifndef _game_h_
#define _game_h_

#include "../lib/SDL/include/SDL/SDL.h"
#include "obstacle.h"

/** Taille d'une case en pixels */
#define SIZE_CASE 15

/** Couleur des murs */
#define WALL 0x005C5C5C
 /** Couleur rouge */
#define RED 0x00B50000
 /** Couleur verte */
#define GREEN 0x004FEB3B
 /** Couleur bleue */
#define BLUE 0x0000046E
 /** Couleur jaune */
#define YELLOW 0x00D9D20B

void play(SDL_Surface* sdlScreen, Board board, int nbSnakes, int nSpeedInit);
void paint(SDL_Surface* sdlScreen, int x, int y, int nId);
void setPixel(SDL_Surface *surface, int x, int y, Uint32 color);

#endif
