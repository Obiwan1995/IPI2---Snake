/**
 * @file bonus.h
 * @author Les Mixtes
 * @date 9/05/2016
 * @brief Header du fichier bonus.c
 * @details Contient les déclarations des structures et des fonctions utiles dans la gestion des bonus
 */

#ifndef _bonus_h_
#define _bonus_h_

#include <stdlib.h>
#include <math.h>
#include "obstacle.h"

/** Probabilité d'apparation des bonus en pourcentage */
#define P_ADD_BONUS 5

/** Durée par défaut des bonus en secondes */
#define DEFAULT_DURATION 5

void add_bonus(Board* b, Serpent** tab_serpent, int nb_snakes);
void take_bonus(Serpent* s, Board* b, int index);
void reverse_snake(Serpent* s);
void clean_snake(Serpent* s);
void close_walls(Board* b, int nWallsRow);
void delete_bonus_board(Board* b, int index);
void delete_bonus_snake(Serpent* s, int index);

#endif