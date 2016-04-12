/**
 * @file obstacle.c
 * @author Les Mixtes
 * @date 21/03/2016
 * @brief Fichier permettant la création des murs et des positions de départ des serpents
 * @details Contient l'initialisation du "plateau"
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
	B.nBoardWidth = 35;
	B.nBoardHeight = 35;

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
	B.pnDirs[0] = 2;

	B.pPtsPositions[1].x = B.nBoardWidth*5/6.f;
	B.pPtsPositions[1].y = B.nBoardHeight/2;
	B.pnDirs[1] = 4;

	return B;
}

/**
 * @fn         void add_walls_inside(Board* b, int width, int height)
 *
 * @brief      Ajoute des murs à l'intérieur du plateau
 *
 * @param	   b 		Le plateau créé précédemment
 * @param	   width 	La largeur du plateau
 * @param	   height 	La hauteur du plateau
 *
 * @return     void
 */

void add_walls_inside(Board* b)
{
	int nNbCases = b->nBoardWidth * b->nBoardHeight;
	double nMin = 0.01; // 1% du nombre total de cases
	double nMax = 0.03; // 3% du nombre total de cases
	int n = b->nSize;
	int nNbWalls = rand()%((int)(nMin * nNbCases))+(nMax - nMin)*nNbCases;
	
	b->nSize += nNbWalls;
	b->pPtsMur = (Point*)realloc(b->pPtsMur, b->nSize*sizeof(Point));

	int i;
	for (i = 0; i < nNbWalls; i++)
	{
		int randx = rand()%(b->nBoardWidth);
		int randy = rand()%(b->nBoardHeight);
		/*while (!wall_ok(randx, randy, n))
		{
			randx = rand()%width;
			randy = rand()%height;
		}*/
		b->pPtsMur[n].x = randx;
		b->pPtsMur[n].y = randy;
		n++;
	}
}

int wall_ok(Board* b, int x, int y, int taille)
{
	return 1;
}

void free_board(Board* b)
{
	
}
