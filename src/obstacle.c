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

	B.nSize = 2*BOARD_WIDTH+2*BOARD_HEIGHT-4;
	B.pPtsMur = (Point*)malloc(B.nSize*sizeof(Point));

	int i, j, n;
	n = 0;
	for (i = 1; i <= BOARD_WIDTH; ++i)
	{
		for (j = 1; j <= BOARD_HEIGHT; ++j)
		{
			if (i == 1 || j == 1 || i == BOARD_WIDTH || j == BOARD_HEIGHT)
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

	B.pPtsPositions[0].x = BOARD_WIDTH/2;
	B.pPtsPositions[0].y = BOARD_HEIGHT/6;
	B.pnDirs[0] = 3;

	B.pPtsPositions[1].x = (BOARD_WIDTH*5)/6;
	B.pPtsPositions[1].y = BOARD_HEIGHT/2;
	B.pnDirs[1] = 4;

	B.pPtsPositions[2].x = BOARD_WIDTH/2;
	B.pPtsPositions[2].y = (BOARD_HEIGHT*5)/6;
	B.pnDirs[2] = 1;

	B.pPtsPositions[3].x = BOARD_WIDTH/6;
	B.pPtsPositions[3].y = BOARD_HEIGHT/2;
	B.pnDirs[3] = 2;

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

	B.nSize = 2*BOARD_WIDTH+2*BOARD_HEIGHT-4;
	B.pPtsMur = (Point*)malloc(B.nSize*sizeof(Point));

	int i, j, n;
	n = 0;
	for (i = 1; i <= BOARD_WIDTH; ++i)
	{
		for (j = 1; j <= BOARD_HEIGHT; ++j)
		{
			if (i == 1 || j == 1 || i == BOARD_WIDTH || j == BOARD_HEIGHT)
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

	B.pPtsPositions[0].x = BOARD_WIDTH/6;
	B.pPtsPositions[0].y = BOARD_HEIGHT/2;
	B.pnDirs[0] = 2;

	B.pPtsPositions[1].x = BOARD_WIDTH*5/6.f;
	B.pPtsPositions[1].y = BOARD_HEIGHT/2;
	B.pnDirs[1] = 4;

	return B;
}

/**
 * @fn         Board init_board_walls()
 *
 * @brief      Initialise le plateau contenant des murs au milieu
 *
 * @param      void
 *
 * @return     Le plateau avec ses murs et 4 positions de départs
 */

Board init_board_walls()
{
	Board B;
	
	B.nSize = 2*BOARD_WIDTH+2*BOARD_HEIGHT-4;
	B.pPtsMur = (Point*)malloc(B.nSize*sizeof(Point));

	int i, j, n;
	n = 0;
	for (i = 1; i <= BOARD_WIDTH; ++i)
	{
		for (j = 1; j <= BOARD_HEIGHT; ++j)
		{
			if (i == 1 || j == 1 || i == BOARD_WIDTH || j == BOARD_HEIGHT)
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

	
	B.pPtsPositions[0].x = BOARD_WIDTH/2;
	B.pPtsPositions[0].y = BOARD_HEIGHT/10;
	B.pnDirs[0] = 3;

	B.pPtsPositions[1].x = (BOARD_WIDTH*9)/10;
	B.pPtsPositions[1].y = BOARD_HEIGHT/2;
	B.pnDirs[1] = 4;

	B.pPtsPositions[2].x = BOARD_WIDTH/2;
	B.pPtsPositions[2].y = (BOARD_HEIGHT*9)/10;
	B.pnDirs[2] = 1;

	B.pPtsPositions[3].x = BOARD_WIDTH/10;
	B.pPtsPositions[3].y = BOARD_HEIGHT/2;
	B.pnDirs[3] = 2;

	return B;
}

void free_board(Board* b)
{
	
}