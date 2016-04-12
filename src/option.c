/**
 * @file option.c
 * @author Les Mixtes
 * @date 01/04/2016
 * @brief Fichier qui gère les options
 * @details Contient la boucle principale du jeu ainsi que les divers affichages
 */

 #include "option.h"
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

void option(SDL_Surface* sdlScreen, int* pNbSnakes, int* pBoard, int* pSpeedInit)
{
    SDL_Surface *sdlOption;
    SDL_Rect sdlPosOption;
    int nInOption = 1;
    int nChoice = 0;
    int nKeyUp = 1;

    sdlPosOption.x = 0;
    sdlPosOption.y = 0;

    SDL_Event event;
    while(nInOption)
    {
        char strImage[100] = "";
        sprintf(strImage, "../images/lac%d", *pBoard);
        printf("../images/lac%d speed : %d menu : %d\n", *pBoard, *pSpeedInit, nChoice);
        sdlOption = SDL_LoadBMP(strImage);
        SDL_BlitSurface(sdlOption, NULL, sdlScreen, &sdlPosOption);
        SDL_Flip(sdlScreen);

        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                nInOption = 0;
                SDL_FreeSurface(sdlOption);
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: // Leave Game
                    case SDLK_q:
                        nInOption = 0;
                        SDL_FreeSurface(sdlOption);
                        break;
                    case SDLK_UP:
                        if (nKeyUp)
                            nChoice = (nChoice+1)%2;
                        nKeyUp = 0;
                        break;
                    case SDLK_RIGHT:
                        if (nKeyUp)
                        {
                            switch(nChoice)
                            {
                                case 0:
                                    switch(*pBoard)
                                    {
                                        case BOARD_BASE:
                                            *pBoard = BOARD_1V1;
                                            break;
                                        case BOARD_1V1:
                                            *pBoard = BIG_BOARD;
                                            break;
                                        case BIG_BOARD:
                                            *pBoard = BOARD_BASE;
                                            break;
                                        default:
                                            break;
                                    }
                                    break;
                                case 1:
                                    switch(*pSpeedInit)
                                    {
                                        case SPEED_EASY:
                                            *pSpeedInit = SPEED_MEDIUM;
                                            break;
                                        case SPEED_MEDIUM:
                                            *pSpeedInit = SPEED_HARD;
                                            break;
                                        case SPEED_HARD:
                                            *pSpeedInit = SPEED_EASY;
                                            break;
                                        default:
                                            break;
                                    }
                                    break;
                                default:
                                    break;
                            }
                        }
                        nKeyUp = 0;
                        break;
                    case SDLK_LEFT:
                        if (nKeyUp)
                        {
                            switch(nChoice)
                            {
                                case 0:
                                    switch(*pBoard)
                                    {
                                        case BOARD_BASE:
                                            *pBoard = BIG_BOARD;
                                            break;
                                        case BOARD_1V1:
                                            *pBoard = BOARD_BASE;
                                            break;
                                        case BIG_BOARD:
                                            *pBoard = BOARD_1V1;
                                            break;
                                        default:
                                            break;
                                    }
                                    break;
                                case 1:
                                    switch(*pSpeedInit)
                                    {
                                        case SPEED_EASY:
                                            *pSpeedInit = SPEED_HARD;
                                            break;
                                        case SPEED_MEDIUM:
                                            *pSpeedInit = SPEED_EASY;
                                            break;
                                        case SPEED_HARD:
                                            *pSpeedInit = SPEED_MEDIUM;
                                            break;
                                        default:
                                            break;
                                    }
                                    break;
                                default:
                                    break;
                            }
                        }
                        nKeyUp = 0;
                        break;
                    case SDLK_DOWN:
                        if (nKeyUp)
                            nChoice = nChoice-1;
                        if (nChoice == -1)
                            nChoice = 1;
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
    }
}

void aide(SDL_Surface* sdlScreen)
{
    SDL_Surface *sdlAide;
    SDL_Rect sdlPosAide;
    sdlAide = SDL_LoadBMP("../images/MenuV2.bmp");
    sdlPosAide.x = 0;
    sdlPosAide.y = 0;
    SDL_BlitSurface(sdlAide, NULL, sdlScreen, &sdlPosAide);
    SDL_Flip(sdlScreen);
    SDL_Event event;
    while(1)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
            case SDL_KEYDOWN:
                SDL_FreeSurface(sdlAide);
                return;
            default:
            break;
        }
    }
}
    