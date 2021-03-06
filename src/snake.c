/**
 * @file snake.c
 * @author Les Mixtes
 * @date 7/05/2016
 * @brief Fichier permettant la gestion des serpents
 * @details Contient toutes les fonctions utiles à la gestion des serpents : initialisation et déplacements
 */

#include "snake.h"

/**
 * @fn         Serpent* init_snake(Serpent *snake, int id, int speed, int dir, Point pos)
 *
 * @brief      Initialise le serpent : donne une valeur à chaque champ de la structure
 *
 * @param      	snake 		Le serpent à initialiser
 * @param		id 			L'identifiant du serpent
 * @param		speed 		La vitesse du serpent
 * @param		dir 		La direction du serpent
 * @param		pos 		La position initiale du serpent
 *
 * @return     Le serpent passé en paramètre avec des valeurs pour chaque champ de sa structure
 */


void init_snake(Serpent* snake, int id, int speed, int dir, Point pos)
{
	snake->id = id ;
	snake->vitesse = speed;
	snake->vivant = 1;
	snake->reverse = 0;
	snake->tete.x = pos.x;
	snake->tete.y = pos.y;
	snake->dir = dir;
	snake->nNbBonus = 0;

	snake->taille = 2;
	snake->pGainSize = P_GAIN_SIZE;
	snake->tab = (Point*)malloc(snake->taille*sizeof(Point));
	snake->tab[0].x=snake->tete.x;
	snake->tab[0].y=snake->tete.y;

	switch (dir) {
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
	snake->tab[1].x=snake->tete.x;
	snake->tab[1].y=snake->tete.y;
}

/**
 *
 * @fn         	void Right(Serpent *snake)
 * 
 * @brief       Change la direction et le serpent lorsque le déplacement choisi par le joueur est la droite.
 *
 * @param      	snake  serpent à déplacer
 *
 * @details		Enumération des 4 cas selon la direction actuelle du serpent
 * @details		On ajoute une case de plus au tableau du serpent qui correspond à la position de la nouvelle tête.
 *
 * @return 		void
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
	if (rng > snake->pGainSize)
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
 * @fn         	void Forward(Serpent *snake)
 * 
 * @brief      	Change la direction et le serpent lorsque le déplacement choisi par le joueur est tout droit (il continue dans sa direction actuelle).
 *
 * @param      	snake  serpent à déplacer
 *
 * @details		Enumération des 4 cas selon la direction actuelle du serpent
 * @details   	On ajoute une case de plus au tableau du serpent qui correspond à la position de la nouvelle tête.
 *
 * @return 		void
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
	if (rng > snake->pGainSize)
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
 * @fn         	void Left(Serpent *snake)
 * 
 * @brief      	Change la direction et le serpent lorsque le déplacement choisi par le joueur est la gauche.		
 *
 * @param      	snake  serpent à déplacer
 *
 * @details		Enumération des 4 cas selon la direction actuelle du serpent
 * @details	   	On ajoute une case de plus au tableau du serpent qui correspond à la position de la nouvelle tête.
 *
 * @return 		void
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
	if (rng > snake->pGainSize)
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
 * @fn 			enter_tunnel(Serpent* snake, Tunnel* t)
 *
 * @brief		Fait bouger un serpent à travers un tunnel
 *
 * @param 		snake 		Le serpent à déplacer
 * @param		tunnel 		Le tunnel emprunté
 *
 * @return 		void
 */

void enter_tunnel(Serpent* snake, Tunnel* tunnel)
{
	int rand_sortie = rand()%(tunnel->nNbSorties);
	snake->tete.x = tunnel->sorties[rand_sortie].x;
	snake->tete.y = tunnel->sorties[rand_sortie].y;
}

/**
 * @fn 			free_snakes(Serpent** snakes, int nbSnake)
 *
 * @brief		Supprime la mémoire allouée au tableau de serpents
 *
 * @param 		snakes		Le tableau de serpents à supprimer
 * @param		nbSnake 	Le nombre de serpents dans le tableau
 *
 * @details		Supprime un tableau de serpents de la mémoire en supprimant pour chaque serpent son tableau de points puis sa structure complète
 *
 * @return 		void
 */

void free_snakes(Serpent** snakes, int nbSnake) 
{	
	int i;
	for (i=0; i<nbSnake; i++)
	{
		free_snake(snakes[i]);
	}
	free(snakes);
}

/**
 * @fn 			free_snake(Serpent* snake)
 *
 * @brief		Supprime la mémoire allouée à un serpent
 *
 * @param 		snake 		Le serpent à supprimer
 *
 * @details		Supprime le tableau de points du serpent, son tableau de bonus puis sa structure complète
 *
 * @return 		void
 */

void free_snake(Serpent* snake)
{
	free(snake->tab);
	free(snake);
}