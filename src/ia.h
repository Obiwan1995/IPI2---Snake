/**
 * @file ia.h
 * @author Les Mixtes
 * @date 17/04/2016
 * @brief Header du fichier ia.c
 * @details Contient les déclarations des structures et des fonctions utiles dans la gestion de l'IA aléatoire
 */

#ifndef IA_H_
#define IA_H_

#include "obstacle.h"

int deplacement_ia(Serpent* ia, Board board, int nbSnakes, Serpent** snakes);

#endif