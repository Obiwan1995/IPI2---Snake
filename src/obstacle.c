/**
 * @file obstacle.c
 * @author Les Mixtes
 * @date 14/05/2016
 * @brief Fichier permettant la création des murs et des positions de départ des serpents
 * @details Contient l'initialisation du "plateau" et des murs et des fonctions de gestion des collisions
 */

#include "obstacle.h"

/**
 * @fn         Board init_board1()
 *
 * @brief      Initialise le plateau de base
 *
 * @param      void
 *
 * @return     Le plateau avec ses murs et 4 positions de départs
 */

Board init_board1()
{
	Board B;
	B.nBoardWidth = 40;
	B.nBoardHeight = 40;

	B.nNbTunnels = 0;

	B.nNbBonus = 0;

	B.nSize = 2*B.nBoardWidth+2*B.nBoardHeight-4;
	B.pPtsMur = (Point*)malloc(B.nSize*sizeof(Point));

	int i, j, n;
	n = 0;
	for (i = 1; i <= B.nBoardWidth; ++i)
	{
		for (j = 1; j <= B.nBoardHeight; ++j)
		{
			if (i == 1 || j == 1 || i == B.nBoardWidth || j == B.nBoardHeight)
			{
				B.pPtsMur[n].x = (i-1);
				B.pPtsMur[n].y = (j-1);
				n++;
			}
		}
	}

	B.nNbPos = 4;

	B.pPtsPositions = (Point*)malloc(B.nNbPos*sizeof(Point));
	B.pnDirs = (int*)malloc(B.nNbPos*sizeof(int));

	B.pPtsPositions[0].x = B.nBoardWidth/2;
	B.pPtsPositions[0].y = B.nBoardHeight/6;
	B.pnDirs[0] = bot;

	B.pPtsPositions[1].x = (B.nBoardWidth*5)/6;
	B.pPtsPositions[1].y = B.nBoardHeight/2;
	B.pnDirs[1] = left;

	B.pPtsPositions[2].x = B.nBoardWidth/2;
	B.pPtsPositions[2].y = (B.nBoardHeight*5)/6;
	B.pnDirs[2] = top;

	B.pPtsPositions[3].x = B.nBoardWidth/6;
	B.pPtsPositions[3].y = B.nBoardHeight/2;
	B.pnDirs[3] = right;

	B.nClosingWalls = 0;

	return B;
}

/**
 * @fn         Board init_board_big()
 *
 * @brief      Initialise le grand plateau
 *
 * @param      void
 *
 * @return     Le plateau avec ses murs et 4 positions de départs
 */

Board init_board_big()
{
	Board B;
	B.nBoardWidth = 70;
	B.nBoardHeight = 45;

	B.nNbTunnels = 0;

	B.nNbBonus = 0;

	B.nSize = 2*B.nBoardWidth+2*B.nBoardHeight-4;
	B.pPtsMur = (Point*)malloc(B.nSize*sizeof(Point));

	int i, j, n;
	n = 0;
	for (i = 1; i <= B.nBoardWidth; ++i)
	{
		for (j = 1; j <= B.nBoardHeight; ++j)
		{
			if (i == 1 || j == 1 || i == B.nBoardWidth || j == B.nBoardHeight)
			{
				B.pPtsMur[n].x = (i-1);
				B.pPtsMur[n].y = (j-1);
				n++;
			}
		}
	}

	B.nNbPos = 4;

	B.pPtsPositions = (Point*)malloc(B.nNbPos*sizeof(Point));
	B.pnDirs = (int*)malloc(B.nNbPos*sizeof(int));

	B.pPtsPositions[0].x = B.nBoardWidth/2;
	B.pPtsPositions[0].y = B.nBoardHeight/6;
	B.pnDirs[0] = bot;

	B.pPtsPositions[1].x = (B.nBoardWidth*5)/6;
	B.pPtsPositions[1].y = B.nBoardHeight/2;
	B.pnDirs[1] = left;

	B.pPtsPositions[2].x = B.nBoardWidth/2;
	B.pPtsPositions[2].y = (B.nBoardHeight*5)/6;
	B.pnDirs[2] = top;

	B.pPtsPositions[3].x = B.nBoardWidth/6;
	B.pPtsPositions[3].y = B.nBoardHeight/2;
	B.pnDirs[3] = right;

	B.nClosingWalls = 0;

	return B;
}

