/**
 * @file bonus.c
 * @author Les Mixtes
 * @date 14/05/2016
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
 * @param 		tab_serpent 	Le tableau des serpents dans la partie
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
	Bonus* bonus = (Bonus*) malloc(sizeof(Bonus));
	bonus->point = p;
	bonus->type = rand()%NB_TYPES;
	if (bonus->type == change_snake)
	{
		bonus->effect = self;
	}
	else
	{
		bonus->effect = rand()%2;
	}
	if (bonus->type == reverse || bonus->type == clean || bonus->type == change_snake)
	{
		bonus->duration = 0;
	}
	else
	{
		bonus->duration = DEFAULT_DURATION;
	}
	b->pTabBonus[b->nNbBonus] = bonus;
	b->nNbBonus++;
}

/**
 * @fn 			take_bonus(Serpent* s, Bonus* bonus)
 *
 * @brief 		Permet de gérer la prise d'un bonus par un serpent
 *
 * @param 		s 		Le serpent qui prend le bonus
 * @param 		bonus 	Le bonus pris par le serpent
 *
 * @details 	Copie le bonus du tableau des bonus du plateau vers le tableau des bonus du serpent
 * 
 * @return 		void
 */

void take_bonus(Serpent* s, Bonus* bonus)
{
	if (s->vivant)
	{
		if (bonus->duration == 0)
		{
			switch(bonus->type)
			{
				case reverse:
					reverse_snake(s);
					break;

				case clean:
					clean_snake(s);
					break;

				default:
					break;
			}
		}
		else
		{
			switch (bonus->type)
			{
				case increase_size:
					s->pGainSize = 100;
					break;

				case decrease_size:
					s->pGainSize = 0;
					break;

				case increase_speed:
					s->vitesse = round(0.75*s->vitesse);
					break;

				case decrease_speed:
					s->vitesse = round(1.25*s->vitesse);
					break;

				case reverse_keys:
					s->reverse = 1;
					break;

				default:
					break;
			}
			if (s->nNbBonus == 0)
			{
				s->tabBonus = (Bonus**) malloc(sizeof(Bonus*));
			}
			else
			{
				s->tabBonus = realloc(s->tabBonus, (s->nNbBonus+1)*sizeof(Bonus*));
			}
			s->tabBonus[s->nNbBonus] = bonus;
			s->nNbBonus++;
		}
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
			Point bas;
			bas.x = s->tete.x;
			bas.y = s->tete.y+1;
			if (belongs_to_tab(bas, s->tab, s->taille))
			{
				Point gauche;
				gauche.x = s->tete.x-1;
				gauche.y = s->tete.y;
				if (belongs_to_tab(gauche, s->tab, s->taille))
				{
					s->dir = left;
				}
				else
				{
					s->dir = right;
				}
			}
			break;

		case right:
			s->dir = left;
			Point gauche;
			gauche.x = s->tete.x-1;
			gauche.y = s->tete.y;
			if (belongs_to_tab(gauche, s->tab, s->taille))
			{
				Point haut;
				haut.x = s->tete.x;
				haut.y = s->tete.y-1;
				if (belongs_to_tab(haut, s->tab, s->taille))
				{
					s->dir = bot;
				}
				else
				{
					s->dir = top;
				}
			}
			break;

		case bot:
			s->dir = top;
			Point haut;
			haut.x = s->tete.x;
			haut.y = s->tete.y-1;
			if (belongs_to_tab(haut, s->tab, s->taille))
			{
				Point gauche;
				gauche.x = s->tete.x-1;
				gauche.y = s->tete.y;
				if (belongs_to_tab(gauche, s->tab, s->taille))
				{
					s->dir = right;
				}
				else
				{
					s->dir = left;
				}
			}
			break;

		default:
			s->dir = right;
			Point droite;
			droite.x = s->tete.x+1;
			droite.y = s->tete.y;
			if (belongs_to_tab(droite, s->tab, s->taille))
			{
				Point haut;
				haut.x = s->tete.x;
				haut.y = s->tete.y-1;
				if (belongs_to_tab(haut, s->tab, s->taille))
				{
					s->dir = bot;
				}
				else
				{
					s->dir = top;
				}
			}
			break;
	}
}

