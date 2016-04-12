/**
 * @file snake.c
 * @author Les Mixtes
 * @date 17/03/2016
 * @brief Fichier permettant la gestion des serpents
 * @details Contient toutes les fonctions utiles à la gestion des serpents : initialisation, déplacements et gestion des collisions
 */

#include "snake.h"

/**
 * @fn         Serpent* init_snake(Serpent *snake, int id, int speed, int dir, Point pos)
 *
 * @brief      initialise le serpent : donne une valeur à chaque champ de la structure
 *
 * @param      	snake           serpent à initialiser
 * @param		id              id du serpent
 * @param		speed			vitesse du serpent
 * @param		dir 			direction du serpent
 * @param		pos 			position initiale du serpent
 *
 * @return     Le serpent passé en paramètre avec des valeurs pour chaque champ de sa structure
 */


void init_snake(Serpent* snake, int id, int speed, int dir, Point pos)
{
	snake->id = id ;
	snake->vitesse = speed;
	snake->tete.x = pos.x;
	snake->tete.y = pos.y;
	snake->dir = dir;

	snake->taille = 1;
	snake->tab = (Point*)malloc(snake->taille*sizeof(Point)) ;
	snake->tab[0].x=snake->tete.x;
	snake->tab[0].y=snake->tete.y;
}

/**
 *
 * @fn         void Right(Serpent *snake)
 * 
 * @brief       Change la direction et le serpent lorsque le déplacement choisi par le joueur est la droite.
 * @details		Enumération des 4 cas selon la direction actuelle du serpent
 * @details		On ajoute une case de plus au tableau du serpent qui correspond à la position de la nouvelle tête.
 *
 * @param      snake  serpent à déplacer
 */

void Left(Serpent *snake)
{
	switch (snake->dir) {
			case top :
				snake->tete.x -= 1;
				snake->dir = left;
				break;
			case right :
				snake->tete.y -= 1;
				snake->dir = top;
				break;
			case bot :
				snake->tete.x += 1;
				snake->dir = right;
				break;
			case left :
				snake->tete.y += 1;
				snake->dir = bot;
				break;
	}

	//soit on fait ca : ajout de la tete et déplacement des autres cases : le serpent ne grandit pas
	//sinon :le serpent grandit
	int rng=rand()%100;
	if (rng > P_GAIN_SIZE)
	{
		int i;
		for (i=1; i<snake->taille; i++)
		{
			snake->tab[i-1].x = snake->tab[i].x;
			snake->tab[i-1].y = snake->tab[i].y;
		}
		snake->tab[snake->taille-1] = snake->tete;
	}
	else
	{
		snake->tab = (Point*)realloc(snake->tab, (snake->taille + 1)*sizeof(Point));
		snake->tab[snake->taille] = snake->tete;
		snake->taille++;
	}
}

/**
 *
 * @fn         void Forward(Serpent *snake)
 * 
 * @brief      	Change la direction et le serpent lorsque le déplacement choisi par le joueur est tout droit (il continue dans sa direction actuelle).
 * @details		Enumération des 4 cas selon la direction actuelle du serpent
 * @details   	On ajoute une case de plus au tableau du serpent qui correspond à la position de la nouvelle tête.
 *
 * @param      snake  serpent à déplacer
 */

void Forward(Serpent *snake)
{
	switch (snake->dir)
	{
		case top :
			snake->tete.y -= 1;
			break;
		case right :
			snake->tete.x += 1;
			break;
		case bot :
			snake->tete.y += 1;
			break;
		case left :
			snake->tete.x -= 1;
			break;
	}

	//soit on fait ca : ajout de la tete et déplacement des autres cases : le serpent ne grandit pas
	//sinon :le serpent grandit
	int rng=rand()%100;
	if (rng > P_GAIN_SIZE)
	{
		int i;
		for (i=1; i<snake->taille; i++)
		{
			snake->tab[i-1].x = snake->tab[i].x;
			snake->tab[i-1].y = snake->tab[i].y;
		}
		snake->tab[snake->taille-1] = snake->tete;
	}
	else
	{
		snake->tab = (Point*)realloc(snake->tab, (snake->taille + 1)*sizeof(Point));
		snake->tab[snake->taille] = snake->tete;
		snake->taille++;
	}
}

