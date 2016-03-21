/**
 * @file obstacles.h
 * @author Les Mixtes
 * @date 17/03/2016
 * @brief Header du fichier obstacles.c
 * @details Contient les déclarations des structures et des fonctions utiles dans la gestion du plateau
 */

#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include <stdlib.h>


/** Taille et hauteur du plateau de jeu */
#define BOARD_HEIGHT 40
#define BOARD_WIDTH 40

 /** Structure de Serpent qui permet de situer le serpent ou les obstacles:
- x : sa position en x
- y : sa position en y */

typedef struct {
	int x;
	int y;
} Point;

 /** Structure du plateau :
- nNbPos : le nombre de position de départ possible pour ce plateau
- nSize : le nombre de case du mur du plateau
- pPtsMur : les cases du mur
- pPtsPositions : les points des positions de départ
- pnDirs : la direction des positions de départ */

typedef struct
{
	int nNbPos;
	int nSize;
	Point* pPtsMur;
	Point* pPtsPositions;
	int* pnDirs;
} Board;

Board init_board1();

#endif