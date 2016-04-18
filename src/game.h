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

/** Couleur noire */
#define BLACK 0x00696969
 /** Couleur rouge */
#define RED 0x00DF2020
 /** Couleur verte */
#define GREEN 0x0000FF00
 /** Couleur bleue */
#define BLUE 0x000000FF

void play(SDL_Surface* sdlScreen, Board board, int nbSnakes, int nSpeedInit);
void paint(SDL_Surface* sdlScreen, int x, int y, int nId);
void setPixel(SDL_Surface *surface, int x, int y, Uint32 color);

#endif
