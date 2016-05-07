/**
 * @file obstacle.h
 * @author Les Mixtes
 * @date 5/05/2016
 * @brief Header du fichier obstacle.c
 * @details Contient les déclarations des structures et des fonctions utiles dans la gestion du plateau
 */

#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include <stdlib.h>
#include "snake.h"

 /** Structure du plateau :
- nBoardWidth : la largeur du plateau
- nBoardHeight : la hauteur du plateau
- nNbPos : le nombre de positions de départ possibles pour ce plateau
- nSize : le nombre de cases du mur du plateau
- pPtsMur : les cases correspondant au mur
- pPtsPositions : les points correspondant aux positions de départ
- pnDirs : la direction des positions de départ 
- tunnels : les tunnels du plateau 
- nNbTunnels : le nombre de tunnels sur le plateau 
- un tableau de bonus présents sur le plateau 
- le nombre de bonus présents sur le plateau */

typedef struct
{
	int nBoardWidth;
	int nBoardHeight;
	int nNbPos;
	int nSize;
	Point* pPtsMur;
	Point* pPtsPositions;
	int* pnDirs;
	Tunnel** pTunnels;
	int nNbTunnels;
	Bonus** pTabBonus;
	int nNbBonus;
} Board;

Board init_board1();
Board init_board_1v1();
int belongs_to_tab(Point point, Point* tableau, int taille);
int test_collision(Board* mur, Serpent** tab_serpent, int nb_snakes, Point point, int id_snake);
void add_walls_inside(Board* b);
void delete_too_close_walls(Board* b);
int is_cell_free(Point p, Board* b, Serpent** tab_serpent, int nb_snakes);
int okay_to_add_wall(Point p, Board* b, Serpent** tab_serpent, int nb_snakes);
int nb_obstacles_around_3(Point centre, Board* b, Serpent** tab_serpent, int nb_snakes, Serpent* snake);
int nb_obstacles_around_5(Point centre, Board* b, Serpent** tab_serpent, int nb_snakes, Serpent* snake);
void add_wall(Board* b, Serpent** tab_serpent, int nb_snakes);
int belongs_to_tunnel(Point p, Tunnel* t);
void add_tunnels(Board* b, Serpent** tab_serpent, int nb_snakes);
void handle_tunnels(Serpent* s, Board* b);
void free_board(Board b);

#endif