/**
 *
 * @fn         void Left(Serpent *snake)
 * 
 * @brief      	Change la direction et le serpent lorsque le déplacement choisi par le joueur est la gauche.		
 * @details		Enumération des 4 cas selon la direction actuelle du serpent
 * @details	   	On ajoute une case de plus au tableau du serpent qui correspond à la position de la nouvelle tête.
 *
 * @param      snake  serpent à déplacer
 */

void Right(Serpent *snake)
{
	switch (snake->dir)
	{
		case top :
			snake->tete.x += 1;
			snake->dir = right;
			break;
		case right :
			snake->tete.y += 1;
			snake->dir = bot;
			break;
		case bot :
			snake->tete.x -= 1;
			snake->dir = left;
			break;
		case left :
			snake->tete.y -= 1;
			snake->dir = top;
			break;
	}

	//soit on fait ca : ajout de la tete et déplacement des autres cases : le serpent ne grandit pas
	//sinon :le serpent grandit
	int rng=rand()%100;
	if (rng > P_GAIN_SIZE)
	{
		int i;
		for (i=1; i<snake->taille; i++)
		{
			snake->tab[i-1].x = snake->tab[i].x;
			snake->tab[i-1].y = snake->tab[i].y;
		}
		snake->tab[snake->taille-1] = snake->tete;
	}
	else
	{
		snake->tab = (Point*)realloc(snake->tab, (snake->taille + 1)*sizeof(Point));
		snake->tab[snake->taille] = snake->tete;
		snake->taille++;
	}
}

/**
 * @fn 		int appartient_tableau(Point point, Point* tableau, int taille)
 * 
 * @brief   Teste l'appartenance d'un point (2 coordonnées x et y) à un tableau
 *
 * @param  point    point dont on veut tester l'appartenance au tableau
 * @param  tableau  tableau de points
 * @param  taille   taille du tableau
 *
 * @return 0 si le point n'appartient pas au tableau
 * @return 1 sinon
 */

int appartient_tableau(Point point, Point* tableau, int taille) {
	int i=0;
	int flag=0;
	while (flag==0 && i<taille) {
		if ( (tableau[i].x == point.x) && (tableau[i].y == point.y) ) {
			flag=1;
		}
		else {
			i=i+1;
		}
	}
	return flag;
}

/**
 * @fn         int test_collision(Board* mur, Serpent** tab_serpent, int nb_snakes)
 *
 * @brief      Teste la collision d'un serpent avec le mur ou un autre serpent
 *
 * @param  mur          plateau contenant un tableau de points correspondant aux emplacements des murs
 * @param  tab_serpent  tableau de serpent : nécessaire pour la collision avec les autres serpents
 * @param  nb_snakes  	nombre de serpents = longueur du tableau tab_serpent
 *
 * @return  0 s'il n'y a pas de collision
 * @return	Sinon, l'id du serpent qui entre en collision avec le mur ou un autre serpent
 */

int test_collision(Board* mur, Serpent** tab_serpent, int nb_snakes, Point point, int id_snake) { //Point = tête du serpent
	int i;
	if (appartient_tableau(point, mur->pPtsMur, mur->nSize)) 
	{
		return 1;
	}
	else 
	{
		for (i=0; i<nb_snakes; i++) 
		{
			if ((i+1 != id_snake && appartient_tableau(point, tab_serpent[i]->tab, tab_serpent[i]->taille)) || (i+1 == id_snake && appartient_tableau(point, tab_serpent[i]->tab, tab_serpent[i]->taille-1)))
			{
				return 1;
			}
		}
	}
	return 0;	
}

/**
 * @fn 			free_snake(Serpent* snake)
 *
 * @brief		Supprime un serpent
 *
 * @param 		snake Serpent à supprimer
 *
 * @details		Supprime un serpent de la mémoire en supprimant son tableau de points puis sa structure complète
 *
 */

void free_snake(Serpent* snake) 
{
	free(snake->tab);
	free(snake);
}