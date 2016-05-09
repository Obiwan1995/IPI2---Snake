/**
 * @file snake.h
 * @author Les Mixtes
 * @date 5/05/2016
 * @brief Header du fichier snake.c
 * @details Contient toutes les déclarations des structures et des variables utiles dans la gestion des serpents
 */

#ifndef SNAKE_H_
#define SNAKE_H_

#include <time.h>
#include <stdlib.h>

/** Probabilité que le serpent grandisse à chaque pas de temps (en pourcentage) */
#define P_GAIN_SIZE 40

/** Structure de Serpent qui permet de situer le serpent ou les obstacles:
- x : sa position en x
- y : sa position en y */

typedef struct {
	int x;
	int y;
} Point;

/** Type du bonus : affecte soit la vitesse, soit la taille du serpent, soit l'emplacement de la tête et de la queue, soit le corps du serpent en le supprimant, soit les touches en les inversant */
typedef enum Type {increase_speed, decrease_speed, increase_size, decrease_size, reverse, clean, reverse_keys, closing_walls, NB_TYPES} Type;

/** Effet du bonus : pour soi ou pour les autres */
typedef enum Effect {self, others} Effect;

/** Structure d'un bonus :
- Son type
- Son effet
- Le point où il est situé 
- L'heure à laquelle il commence a être utilisé 
- Sa durée en secondes
- Le nombre de références vers ce bonus */
typedef struct {
	Type type;
	Effect effect;
	Point point;
	int startTimer;
	int duration;
	int nbRef;
} Bonus;


/** Direction du serpent : haut, droite, bas ou gauche */
typedef enum Direction {top, right, bot, left} Direction;


/** Structure de Serpent avec plusieurs champs qui le caractérise :
- un identifiant : permet de reconnaitre le serpent
- une vitesse
- une taille (est modifiée au cours du jeu)
- un booléen vivant pour savoir s'il bouge encore
- un tableau de points qui représente le serpent 
- un point correspondant à la tête du serpent
- une direction : la direction du serpent 
- un tableau de bonus possédés par le serpent 
- le nombre de bonus possédés par le serpent */

typedef struct {
	int id;
	int vitesse;
	int taille;
	int vivant;
	Point* tab;
	Point tete;
	Direction dir;
	Bonus** tabBonus;
	int nNbBonus;
} Serpent;


/** Structure d'un tunnel :
- entree : l'entrée du tunnel
- sorties : les sorties du tunnel
- nNbSorties : le nombre de sorties du tunnel */

typedef struct
{
	Point entree;
	Point* sorties;
	int nNbSorties;
} Tunnel;

void init_snake(Serpent* snake, int id, int speed, int dir, Point pos);
void Right(Serpent* snake);
void Forward(Serpent* snake);
void Left(Serpent* snake);
void enter_tunnel(Serpent* snake, Tunnel* tunnel);
void free_snakes(Serpent** snake, int nbSnake);
void free_bonus_snakes(Serpent** snakes, int nbSnake);
void free_snake(Serpent* snake);

#endif