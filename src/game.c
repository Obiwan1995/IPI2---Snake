/**
 * @file game.c
 * @author Les Mixtes
 * @date 7/05/2016
 * @brief Fichier qui gère le jeu
 * @details Contient la boucle principale du jeu ainsi que les divers affichages
 */

 #include "game.h"
 #include "ia.c"
 #include <stdio.h>
 #include <unistd.h>

/**
 * @fn         play(SDL_Surface* sdlScreen, Board board, int nbSnakes, int nSpeedInit)
 *
 * @brief      Fait tourner le jeu, boucle principale
 *
 * @param       sdlScreen       L'écran affiché à l'utilisateur
 * @param       board           Le plateau de jeu
 * @param       nbSnakes        Le nombre de serpents
 * @param       nSpeedInit      La vitesse initiale de tous les serpents
 *
 * @details     Initialise les serpents puis le plateau avant de rentrer dans la boucle de jeu qui ne s'arrête que lorsqu'une collision est détectée.
 *
 * @return     void
 */

void play(SDL_Surface* sdlScreen, Board board, int nbSnakes, int nSpeedInit)
{
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
            fprintf(stderr, "Trop de snakes pour les positions disponibles\n");
            exit(1);
        }
    }

    //premier affichage
    SDL_FillRect(sdlScreen, NULL, SDL_MapRGB(sdlScreen->format, 255, 255, 255)); 

    for (i=0; i< board.nSize; i++)
    {
        paint(sdlScreen, board.pPtsMur[i].x, board.pPtsMur[i].y, 0);
    }
    for (i = 0; i < board.nNbTunnels; i++)
    {
        paint(sdlScreen, board.pTunnels[i]->entree.x, board.pTunnels[i]->entree.y, 5);
    }
    int j;
    for (j = 0; j < nbSnakes; j++)
    {
        for (i=0; i < snakes[j]->taille; i++)
        {
            paint(sdlScreen, snakes[j]->tab[i].x, snakes[j]->tab[i].y, j+1);
        }
    }

    int k;
    for (k = 0; k < 3; ++k)
    {
        int id;
        switch(k)
        {
            case 0:
                id = 2;
                break;
            case 1:
                id = 4;
                break;
            case 2:
                id = 1;
                break;
        }
        for (j = -1; j < 2; ++j)
        {
            for (i = -1; i < 2; ++i)
            {
                paint(sdlScreen, (board.nBoardWidth/2)+j, (board.nBoardHeight/2)+i, id);
            }
        }
        SDL_Flip(sdlScreen);
        sleep(STARTING_TIMER);
    }


    add_tunnels(&board, snakes, nbSnakes);

    int nDir = 0;
    int nKeyUp = 0;
    int nInGame = 1;
    int nRandBonus = P_ADD_BONUS;
    int actualTime = 0;
    int nWallsRow = 1;
    int closingWallsTimer = 0;
    int pause = 0;

    int nbSnakesAlive = nbSnakes;

    int previousTime[nbSnakes+1];
    for (i=0; i < nbSnakes+1; i++)
    {
        previousTime[i] = 0;
    }

    while(nInGame)
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
                    case SDLK_p:
                        if (nKeyUp)
                        {
                            if (pause)
                            {
                                pause = 0;
                                nDir = 0;
                            }
                            else
                            {
                                pause = 1;
                            }
                        }
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

        if (pause == 0)
        {
            if (board.nClosingWalls && actualTime - closingWallsTimer > WALLS_CLOSING_TIMER)
            {
                close_walls(&board, nWallsRow);
                closingWallsTimer = SDL_GetTicks();
                nWallsRow++;
            }

            for (k = 0; k < nbSnakes; ++k)
            {
                int k;
                for (k = 0; k < nbSnakes; ++k)
                {
                    if (actualTime - previousTime[k] > snakes[k]->vitesse && snakes[k]->vivant)
                    {
                        previousTime[k] = actualTime;

                        if (k == 0)
                        {
                            if (snakes[k]->reverse)
                            {
                                if (nDir == 1)
                                {
                                    nDir = 2;
                                }
                                else if (nDir == 2)
                                {
                                    nDir = 1;
                                }
                            }
                            switch(nDir)
                            {
                                case 0:
                                    Forward(snakes[k]);
                                    break;
                                case 1:
                                    Right(snakes[k]);
                                    break;
                                case 2:
                                    Left(snakes[k]);
                                    break;
                            }
                            nDir = 0;
                        }
                        else
                        {
                            move_def_ia(snakes[k], board, nbSnakes, snakes);
                        }

                        handle_tunnels(snakes[k], &board);
                        
                        if(test_collision(&board, snakes, nbSnakes, snakes[k]->tete, k))
                        {
                            snakes[k]->vivant = 0;
                            --nbSnakesAlive;
                            if (nbSnakesAlive < 2)
                                nInGame = 0;
                        }
                        else
                        {
                            for (i = 0; i < board.nNbBonus; i++)
                            {
                                Bonus* bonus = board.pTabBonus[i];
                                if (snakes[k]->tete.x == bonus->point.x && snakes[k]->tete.y == bonus->point.y)
                                {
                                    printf("BONUS : %d\n", bonus->type);
                                    if (bonus->type == closing_walls)
                                    {
                                        closingWallsTimer = SDL_GetTicks();
                                        board.nClosingWalls = 1;
                                    }
                                    else if(bonus->type == change_snake)
                                    {
                                        change_snakes(snakes, nbSnakes, k);
                                    }
                                    else if(bonus->type == more_bonus)
                                    {
                                        nRandBonus -= (int)(7.0/100.0*nRandBonus);
                                    }
                                    else
                                    {
                                        if (bonus->effect == self)
                                        {
                                            take_bonus(snakes[k], board.pTabBonus[i]);
                                        }
                                        else
                                        {
                                            for (j = 0; j < nbSnakes; j++)
                                            {
                                                if (j != k)
                                                    take_bonus(snakes[j], board.pTabBonus[i]);
                                            }
                                        }
                                    }

                                    if (bonus->duration != 0)
                                        bonus->startTimer = SDL_GetTicks();

                                    delete_bonus_board(&board, i);
                                }
                            }
                            
                            for (j = 0; j < snakes[k]->nNbBonus; j++)
                            {
                                Bonus* bonus = snakes[k]->tabBonus[j];
                                if (actualTime - bonus->startTimer >= bonus->duration*1000) 
                                {
                                    delete_bonus_snake(snakes[k], j);
                                }
                            }
                        }
                    }
                }

                if (actualTime - previousTime[nbSnakes] > ADDING_OBJECT_TIMER)
                {
                    previousTime[nbSnakes] = actualTime;

                    int nRandObject = rand()%100;
                    if (nRandObject < P_ADD_WALL)
                        add_wall(&board, snakes, nbSnakes);
                    else if (nRandObject > nRandBonus)
                        add_bonus(&board, snakes, nbSnakes);
                }

                SDL_FillRect(sdlScreen, NULL, SDL_MapRGB(sdlScreen->format, 255, 255, 255)); 
                
                for (i = 0; i < board.nNbTunnels; i++)
                {
                    paint(sdlScreen, board.pTunnels[i]->entree.x, board.pTunnels[i]->entree.y, 5);
                }
                for (i = 0; i < board.nNbBonus; i++)
                {
                    paintBonus(sdlScreen, board.pTabBonus[i]);
                }
                    
                for (j = 0; j < nbSnakes; j++)
                {
                    for (i=0; i < snakes[j]->taille; i++)
                    {
                        paint(sdlScreen, snakes[j]->tab[i].x, snakes[j]->tab[i].y, j+1);
                    }
                }

                for (i=0; i< board.nSize; i++)
                {
                    paint(sdlScreen, board.pPtsMur[i].x, board.pPtsMur[i].y, 0);
                }

                SDL_Flip(sdlScreen);
            }
        }
    }

    SDL_Surface *sdlOption;
    SDL_Rect sdlPosOption;

    sdlPosOption.x = 0;
    sdlPosOption.y = 0;
    if (snakes[0]->vivant)
    {
        sdlOption = SDL_LoadBMP("../images/Victoire.bmp"); 
    }
    else
    {
        sdlOption = SDL_LoadBMP("../images/Defaite.bmp"); 
    }

    SDL_FreeSurface(sdlScreen);
    sdlScreen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_BlitSurface(sdlOption, NULL, sdlScreen, &sdlPosOption);
    SDL_Flip(sdlScreen);
    sleep(4);

    free_snakes(snakes, nbSnakes);
    free_board(board);
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
            color = WALL;
            break;
        case 1:
            color = GREEN;
            break;
        case 2:
            color = RED;
            break;
        case 3:
            color = BLUE;
            break;
        case 4:
            color = YELLOW;
            break;
        case 5:
            color = TUNNEL;
            break;
        default:
            fprintf(stderr, "Trop de snakes pour les couleurs disponibles\n");
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
 * @fn         paintBonus(SDL_Surface* sdlScreen, Bonus* bonus)
 *
 * @brief      Colorie un bonus en forme de losange
 *
 * @param       sdlScreen     L'écran affiché à l'utilisateur
 * @param       bonus         Le bonus à colorier
 *
 * @return     void
 */

