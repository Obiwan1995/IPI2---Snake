#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include <stdlib.h>

#define BOARD_HEIGTH 40
#define BOARD_WIDTH 40

// Structure de Point qui permet de situer le serpent ou les obstacles

typedef struct {
	int x;
	int y;
} Point;

// Structure de Serpent avec différents champs qui le cararctérise :
// 		- un identifiant : permet de reconnaitre le serpent
// 		- une vitesse
// 		- une taille (est modifiée au cours du jeu)
// 		- un tableau de point qui représente le serpent 
// 		- une direction : la direction du serepent

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