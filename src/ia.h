/**
 * @file ia.h
 * @author Les Mixtes
 * @date 18/04/2016
 * @brief Header du fichier ia.c
 * @details Contient les déclarations des structures et des fonctions utiles dans la gestion de l'IA aléatoire
 */

#ifndef IA_H_
#define IA_H_

#include "obstacle.h"

void move_random_ia(Serpent* ia, Board board, int nbSnakes, Serpent** snakes);

#endif