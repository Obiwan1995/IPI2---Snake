/**
 * @file obstacle.h
 * @author Les Mixtes
 * @date 1/04/2016
 * @brief Header du fichier obstacle.c
 * @details Contient les déclarations des structures et des fonctions utiles dans la gestion du plateau
 */

#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include <stdlib.h>

#define BOARD_WIDTH 40
#define BOARD_HEIGHT 40


 /** Structure de Serpent qui permet de situer le serpent ou les obstacles:
- x : sa position en x
- y : sa position en y */

typedef struct {
	int x;
	int y;
} Point;

 /** Structure du plateau :
- nNbPos : le nombre de positions de départ possibles pour ce plateau
- nSize : le nombre de cases du mur du plateau
- pPtsMur : les cases correspondant au mur
- pPtsPositions : les points correspondant aux positions de départ
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
Board init_board_1v1();
Board init_board_walls();
void free_board(Board* b);

#endif