void paintBonus(SDL_Surface* sdlScreen, Bonus* bonus)
{
    Uint32 color;
    if (bonus->type == closing_walls || bonus->type == more_bonus)
    {
        color = GLOBAL_BONUS;
    }
    else
    {
        if (bonus->effect == self)
        {
            color = SELF_BONUS;
        }
        else
        {
            color = RED;
        }
    }

    int i, j;
    if (SIZE_CASE%2 == 0)
    {
        for (i = 0; i < SIZE_CASE/2; i++)
        {
            for (j = SIZE_CASE/2-i; j <= SIZE_CASE/2+i; j++)
            {
                setPixel(sdlScreen, bonus->point.x*SIZE_CASE+j, bonus->point.y*SIZE_CASE+i, color);
            }    
        }
        for (j = 0; j < SIZE_CASE; j++)
        {
            setPixel(sdlScreen, bonus->point.x*SIZE_CASE+j, bonus->point.y*SIZE_CASE+SIZE_CASE/2, color);
        }  
        for (i = (SIZE_CASE-2)/2; i > 0; i--)
        {
            for (j = SIZE_CASE/2-i; j <= SIZE_CASE/2+i; j++)
            {
                setPixel(sdlScreen, bonus->point.x*SIZE_CASE+j, bonus->point.y*SIZE_CASE+(SIZE_CASE-i), color);
            }    
        }
    }
    else
    {
        for (i = 0; i < (SIZE_CASE+1)/2; i++)
        {
            for (j = (SIZE_CASE+1)/2-i; j < (SIZE_CASE+1)/2+i; j++)
            {
                setPixel(sdlScreen, bonus->point.x*SIZE_CASE+j, bonus->point.y*SIZE_CASE+i, color);
            }    
        }
        for (i = (SIZE_CASE-1)/2; i >= 0; i--)
        {
            for (j = (SIZE_CASE+1)/2-i; j < (SIZE_CASE+1)/2+i; j++)
            {
                setPixel(sdlScreen, bonus->point.x*SIZE_CASE+j, bonus->point.y*SIZE_CASE+(SIZE_CASE-i), color);
            }    
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
