// Présentation des structures de données utiles au jeu

#ifndef SNAKE_H_
#define SNAKE_H_

#include <stdio.h>
#include <time.h>
#include "obstacle.h"

#define P_GAIN_SIZE 50

// Type Direction pour savoir dans quelle direction le serepent est actuellement
// en train d'avancer : vers le haut, vers la droite, vers la gauche, vers le bas

typedef enum Direction {top=1, right=2, bot=3, left=4} Direction;

// Structure de Serpent avec différents champs qui le cararctérise :
// 		- un identifiant : permet de reconnaitre le serpent
// 		- une vitesse
// 		- une taille (est modifiée au cours du jeu)
// 		- un tableau de point qui représente le serpent 
// 		- une direction : la direction du serepent

typedef struct {
	int id;
	int vitesse;
	int taille;
	Point* tab;
	Point tete;
	Direction dir;
} Serpent;

void init_snake(Serpent* snake, int id, int speed, int dir, Point pos);
void Right(Serpent* snake);
void Forward(Serpent* snake);
void Left(Serpent* snake);
int appartient_tableau(Point point, Point* tableau, int taille);
void affiche_tableau(Serpent* snake);
int test_collision(Board* mur, Serpent** tab_serpent, int nb_snakes);

#endif