/**
 * @fn 			clean_snake(Serpent* s)
 *
 * @brief 		Permet de supprimer le corps du serpent
 *
 * @param 		s 		Le serpent à modifier
 *
 * @details		Free le tableau de points du serpent puis remet la tête dans le tableau
 * 
 * @return 		void
 */

void clean_snake(Serpent* s)
{
	free(s->tab);
	s->tab = (Point*) malloc(sizeof(Point));
	s->tab[0] = s->tete;
	s->taille = 1;
}

/**
 * @fn 			void change_snakes(Serpent** snakes, int nb_snakes, int index)
 *
 * @brief 		Permet d'échanger deux serpents
 *
 * @param 		snakes 		Le tableau de serpents dans la partie
 * @param 		nb_snakes 	Le nombre de serpents dans la partie
 * @param 		index  		L'indice du serpent qui a pris le bonus dans le tableau des serpents
 *
 * @details		Si le serpent qui a pris le bonus est le joueur, on l'échange aléatoirement avec l'un des autres serpents.
 * @details 	Si le serpent qui a pris le bonus est géré par une IA, on échange celui-ci avec celui du joueur
 * 
 * @return 		void
 */

void change_snakes(Serpent** snakes, int nb_snakes, int index)
{
	Serpent* player = snakes[0];
	if (index == 0)
	{
		int snakesIndex[nb_snakes-1];
		int n = 0;
		int i;
		for(i = 1; i < nb_snakes; i++)
		{
			if (snakes[i]->vivant)
			{
				snakesIndex[n] = i;
				n++;
			}
		}
		int randIndex = snakesIndex[rand()%n];
		snakes[0] = snakes[randIndex];
		snakes[randIndex] = player;
	}
	else
	{
		snakes[0] = snakes[index];
		snakes[index] = player;
	}
}

/**
 * @fn 			close_walls(Board* b, int nWallsRow)
 *
 * @brief 		Permet de remplir le plateau avec des murs
 *
 * @param 		b 			Le plateau de jeu
 * @param 		nWallsRow 	La rangée courante des murs
 *
 * @details 	Rajoute une rangée de murs au plateau en fonction de la rangée actuelle
 * 
 * @return 		void
 */

void close_walls(Board* b, int nWallsRow)
{
	int n = b->nSize;
	b->nSize += 2*(b->nBoardWidth-nWallsRow-nWallsRow-1)+2*(b->nBoardHeight-nWallsRow-nWallsRow-1);
	b->pPtsMur = realloc(b->pPtsMur, b->nSize*sizeof(Point));
	int i, j;
	for (i = nWallsRow; i < b->nBoardWidth-nWallsRow; i++)
	{
		for (j = nWallsRow; j < b->nBoardHeight-nWallsRow; ++j)
		{
			if (i == nWallsRow || j == nWallsRow || i == b->nBoardWidth-nWallsRow-1 || j == b->nBoardHeight-nWallsRow-1)
			{
				b->pPtsMur[n].x = i;
				b->pPtsMur[n].y = j;
				n++;
			}
		}
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
	switch(s->tabBonus[index]->type)
	{
		case increase_size:
		case decrease_size:
			s->pGainSize = P_GAIN_SIZE;
			break;

		case increase_speed:
			s->vitesse = (int)(4.0/3.0*s->vitesse);
			break;

		case decrease_speed:
			s->vitesse = (int)(4.0/5.0*s->vitesse);
			break;

		case reverse_keys:
			s->reverse = 0;
			break;

		default:
			break;
	}
	s->nNbBonus--;
	s->tabBonus[index] = s->tabBonus[s->nNbBonus];
	s->tabBonus = realloc(s->tabBonus, s->nNbBonus*sizeof(Bonus*));
}