/**
 * @fn         Board init_board_1v1()
 *
 * @brief      Initialise le plateau spécifique au 1v1
 *
 * @param      void
 *
 * @details    Pour le 1 contre 1, il n'y a plus que deux positions de départ : à gauche et à droite.
 * @details    La largeur du plateau est aussi deux fois plus grande que sa hauteur.
 *
 * @return     Le plateau avec ses murs et 2 positions de départs
 */

Board init_board_1v1()
{
	Board B;
	B.nBoardHeight = 25;
	B.nBoardWidth = 2*B.nBoardHeight;

	B.nNbTunnels = 0;

	B.nNbBonus = 0;

	B.nSize = 2*B.nBoardWidth+2*B.nBoardHeight-4;
	B.pPtsMur = (Point*)malloc(B.nSize*sizeof(Point));

	int i, j, n;
	n = 0;
	for (i = 1; i <= B.nBoardWidth; ++i)
	{
		for (j = 1; j <= B.nBoardHeight; ++j)
		{
			if (i == 1 || j == 1 || i == B.nBoardWidth || j == B.nBoardHeight)
			{
				B.pPtsMur[n].x = (i-1);
				B.pPtsMur[n].y = (j-1);
				n++;
			}
		}
	}

	B.nNbPos = 2;

	B.pPtsPositions = (Point*)malloc(B.nNbPos*sizeof(Point));
	B.pnDirs = (int*)malloc(B.nNbPos*sizeof(int));

	B.pPtsPositions[0].x = B.nBoardWidth/6;
	B.pPtsPositions[0].y = B.nBoardHeight/2;
	B.pnDirs[0] = right;

	B.pPtsPositions[1].x = B.nBoardWidth*5/6.f;
	B.pPtsPositions[1].y = B.nBoardHeight/2;
	B.pnDirs[1] = left;

	B.nClosingWalls = 0;

	return B;
}

/**
 * @fn 		int belongs_to_tab(Point point, Point* tableau, int taille)
 * 
 * @brief   Teste l'appartenance d'un point (2 coordonnées x et y) à un tableau
 *
 * @param  point    Le point dont on veut tester l'appartenance au tableau
 * @param  tableau  Le tableau de points dans lequel on veut tester l'appartenance
 * @param  taille   La taille du tableau
 *
 * @return 1 si le point appartient au tableau
 * @return 0 sinon
 */

int belongs_to_tab(Point point, Point* tableau, int taille) 
{
	int i=0;
	int flag=0;
	while (flag==0 && i<taille) 
	{
		if ( (tableau[i].x == point.x) && (tableau[i].y == point.y) ) 
		{
			flag=1;
		}
		else 
		{
			i=i+1;
		}
	}
	return flag;
}


/**
 * @fn         int test_collision(Board* mur, Serpent** tab_serpent, int nb_snakes, Point point, int id_snake)
 *
 * @brief      Teste la collision d'un serpent avec le mur ou un autre serpent
 *
 * @param  	mur          	Le plateau contenant un tableau de points correspondant aux emplacements des murs
 * @param  	tab_serpent  	Le tableau de serpents : nécessaire pour la collision avec les autres serpents
 * @param  	nb_snakes  		Le nombre de serpents = longueur du tableau tab_serpent
 * @param 	point 			La tête du serpent à tester
 * @param 	index			La position du serpent à tester dans le tableau des serpents
 *
 * @return  0 s'il n'y a pas de collision
 * @return	1 sinon
 */

