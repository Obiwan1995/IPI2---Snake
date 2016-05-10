/**
 * @file game.h
 * @author Les Mixtes
 * @date 27/04/2016
 * @brief Header du fichier game.c
 * @details Contient les déclarations des fonctions utiles dans la gestion du jeu
 */

#ifndef _game_h_
#define _game_h_

#include "../lib/SDL/include/SDL/SDL.h"
#include "bonus.h"

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
/** Couleur des tunnels */
#define TUNNEL 0x00BD8C22
/** Couleur des bonus qui affectent le serpent qui le prend */
#define SELF_BONUS 0x0008690F
/** Couleur des bonus globaux */
#define GLOBAL_BONUS 0x009C008F
 
/** Nombre de secondes avant le début du jeu */
#define STARTING_TIMER 3
/** Nombre de secondes lorsque le mur avance */
#define WALLS_CLOSING_TIMER 2000
/** Nombre de secondes lorsqu'on ajoute un objet */
#define ADDING_OBJECT_TIMER 150


/** Probabilité d'apparation des murs en pourcentage */
#define P_ADD_WALL 7
/**  1 - Probabilité d'apparation des bonus en pourcentage */
#define P_ADD_BONUS 95

void play(SDL_Surface* sdlScreen, Board board, int nbSnakes, int nSpeedInit);
void paint(SDL_Surface* sdlScreen, int x, int y, int nId);
void paintBonus(SDL_Surface* sdlScreen, Bonus* bonus);
void setPixel(SDL_Surface *surface, int x, int y, Uint32 color);

#endif
