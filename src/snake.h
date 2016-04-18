/**
 * @file snake.h
 * @author Les Mixtes
 * @date 18/04/2016
 * @brief Header du fichier snake.c
 * @details Contient toutes les déclarations des structures et des variables utiles dans la gestion des serpents
 */

#ifndef SNAKE_H_
#define SNAKE_H_

#include <time.h>
#include <stdlib.h>

/** Probabilité que le serpent grandisse à chaque pas de temps (en pourcentage) */
#define P_GAIN_SIZE 40

/** Direction du serpent : haut, droite, bas ou gauche */
typedef enum Direction {top, right, bot, left} Direction;

/** Structure de Serpent qui permet de situer le serpent ou les obstacles:
- x : sa position en x
- y : sa position en y */

typedef struct {
	int x;
	int y;
} Point;

/** Structure de Serpent avec plusieurs champs qui le caractérise :
- un identifiant : permet de reconnaitre le serpent
- une vitesse
- une taille (est modifiée au cours du jeu)
- un tableau de points qui représente le serpent 
- un point correspondant à la tête du serpent
- une direction : la direction du serpent */

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
void free_snake(Serpent** snake, int nbSnake);

#endif