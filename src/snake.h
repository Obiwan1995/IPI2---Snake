/**
 * @file snake.h
 * @author Les Mixtes
 * @date 17/03/2016
 * @brief Header du fichier snake.c
 * @details Contient toutes les déclarations des structures et des variables utiles dans la gestion des serpents
 */

#ifndef SNAKE_H_
#define SNAKE_H_

#include <stdio.h>
#include <time.h>
#include "obstacle.h"

/** Probabilité que le serpent grandisse à chaque pas de temps (en pourcentage) */
#define P_GAIN_SIZE 50

/** Correspond à la direction du serpent : haut, droite, bas ou gauche */

typedef enum Direction {top=1, right=2, bot=3, left=4} Direction;

/** Structure de Serpent avec plusieurs champs qui le caractérise :
- un identifiant : permet de reconnaitre le serpent
- une vitesse
- une taille (est modifiée au cours du jeu)
- un tableau de point qui représente le serpent 
- un point correspondant à la tête du serpent
- une direction : la direction du serepent */

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
<<<<<<< HEAD
void affiche_tableau(Serpent* snake);
void init_snake(Serpent* snake, int taille_plateau, int id, int vitesse);
int test_collision(Mur mur, Serpent** tab_serpent, int taille_mur, int nbr_serpent);
void free_snake(Serpent* snake)
=======
int test_collision(Board* mur, Serpent** tab_serpent, int nb_snakes);
>>>>>>> 7eb4872e3db42dccd2da46d33e18ddb26200f123

#endif