int test_collision(Board* mur, Serpent** tab_serpent, int nb_snakes, Point point, int index) 
{
	int i;
	if (point.x <= 0 || point.x >= mur->nBoardWidth || point.y <= 0 || point.y >= mur->nBoardHeight)
	{
		return 1;
	}
	if (belongs_to_tab(point, mur->pPtsMur, mur->nSize)) 
	{
		return 1;
	}
	else 
	{
		for (i=0; i<nb_snakes; i++) 
		{
			if ((i != index && belongs_to_tab(point, tab_serpent[i]->tab, tab_serpent[i]->taille)) || (i == index && belongs_to_tab(point, tab_serpent[i]->tab, tab_serpent[i]->taille-1)))
			{
				return 1;
			}
		}
	}
	return 0;	
}

/**
 * @fn         void add_walls_inside(Board* b)
 *
 * @brief      Ajoute des murs à l'intérieur du plateau
 *
 * @param	   b 		Le plateau créé précédemment
 *
 * @details    Ajoute des murs de formes prédéfinies, selon le nombre de cases qu'il comporte
 * @details    Avec 3 cases, on a soit une ligne, soit un angle
 * @details	   Avec 4 cases, on crée un carré
 * @details    Avec 5 cases, on choisit soit une croix, un carré avec une case en plus ou un grand angle
 * @details	   A la fin, cette fonction supprime les murs trop proches des positions de départ
 *
 * @return     void
 */

