/**
 * @file option.c
 * @author Les Mixtes
 * @date 18/04/2016
 * @brief Fichier qui gère les options
 * @details 
 */

 #include "option.h"
 #include <stdio.h>

/**
 * @fn         option(SDL_Surface* sdlScreen, int* pNbSnakes, int *pBoard, int* pSpeedInit)
 *
 * @brief      Gère les options du jeu
 *
 * @param       sdlScreen       L'écran affiché à l'utilisateur
 * @param       pNbSnakes       Le nombre de serpents
 * @param       pBoard          Le type de plateau utilisé actuellement
 * @param       pSpeedInit      La vitesse initiale définie actuellement
 *
 * @return     void
 */

void option(SDL_Surface* sdlScreen, int* pNbSnakes, int* pBoard, int* pSpeedInit, int* pWalls)
{
    SDL_Surface *sdlOption;
    SDL_Rect sdlPosOption;
    SDL_Rect posChoix;
    SDL_Rect posSpeed;
    SDL_Rect posSnakes;
    SDL_Rect posMap;
    SDL_Rect posWall;
    int nInOption = 1;
    int nChoice = 0;
    int nKeyUp = 1;

    sdlPosOption.x = 0;
    sdlPosOption.y = 0;
    posChoix.h = 2;
    posSpeed.y = 89;
    posSpeed.h = 2;
    posSnakes.y = 185;
    posSnakes.h = 2;
    posMap.y = 278;
    posMap.h = 2;
    posWall.y = 384;
    posWall.h = 2;

    sdlOption = SDL_LoadBMP("../images/Option.bmp");       
    SDL_Event event;
    while(nInOption)
    {
        SDL_BlitSurface(sdlOption, NULL, sdlScreen, &sdlPosOption);
        switch(nChoice)
        {
            case 0:
                posChoix.x = 332;
                posChoix.y = 37;
                posChoix.w = 105;
                break;
            case 1:
                posChoix.x = 323;
                posChoix.y = 137;
                posChoix.w = 128;
                break;
            case 2:
                posChoix.x = 349;
                posChoix.y = 228;
                posChoix.w = 74;
                break;
            case 3:
                posChoix.x = 332;
                posChoix.y = 328;
                posChoix.w = 111;
                break;
            default:
                break;
        }
        switch(*pSpeedInit)
        {
            case SPEED_EASY:
                posSpeed.x = 197;
                posSpeed.w = 75;
                break;
            case SPEED_MEDIUM:
                posSpeed.x = 326;
                posSpeed.w = 114;
                break;
            case SPEED_HARD:
                posSpeed.x = 495;
                posSpeed.w = 68;
                break;
            default:
                break;
        }
        switch(*pNbSnakes)
        {
            case 1:
                posSnakes.x = 298;
                posSnakes.w = 15;
                break;
            case 2:
                posSnakes.x = 353;
                posSnakes.w = 15;
                break;
            case 3:
                posSnakes.x = 408;
                posSnakes.w = 15;
                break;
            case 4:
                posSnakes.x = 465;
                posSnakes.w = 15;
                break;
            default:
                break;
        }
        switch(*pBoard)
        {
            case BOARD_BASE:
                posMap.x = 175;
                posMap.w = 123;
                break;
            case BOARD_1V1:
                posMap.x = 360;
                posMap.w = 44;
                break;
            case BIG_BOARD:
                posMap.x = 485;
                posMap.w = 49;
                break;
            default:
                break;
        }
        switch(*pWalls)
        {
            case BOARD_WITH_WALLS:
                posWall.x = 289;
                posWall.w = 49;
                break;
            case BOARD_WITHOUT_WALLS:
                posWall.x = 435;
                posWall.w = 42;
                break;
            default:
                break;
        }

        SDL_FillRect(sdlScreen, &posChoix, SDL_MapRGB(sdlScreen->format, 206, 206, 0));
        SDL_FillRect(sdlScreen, &posSpeed, SDL_MapRGB(sdlScreen->format, 206, 206, 206));
        SDL_FillRect(sdlScreen, &posSnakes, SDL_MapRGB(sdlScreen->format, 206, 206, 206));
        SDL_FillRect(sdlScreen, &posMap, SDL_MapRGB(sdlScreen->format, 206, 206, 206));
        SDL_FillRect(sdlScreen, &posWall, SDL_MapRGB(sdlScreen->format, 206, 206, 206));

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
                    case SDLK_UP:
                        if (nKeyUp)
                            nChoice = nChoice-1;
                        if (nChoice == -1)
                            nChoice = 3;
                        nKeyUp = 0;
                        break;
                    case SDLK_RIGHT:
                        if (nKeyUp)
                        {
                            switch(nChoice)
                            {
                                case 0:
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
                                case 1:
                                    switch(*pNbSnakes)
                                    {
                                        case 1:
                                            *pNbSnakes = 2;
                                            break;
                                        case 2:
                                            *pNbSnakes = 3;
                                            break;
                                        case 3:
                                            *pNbSnakes = 4;
                                            break;
                                        case 4:
                                            *pNbSnakes = 1;
                                            break;
                                        default:
                                            break;
                                    }
                                    break;
                                case 2:
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
                                case 3:
                                    switch(*pWalls)
                                    {
                                        case BOARD_WITH_WALLS:
                                            *pWalls = BOARD_WITHOUT_WALLS;
                                            break;
                                        case BOARD_WITHOUT_WALLS:
                                            *pWalls = BOARD_WITH_WALLS;
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
                                case 1:
                                    switch(*pNbSnakes)
                                    {
                                        case 1:
                                            *pNbSnakes = 4;
                                            break;
                                        case 2:
                                            *pNbSnakes = 1;
                                            break;
                                        case 3:
                                            *pNbSnakes = 2;
                                            break;
                                        case 4:
                                            *pNbSnakes = 3;
                                            break;
                                        default:
                                            break;
                                    }
                                    break;
                                case 2:
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
                                case 3:
                                    switch(*pWalls)
                                    {
                                        case BOARD_WITH_WALLS:
                                            *pWalls = BOARD_WITHOUT_WALLS;
                                            break;
                                        case BOARD_WITHOUT_WALLS:
                                            *pWalls = BOARD_WITH_WALLS;
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
                            nChoice = (nChoice+1)%4;
                        nKeyUp = 0;
                        break;
                    default:
                        nInOption = 0;
                        SDL_FreeSurface(sdlOption);
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

/**
 * @fn         aide(SDL_Surface* sdlScreen)
 *
 * @brief      Affiche l'aide du jeu
 *
 * @param       sdlScreen       L'écran affiché à l'utilisateur
 *
 * @return     void
 */

void aide(SDL_Surface* sdlScreen)
{
    return;

    SDL_Surface *sdlAide;
    SDL_Rect sdlPosAide;
    sdlAide = SDL_LoadBMP("../images/Menu.bmp");
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
    