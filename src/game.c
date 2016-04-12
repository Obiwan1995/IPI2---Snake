/**
 * @file game.c
 * @author Les Mixtes
 * @date 19/03/2016
 * @brief Fichier qui gère le jeu
 * @details Contient la boucle principale du jeu ainsi que les divers affichages
 */

 #include "game.h"
 #include <stdio.h>

/**
 * @fn         play(SDL_Surface* sdlScreen, int nbSnakes, int nBoardWidth int nBoardHeight, int nSpeedInit)
 *
 * @brief      Fait tourner le jeu, boucle principale
 *
 * @param       sdlScreen       L'écran affiché à l'utilisateur
 * @param       nbSnakes        Le nombre de serpents
 *
 * @return     void
 */

void play(SDL_Surface* sdlScreen, Board board, int nbSnakes, int nSpeedInit)
{
    srand(time(NULL));
    SDL_Event event;

    Serpent** snakes = malloc(nbSnakes * sizeof(Serpent *));
    int i;
    for (i = 0; i < nbSnakes; i++)
    {
        snakes[i] = malloc(sizeof(Serpent));

        int rng = rand()%board.nNbPos;
        init_snake(snakes[i], (i+1), nSpeedInit, board.pnDirs[rng], board.pPtsPositions[rng]);

        board.pPtsPositions[rng] = board.pPtsPositions[board.nNbPos-1];
        board.pnDirs[rng] = board.pnDirs[board.nNbPos-1];
        board.nNbPos--;
        if(board.nNbPos < 0)
        {
            fprintf(stderr, "Trop de snake pour les positions disponibles\n");
            exit(1);
        }
    }

    int nDir = 0;
    int nKeyUp = 0;
    int nInGame = 1;
    int nResGame = 0;
    int actualTime = 0;
    int previousTime = 0;

    while(nInGame && !nResGame)
    {
        actualTime = SDL_GetTicks();
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                nInGame = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: // Leave Game
                        nInGame = 0;
                        break;
                    case SDLK_d:
                    case SDLK_RIGHT:
                        if (nKeyUp)
                            nDir = 1;
                        nKeyUp = 0;
                        break;
                    case SDLK_q:
                    case SDLK_LEFT:
                        if (nKeyUp)
                            nDir = 2;
                        nKeyUp = 0;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYUP:
                        nKeyUp = 1;
            default:
                break;
        }

        if (actualTime - previousTime > snakes[0]->vitesse) {
            switch(nDir)
            {
                case 0:
                    Forward(snakes[0]);
                    break;
                case 1:
                    Right(snakes[0]);
                    break;
                case 2:
                    Left(snakes[0]);
                    break;
            }

            nResGame = test_collision(&board, snakes, nbSnakes);

            SDL_FillRect(sdlScreen, NULL, SDL_MapRGB(sdlScreen->format, 255, 255, 255)); 

            int i;
            for (i=0; i< board.nSize; i++)
            {
                paint(sdlScreen, board.pPtsMur[i].x, board.pPtsMur[i].y, 0);
            }

            for (i=0; i< snakes[0]->taille; i++)
            {
                paint(sdlScreen, snakes[0]->tab[i].x, snakes[0]->tab[i].y, 1);
            }

            SDL_Flip(sdlScreen);

            nDir = 0;
            previousTime = actualTime;
        }

    }

}

/**
 * @fn         paint(SDL_Surface* sdlScreen, int x, int y, int nId)
 *
 * @brief      Colorie SIZE_CASE*SIZE_CASE pixels en x, y, pour les serpents ou le mur (la couleur dépend du nId)
 *
 * @param       sdlScreen     L'écran affiché à l'utilisateur
 * @param       x             Le x de la case à colorier
 * @param       y             Le y de la case à colorier
 * @param       nId           L'identifiant du propriétaire de la case à colorier
 *
 * @return     void
 */

void paint(SDL_Surface* sdlScreen, int x, int y, int nId)
{
    Uint32 color;

    switch(nId)
    {
        case 0:
            color = BLACK;
            break;
        case 1:
            color = GREEN;
            break;
        case 2:
            color = BLUE;
            break;
        default:
            exit(1);
    }

    int i, j;
    for (i = 0; i != SIZE_CASE; ++i)
    {
        for (j = 0; j != SIZE_CASE; ++j)
        {
            if (!((i == 0 || i == SIZE_CASE || i == 1 || i == SIZE_CASE-1) && (j == 0 || j == SIZE_CASE || j == 1 || j == SIZE_CASE-1)))
                setPixel(sdlScreen, x*SIZE_CASE+i, y*SIZE_CASE+j, color);
        }    
    }
}


/**
 * @fn         setPixel(SDL_Surface *surface, int x, int y, Uint32 color)
 *
 * @brief      Colorie un pixel à l'écran
 *
 * @param       surface       L'écran affiché à l'utilisateur
 * @param       x             La coordonnée x du pixel à colorier
 * @param       y             La coordonnée y du pixel à colorier
 * @param       color         La couleur utilisée pour colorier le pixel
 *
 * @return     void
 */

void setPixel(SDL_Surface *surface, int x, int y, Uint32 color)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
     
    if(bpp == 1)
        *p = color;
    else if(bpp == 2)
        *(Uint16*)p = color;
    else if(bpp == 4)
        *(Uint32*)p = color;
    else
    {
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
        {
            p[0] = (color >> 16) & 0xff;
            p[1] = (color >> 8) & 0xff;
            p[2] = color & 0xff;
        }
        else
        {
            p[0] = color & 0xff;
            p[1] = (color >> 8) & 0xff;
            p[2] = (color >> 16) & 0xff;
        }
    }
}