void add_walls_inside(Board* b)
{
	int nNbCases = b->nBoardWidth * b->nBoardHeight;
	int nMin = 3; // 3% du nombre total de cases
	int nMax = 7; // 7% du nombre total de cases
	int n = b->nSize;
	int nNbWalls = (rand()%(nMin * nNbCases)+(nMax - nMin)*nNbCases)/100;
	
	b->nSize += nNbWalls;
	b->pPtsMur = (Point*)realloc(b->pPtsMur, b->nSize*sizeof(Point));

	while(n < b->nSize)
	{
		int nNbWallsToAdd = rand()%5+1;
		int randx = rand()%(b->nBoardWidth-2)+1;
		int randy = rand()%(b->nBoardHeight-2)+1;
		b->pPtsMur[n].x = randx;
		b->pPtsMur[n].y = randy;
		int nRandDir = 0, nRandDir2 = 0, nRandForm = 0;
		n++;
		if (nNbWallsToAdd != 1 && n < b->nSize-1)
		{
			
			switch(nNbWallsToAdd)
			{
				case 2:
					nRandDir = rand()%4;
					switch(nRandDir)
					{
						case top:
							b->pPtsMur[n].x = randx;
							b->pPtsMur[n].y = randy - 1;
						break;

						case left:
							b->pPtsMur[n].x = randx - 1;
							b->pPtsMur[n].y = randy;
						break;

						case bot:
							b->pPtsMur[n].x = randx;
							b->pPtsMur[n].y = randy + 1;
						break;

						default:
							b->pPtsMur[n].x = randx + 1;
							b->pPtsMur[n].y = randy;
						break;
					}
					n++;
				break;

				case 3:
					if (n < b->nSize-2)
					{
						nRandForm = rand()%2;
						if (nRandForm == 0) // Ligne
						{
							nRandDir = rand()%2;
							if (nRandDir == 0)
							{
								b->pPtsMur[n].x = randx;
								b->pPtsMur[n].y = randy - 1;
								n++;
								b->pPtsMur[n].x = randx;
								b->pPtsMur[n].y = randy + 1;
							}
							else
							{
								b->pPtsMur[n].x = randx - 1;
								b->pPtsMur[n].y = randy;
								n++;
								b->pPtsMur[n].x = randx + 1;
								b->pPtsMur[n].y = randy;
							}
						}
						else // Angle
						{
							nRandDir = rand()%2;
							nRandDir2 = rand()%2;
							if (nRandDir == 0) // Gauche
							{
								b->pPtsMur[n].x = randx - 1;
								b->pPtsMur[n].y = randy;
								n++;
								if (nRandDir2 == 0) // Haut
								{
									b->pPtsMur[n].x = randx;
									b->pPtsMur[n].y = randy - 1;
								}
								else // Bas
								{
									b->pPtsMur[n].x = randx;
									b->pPtsMur[n].y = randy + 1;
								}
							}
							else // Droite
							{
								b->pPtsMur[n].x = randx + 1;
								b->pPtsMur[n].y = randy;
								n++;
								if (nRandDir2 == 0) // Haut
								{
									b->pPtsMur[n].x = randx;
									b->pPtsMur[n].y = randy - 1;
								}
								else // Bas
								{
									b->pPtsMur[n].x = randx;
									b->pPtsMur[n].y = randy + 1;
								}
							}
						}
						n++;
					}
				break;

				case 4: // La case de départ est celle en bas à gauche du carré
					if (n < b->nSize-3)
					{
						// Haut gauche
						b->pPtsMur[n].x = randx;
						b->pPtsMur[n].y = randy - 1;
						n++;
						// Haut droite
						b->pPtsMur[n].x = randx + 1;
						b->pPtsMur[n].y = randy + 1;
						n++;
						// Bas droite
						b->pPtsMur[n].x = randx + 1;
						b->pPtsMur[n].y = randy;
						n++;
					}
				break;

				default:
					if (n < b->nSize-4)
					{
						nRandForm = rand()%3;
						if (nRandForm == 0) // Croix
						{
							b->pPtsMur[n].x = randx - 1;
							b->pPtsMur[n].y = randy;
							n++;
							b->pPtsMur[n].x = randx;
							b->pPtsMur[n].y = randy - 1;
							n++;
							b->pPtsMur[n].x = randx + 1;
							b->pPtsMur[n].y = randy;
							n++;
							b->pPtsMur[n].x = randx;
							b->pPtsMur[n].y = randy + 1;
							n++;
						}
						else if (nRandForm == 1 && randx < b->nBoardWidth-1 && randx > 1 && randy < b->nBoardHeight-1 && randy > 1) // Angle
						{
							nRandDir = rand()%2;
							nRandDir2 = rand()%2;
							if (nRandDir == 0) // Gauche
							{
								b->pPtsMur[n].x = randx - 1;
								b->pPtsMur[n].y = randy;
								n++;
								b->pPtsMur[n].x = randx - 2;
								b->pPtsMur[n].y = randy;
								n++;
								if (nRandDir2 == 0) // Haut
								{
									b->pPtsMur[n].x = randx;
									b->pPtsMur[n].y = randy - 1;
									n++;
									b->pPtsMur[n].x = randx;
									b->pPtsMur[n].y = randy - 2;
								}
								else // Bas
								{
									b->pPtsMur[n].x = randx;
									b->pPtsMur[n].y = randy + 1;
									n++;
									b->pPtsMur[n].x = randx;
									b->pPtsMur[n].y = randy + 2;
								}
							}
							else // Droite
							{
								b->pPtsMur[n].x = randx + 1;
								b->pPtsMur[n].y = randy;
								n++;
								b->pPtsMur[n].x = randx + 2;
								b->pPtsMur[n].y = randy;
								n++;
								if (nRandDir2 == 0) // Haut
								{
									b->pPtsMur[n].x = randx;
									b->pPtsMur[n].y = randy - 1;
									n++;
									b->pPtsMur[n].x = randx;
									b->pPtsMur[n].y = randy - 2;
								}
								else // Bas
								{
									b->pPtsMur[n].x = randx;
									b->pPtsMur[n].y = randy + 1;
									n++;
									b->pPtsMur[n].x = randx;
									b->pPtsMur[n].y = randy + 2;
								}
							}
							n++;
						}
						else // Carré avec une case en plus
						{
							if (randx < b->nBoardWidth - 1 && randx > 1 && randy < b->nBoardHeight - 1 && randy > 1)
							{
								// Haut gauche
								b->pPtsMur[n].x = randx;
								b->pPtsMur[n].y = randy - 1;
								n++;
								// Haut droite
								b->pPtsMur[n].x = randx + 1;
								b->pPtsMur[n].y = randy + 1;
								n++;
								// Bas droite
								b->pPtsMur[n].x = randx + 1;
								b->pPtsMur[n].y = randy;
								n++;
								nRandDir = rand()%4;
								switch(nRandDir)
								{
									case top:
										b->pPtsMur[n].x = randx + 1;
										b->pPtsMur[n].y = randy - 2;
									break;

									case left:
										b->pPtsMur[n].x = randx - 1;
										b->pPtsMur[n].y = randy - 1;
									break;

									case bot:
										b->pPtsMur[n].x = randx;
										b->pPtsMur[n].y = randy + 1;
									break;

									default:
										b->pPtsMur[n].x = randx + 2;
										b->pPtsMur[n].y = randy;
									break;
								}
								n++;
							}
						}
					}
				break;
			}
		}
	}
	delete_too_close_walls(b);
}

