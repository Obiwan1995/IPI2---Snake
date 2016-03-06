
// Présentation des structures de données utiles au jeu

#ifndef SNACK_H_
#define SNACK_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure de Point qui permet de situer le serpent ou les obstacles

typedef struct {
	int x;
	int y;
} Point;

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

// Type Mur qui va délimiter le terrain de jeu : tableau de coordonnées des points qui représentent le mur

typedef Point* Mur;

void Right(Serpent* snake);
void Forward(Serpent* snake);
void Left(Serpent* snake);
int appartient_tableau(Point point, Point* tableau, int taille);
void affiche_tableau(Serpent* snake);
Serpent* init_snake(Serpent* snake, int taille_plateau, int id, int vitesse);
int test_collision(Mur mur, Serpent** tab_serpent, int taille, int nbr_serpent)

#endif