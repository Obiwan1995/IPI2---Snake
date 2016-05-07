/**
 * @file bonus.c
 * @author Les Mixtes
 * @date 7/05/2016
 * @brief Fichier permettant la gestion des bonus
 * @details Contient toutes les fonctions utiles à la gestion des bonus : ajout de bonus, assignation du bonus à un serpent
 */


#include "bonus.h"


/**
 * @fn 			add_bonus(Board* b, Serpent** tab_serpent, int nb_snakes)
 *
 * @brief 		Ajoute un bonus sur le plateau
 *
 * @param 		b 				Le plateau de jeu
 * @param 		tab_serpent 	Le tableaux des serpents dans la partie
 * @param 		nb_snakes 		Le nombre de serpents dans la partie
 *
 * @details 	Génère une case aléatoire pour le nouveau bonus tant que celle-ci n'est pas libre. Ensuite, crée un bonus de type aléatoire et ayant un effet aléatoire et l'ajoute au tableau des bonus du plateau.
 * 
 * @return 		void
 */ 

void add_bonus(Board* b, Serpent** tab_serpent, int nb_snakes)
{
	Point p;
	p.x = rand()%(b->nBoardWidth-2)+1;
	p.y = rand()%(b->nBoardHeight-2)+1;
	while(!is_cell_free(p, b, tab_serpent, nb_snakes))
	{
		p.x = rand()%(b->nBoardWidth-2)+1;
		p.y = rand()%(b->nBoardHeight-2)+1;
	}
	if (b->nNbBonus == 0)
	{
		b->pTabBonus = (Bonus**) malloc(sizeof(Bonus*));
	}
	else
	{
		b->pTabBonus = realloc(b->pTabBonus, (b->nNbBonus+1)*sizeof(Bonus*));
	}
	Bonus* bonus = (Bonus *) malloc(sizeof(Bonus));
	bonus->point = p;
	bonus->type = rand()%NB_TYPES;
	bonus->effect = rand()%2;
	if (bonus->type == reverse || bonus->type == clean)
	{
		bonus->duration = 0;
	}
	else
	{
		bonus->duration = DEFAULT_DURATION;
	}
	bonus->nbRef = 0;
	b->pTabBonus[b->nNbBonus] = bonus;
	b->nNbBonus++;
}

/**
 * @fn 			take_bonus(Serpent* s, Board* b, int index)
 *
 * @brief 		Permet de gérer la prise d'un bonus par un serpent
 *
 * @param 		s 		Le serpent qui prend le bonus
 * @param 		b 		Le plateau de jeu
 * @param 		index 	L'indice du bonus pris par le serpent dans le tableau des bonus du plateau
 *
 * @details 	Copie le bonus du tableau des bonus du plateau vers le tableau des bonus du serpent
 * 
 * @return 		void
 */

void take_bonus(Serpent* s, Board* b, int index)
{
	if (b->pTabBonus[index]->duration == 0)
	{
		switch(b->pTabBonus[index]->type)
		{
			case reverse:
				reverse_snake(s);
				break;

			case clean:
				break;

			default:
				break;
		}
	}
	else
	{
		if (s->nNbBonus == 0)
		{
			s->tabBonus = (Bonus**) malloc(sizeof(Bonus*));
		}
		else
		{
			s->tabBonus = realloc(s->tabBonus, (s->nNbBonus+1)*sizeof(Bonus*));
		}
		s->tabBonus[s->nNbBonus] = b->pTabBonus[index];
		s->tabBonus[s->nNbBonus]->nbRef++;
		s->nNbBonus++;
	}
}

/**
 * @fn 			reverse_snake(Serpent* s)
 *
 * @brief 		Permet d'échanger la tête et la queue du serpent
 *
 * @param 		s 		Le serpent à modifier
 *
 * @details 	Echange toutes les cases du tableau correspondant au corps du serpent puis replace la tête à la place de la queue. Enfin, modifie la direction du serpent en choisissant la direction opposée à l'actuelle.
 * 
 * @return 		void
 */


void reverse_snake(Serpent* s)
{
	int i;
	for (i = 0; i < floor(s->taille/2); i++)
	{
		Point temp = s->tab[i];
		s->tab[i] = s->tab[s->taille-i-1];
		s->tab[s->taille-i-1] = temp;
	}
	s->tete = s->tab[s->taille-1];
	switch(s->dir)
	{
		case top:
			s->dir = bot;
			break;

		case right:
			s->dir = left;
			break;

		case bot:
			s->dir = top;
			break;

		default:
			s->dir = right;
			break;
	}
}

/**
 * @fn 			delete_bonus_board(Board* b, int index)
 *
 * @brief 		Permet de supprimer un bonus du plateau
 *
 * @param 		b 		Le plateau de jeu
 * @param 		index 	L'indice du bonus pris par le serpent dans le tableau des bonus du plateau
 *
 * @details 	Réorganise le tableau des bonus du plateau ou le supprime entièrement en fonction du nombre de bonus présents
 * 
 * @return 		void
 */

void delete_bonus_board(Board* b, int index)
{
	b->nNbBonus--;
	b->pTabBonus[index] = b->pTabBonus[b->nNbBonus];
	b->pTabBonus = realloc(b->pTabBonus, b->nNbBonus*sizeof(Bonus*));
}

/**
 * @fn 			delete_bonus_snake(Serpent* s, int index)
 *
 * @brief 		Permet de supprimer un bonus d'un serpent
 *
 * @param 		s 		Le serpent possédant le bonus à supprimer
 * @param 		index 	L'indice du bonus pris par le serpent dans le tableau des bonus du serpent
 *
 * @details 	Réorganise le tableau des bonus du serpent ou le supprime entièrement en fonction du nombre de bonus possédés
 * 
 * @return 		void
 */

void delete_bonus_snake(Serpent* s, int index)
{
	s->nNbBonus--;
	s->tabBonus[index] = s->tabBonus[s->nNbBonus];
	s->tabBonus = realloc(s->tabBonus, s->nNbBonus*sizeof(Bonus*));
}