/**
 * @fn         	void delete_too_close_walls(Board* b)
 *
 * @brief      	Supprime les murs trop proches des positions de départ
 *
 * @param	   	b 		Le plateau créé précédemment
 *
 * @details 	En partant des positions de départ, on supprime les murs à moins de 5 cases de celles-ci dans les directions données au départ lors de l'initialisation
 *
 * @return     	void
 */

void delete_too_close_walls(Board* b)
{
	int i, j, k;
	Point p;
	for (i = 0; i < b->nNbPos; i++)
	{
		p.x = b->pPtsPositions[i].x;
		p.y = b->pPtsPositions[i].y;
		// On supprime les murs qui sont à moins de 5 cases d'une position de départ
		for (j = 0; j < 6; j++)
		{
			k = 0;
			while(k < b->nSize)
			{
				if (b->pPtsMur[k].x == p.x && b->pPtsMur[k].y == p.y)
				{
					if (k < b->nSize-1)
					{
						b->pPtsMur[k] = b->pPtsMur[b->nSize-1];
					}
					b->nSize--;
					b->pPtsMur = (Point*) realloc(b->pPtsMur, b->nSize*sizeof(Point));
				}
				k++;
			}
			switch(b->pnDirs[i])
			{
				case left:
					p.x--;
				break;

				case top:
					p.y--;
				break;

				case right:
					p.x++;
				break;

				case bot:
					p.y++;
				break;
			}
		}
	}
}

/**
 * @fn         is_cell_free(Point p, Board* b, Serpent** tab_serpent, int nb_snakes)
 *
 * @brief      Teste si une case est libre
 *
 * @param	   p 			La case à tester
 * @param	   b 			Le plateau de jeu
 * @param	   tab_serpent 	Le tableau contenant tous les serpents jouant dans la partie
 * @param 	   nb_snakes	Le nombre de serpents dans la partie
 *
 * @details	   Utilise la fonction appartient_tableau pour savoir si la case testée est contenue dans le tableau des murs, dans le corps d'un des serpents, dans le tableau des tunnels ou dans le tableau des bonus.
 *
 * @return     1 si la case est vide
 * @return	   0 sinon
 */

int is_cell_free(Point p, Board* b, Serpent** tab_serpent, int nb_snakes)
{
	if (belongs_to_tab(p, b->pPtsMur, b->nSize))
	{
		return 0;
	}
	int i;
	for (i = 0; i < nb_snakes; i++)
	{
		if (belongs_to_tab(p, tab_serpent[i]->tab, tab_serpent[i]->taille))
		{
			return 0;
		}
	}
	for (i = 0; i < b->nNbTunnels; i++)
	{
		if (belongs_to_tunnel(p, b->pTunnels[i]))
		{
			return 0;
		}
	}
	for (i = 0; i < b->nNbBonus; i++)
	{
		if (b->pTabBonus[i]->point.x == p.x && b->pTabBonus[i]->point.y == p.y)
		{
			return 0;
		}
	}
	return 1;
}

