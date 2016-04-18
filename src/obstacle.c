/**
 * @file obstacle.c
 * @author Les Mixtes
 * @date 17/04/2016
 * @brief Fichier permettant la création des murs et des positions de départ des serpents
 * @details Contient l'initialisation du "plateau" et des murs
 */

#include <stdio.h>
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

	return B;
}

/**
 * @fn         Board init_board_1v1()
 *
 * @brief      Initialise le plateau spécifique au 1v1
 *
 * @param      void
 *
 * @return     Le plateau avec ses murs et 2 positions de départs
 */

Board init_board_1v1()
{
	Board B;
	B.nBoardWidth = 50;
	B.nBoardHeight = 25;

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

	return B;
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

int appartient_tableau(Point point, Point* tableau, int taille) 
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
 * @param  	mur          	Plateau contenant un tableau de points correspondant aux emplacements des murs
 * @param  	tab_serpent  	Tableau de serpent : nécessaire pour la collision avec les autres serpents
 * @param  	nb_snakes  		Nombre de serpents = longueur du tableau tab_serpent
 * @param 	point 			Tête du serpent à tester
 * @param 	id_snake		Identifiant du serpent à tester
 *
 * @return  0 s'il n'y a pas de collision
 * @return	Sinon, l'id du serpent qui entre en collision avec le mur ou un autre serpent
 */

int test_collision(Board* mur, Serpent** tab_serpent, int nb_snakes, Point point, int id_snake) 
{
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
 * @fn         void add_walls_inside(Board* b, int width, int height)
 *
 * @brief      Ajoute des murs à l'intérieur du plateau
 *
 * @param	   b 		Le plateau créé précédemment
 *
 * @return     void
 */

void add_walls_inside(Board* b)
{
	int nNbCases = b->nBoardWidth * b->nBoardHeight;
	int nMin = 5; // 5% du nombre total de cases
	int nMax = 10; // 10% du nombre total de cases
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
 * @fn         void delete_too_close_walls(Board* b)
 *
 * @brief      Supprime les murs trop proches des positions de départ
 *
 * @param	   b 		Le plateau créé précédemment
 *
 * @details 	En partant des positions de départ, on supprime les murs à moins de 5 cases de celles-ci dans les directions données au départ lors de l'initialisation
 *
 * @return     void
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
 * @param	   p 			Case à tester
 * @param	   b 			Le plateau de jeu
 * @param	   tab_serpent 	Tableau contenant tous les serpents jouant dans la partie
 * @param 	   nb_snakes	Nombre de serpents dans la partie
 *
 * @details	   Utilise la fonction appartient_tableau pour savoir si la case testée est contenue dans le tableau des murs ou dans le corps d'un des serpents du jeu.
 *
 * @return     1 si la case est vide, 0 sinon
 */

int is_cell_free(Point p, Board* b, Serpent** tab_serpent, int nb_snakes)
{
	if (appartient_tableau(p, b->pPtsMur, b->nSize))
	{
		return 0;
	}
	int i;
	for (i = 0; i < nb_snakes; i++)
	{
		if (appartient_tableau(p, tab_serpent[i]->tab, tab_serpent[i]->taille))
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
 * @return     1 si on peut ajouter le mur, 0 sinon
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
 * @fn         add_wall(Board* b, Serpent** tab_serpent, int nb_snakes)
 *
 * @brief      Ajoute un nouveau mur sur le plateau
 *
 * @param	   b 			Le plateau de jeu
 * @param	   tab_serpent 	Tableau contenant tous les serpents jouant dans la partie
 * @param 	   nb_snakes	Nombre de serpents dans la partie
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
	while(!okay_to_add_wall(p, b, tab_serpent, nb_snakes))
	{
		p.x = rand()%(b->nBoardWidth-2)+1;
		p.y = rand()%(b->nBoardHeight-2)+1;
	}
	b->nSize++;
	b->pPtsMur = (Point*) realloc(b->pPtsMur, b->nSize*sizeof(Point));
	b->pPtsMur[b->nSize-1] = p;
}

void free_board(Board b)
{
	 free(b.pPtsMur);
     free(b.pPtsPositions);
     free(b.pnDirs);
     
}