/**
 * @fn         okay_to_add_wall(Point p, Board* b, Serpent** tab_serpent, int nb_snakes)
 *
 * @brief      Teste si on peut ajouter un mur
 *
 * @param	   p 			Case à tester
 * @param	   b 			Le plateau de jeu
 * @param	   tab_serpent 	Tableau contenant tous les serpents jouant dans la partie
 * @param 	   nb_snakes	Nombre de serpents dans la partie
 *
 * @details	   Utilise la fonction is_cell_free pour savoir si la case testée est libre et vérifie que le mur à ajouter n'est pas situé à moins de trois cases de la tête d'un serpent
 *
 * @return     1 si on peut ajouter le mur
 * @return 	   0 sinon
 */

int okay_to_add_wall(Point p, Board* b, Serpent** tab_serpent, int nb_snakes)
{
	if (!is_cell_free(p, b, tab_serpent, nb_snakes))
	{
		return 0;
	}
	int i;
	for (i = 0;i < nb_snakes; i++)
	{
		switch(tab_serpent[i]->dir)
		{
			case top:
			if (p.y == tab_serpent[i]->tete.y-1 || p.y == tab_serpent[i]->tete.y-2 || p.y == tab_serpent[i]->tete.y-3)
			{
				return 0;
			}
			break;

			case left:
			if (p.x == tab_serpent[i]->tete.x-1 || p.x == tab_serpent[i]->tete.x-2 || p.x == tab_serpent[i]->tete.x-3)
			{
				return 0;
			}
			break;

			case bot:
			if (p.y == tab_serpent[i]->tete.y+1 || p.y == tab_serpent[i]->tete.y+2 || p.y == tab_serpent[i]->tete.y+3)
			{
				return 0;
			}
			break;

			case right:
			if (p.x == tab_serpent[i]->tete.x+1 || p.x == tab_serpent[i]->tete.x+2 || p.x == tab_serpent[i]->tete.x+3)
			{
				return 0;
			}
			break;
		}
	}
	return 1;
}

/**
 * @fn         int nb_obstacles_around_3(Point centre, Board* b, Serpent** tab_serpent, int nb_snakes, Serpent* snake)
 *
 * @brief     	Compte le nombre d'obstacles autour du serpent passé en paramètre dans un carré de taille 3
 *
 * @param	   centre 		Le centre du carré à tester (ne fonctionne qu'avec un carré de taille 3x3)
 * @param 	   b 			Le plateau de jeu
 * @param	   tab_serpent 	Le tableau contenant tous les serpents jouant dans la partie
 * @param 	   nb_snakes	Le nombre de serpents dans la partie
 * @param 	   snake 		Le serpent dont on veut connaître le nombre d'obstacles dans les environs
 *
 * @details 	La fonction génère tous les points du carré puis teste s'il y a une collision en chaque point.
 * @details 	Si oui, on incrémente le nombre d'obstacles dans le carré
 *
 * @return     Le nombre d'obstacles dans un carré de taille 3 autour du serpent passé en paramètre
 */

int nb_obstacles_around_3(Point centre, Board* b, Serpent** tab_serpent, int nb_snakes, Serpent* snake)
{
	int i, j;
	Point p;
	int res = 0;
	for (i = centre.x-1; i <= centre.x+1; i++)
	{
		for (j = centre.y-1; j <= centre.y+1; j++)
		{
			p.x = i;
			p.y = j;
			if (test_collision(b, tab_serpent, nb_snakes, p, snake->id) == 1)
			{
				res++;
			}
		}
	}
	return res;
}

/**
 * @fn         int nb_obstacles_around_5(Point centre, Board* b, Serpent** tab_serpent, int nb_snakes, Serpent* snake)
 *
 * @brief     	Compte le nombre d'obstacles autour du serpent passé en paramètre dans un carré de taille 5
 *
 * @param	   centre 		Le centre du carré à tester (ne fonctionne qu'avec un carré de taille 5x5)
 * @param 	   b 			Le plateau de jeu
 * @param	   tab_serpent 	Le tableau contenant tous les serpents jouant dans la partie
 * @param 	   nb_snakes	Le nombre de serpents dans la partie
 * @param 	   snake 		Le serpent dont on veut connaître le nombre d'obstacles dans les environs
 *
 * @details 	La fonction génère tous les points du carré puis teste s'il y a une collision en chaque point.
 * @details 	Si oui, on incrémente le nombre d'obstacles dans le carré
 *
 * @return     Le nombre d'obstacles dans un carré de taille 5 autour du serpent passé en paramètre
 */

int nb_obstacles_around_5(Point centre, Board* b, Serpent** tab_serpent, int nb_snakes, Serpent* snake)
{
	int i, j;
	Point p;
	int res = 0;
	for (i = centre.x-2; i <= centre.x+2; i++)
	{
		for (j = centre.y-2; j <= centre.y+2; j++)
		{
			p.x = i;
			p.y = j;
			if (test_collision(b, tab_serpent, nb_snakes, p, snake->id) == 1)
			{
				res++;
			}
		}
	}
	return res;
}

/**
 * @fn         add_wall(Board* b, Serpent** tab_serpent, int nb_snakes)
 *
 * @brief      Ajoute un nouveau mur sur le plateau
 *
 * @param	   b 			Le plateau de jeu
 * @param	   tab_serpent 	Le tableau contenant tous les serpents jouant dans la partie
 * @param 	   nb_snakes	Le nombre de serpents dans la partie
 *
 * @details	   Génère un mur à une position aléatoire tant qu'il n'a pas une position correcte puis l'ajoute au plateau
 *
 * @return     void
 */

void add_wall(Board* b, Serpent** tab_serpent, int nb_snakes)
{
	Point p;
	p.x = rand()%(b->nBoardWidth-2)+1;
	p.y = rand()%(b->nBoardHeight-2)+1;
	while(!is_cell_free(p, b, tab_serpent, nb_snakes))
	{
		p.x = rand()%(b->nBoardWidth-2)+1;
		p.y = rand()%(b->nBoardHeight-2)+1;
	}
	b->nSize++;
	b->pPtsMur = (Point*) realloc(b->pPtsMur, b->nSize*sizeof(Point));
	b->pPtsMur[b->nSize-1] = p;
}

/**
 * @fn 		int belongs_to_tunnel(Point point, Tunnel* t)
 * 
 * @brief  Teste l'appartenance d'un point (2 coordonnées x et y) à un tunnel (entrée et sorties)
 *
 * @param  p    Le point dont on veut tester l'appartenance au tunnel
 * @param  t  	Le tunnel dans lequel on veut tester l'appartenance
 *
 * @return 1 si le point appartient au tunnel
 * @return 0 sinon
 */

int belongs_to_tunnel(Point p, Tunnel* t)
{
	if (p.x == t->entree.x && p.y == t->entree.y)
	{
		return 1;
	}
	if (belongs_to_tab(p, t->sorties, t->nNbSorties))
	{
		return 1;
	}
	return 0;
}

/**
 * @fn         add_tunnels(Board* b, Serpent** tab_serpent, int nb_snakes)
 *
 * @brief      Ajoute des tunnels sur le plateau
 *
 * @param	   b 			Le plateau de jeu
 * @param	   tab_serpent 	Le tableau contenant tous les serpents jouant dans la partie
 * @param 	   nb_snakes	Le nombre de serpents dans la partie
 *
 * @details	   Choisis une case aléatoire pour y construire une entrée de tunnel puis n autres cases pour les sorties
 *
 * @return     void
 */

void add_tunnels(Board* b, Serpent** tab_serpent, int nb_snakes)
{
	int nb_tunnels = rand()%3+1;
	Point p, p2;
	int i, j;

	for (i = 0; i < nb_tunnels; i++)
	{
		p.x = rand()%(b->nBoardWidth-2)+1;
		p.y = rand()%(b->nBoardHeight-2)+1;
		while(!is_cell_free(p, b, tab_serpent, nb_snakes))
		{
			p.x = rand()%(b->nBoardWidth-2)+1;
			p.y = rand()%(b->nBoardHeight-2)+1;
		}
		b->nNbTunnels++;

		if (i == 0)
		{
			b->pTunnels = (Tunnel**)malloc(sizeof(Tunnel *));
		}
		else
		{
			b->pTunnels = realloc(b->pTunnels, b->nNbTunnels*sizeof(Tunnel *));
		}

		b->pTunnels[i] = (Tunnel *) malloc(sizeof(Tunnel));

		b->pTunnels[i]->entree = p;
		b->pTunnels[i]->nNbSorties = 0;
		int nb_sorties = rand()%3+1;

		for (j = 0; j < nb_sorties; j++)
		{
			p2.x = rand()%(b->nBoardWidth-10)+5;
			p2.y = rand()%(b->nBoardHeight-10)+5;
			while(!is_cell_free(p2, b, tab_serpent, nb_snakes))
			{
				p2.x = rand()%(b->nBoardWidth-10)+5;
				p2.y = rand()%(b->nBoardHeight-10)+5;
			}
			b->pTunnels[i]->nNbSorties++;
			if (j == 0)
			{
				b->pTunnels[i]->sorties = (Point *) malloc(sizeof(Point));
			}
			else
			{
				b->pTunnels[i]->sorties = realloc(b->pTunnels[i]->sorties, b->pTunnels[i]->nNbSorties*sizeof(Point));
			}
			b->pTunnels[i]->sorties[j] = p2;
		}
	}
}

/**
 * @fn 		 	void handle_tunnels(Serpent* s, Board* b)
 *
 * @brief      	Permet la gestion des tunnels
 *
 * @param 		s 	  Serpent à tester
 * @param		b     Plateau contenant le tableau des tunnels
 * 
 * @details		Teste si un serpent arrive sur une entrée d'un tunnel puis le fait entrer dans ce tunnel le cas échéant
 *
 * @return 		void
 */


void handle_tunnels(Serpent* s, Board* b)
{
	int i;
	for (i = 0; i < b->nNbTunnels; i++)
	{
		Tunnel* t = b->pTunnels[i];
		if (s->tete.x == t->entree.x && s->tete.y == t->entree.y)
		{
			enter_tunnel(s, t);
		}
	}
}

/**
 * @fn 		 	void free_board(Board b)
 *
 * @brief      	Supprime la mémoire allouée au plateau
 *
 * @param		b     Plateau dont on veut supprimer la mémoire
 * 
 * @details 	Supprime les points du mur, les points correspondant aux positions de départ, la direction des positions de départ, les tunnels et les bonus du plateau
 *
 * @return 		void
 */

void free_board(Board b)
{
	free(b.pPtsMur);
	free(b.pPtsPositions);
	free(b.pnDirs);
	int i;
	for (i = 0; i < b.nNbTunnels; i++)
	{
		free(b.pTunnels[i]->sorties);
		free(b.pTunnels[i]);
	}
	if (b.nNbTunnels > 0)
	{
		free(b.pTunnels);
	}
	for (i = 0; i < b.nNbBonus; i++)
	{
		free(b.pTabBonus[i]);
	}
	if (b.nNbBonus > 0)
	{
		free(b.pTabBonus);
	}
}