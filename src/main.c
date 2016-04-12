#include "game.h"
#include "option.h"

/** Largeur du Menu */
#define BOARD_WIDTH 40
/** Hauteur du Menu */
#define BOARD_HEIGHT 40
/** Nombre de serpents */
#define NB_SNAKE 1

int main(int argc, char *argv[])
{
    SDL_Surface *sdlScreen;
    SDL_Surface *sdlMenu;
    SDL_Rect sdlPosMenu;
    SDL_Event event;
    int nMenu;
    int nBoard = BOARD_BASE;
    int nSpeedInit = SPEED_MEDIUM;
    int nNbSnake = NB_SNAKE;

    if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    sdlScreen = SDL_SetVideoMode(BOARD_WIDTH*SIZE_CASE, BOARD_HEIGHT*SIZE_CASE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (sdlScreen == NULL) // Si l'ouverture a échoué, on le note et on arrête
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("Snake.. SNAKE !", NULL);
    SDL_ShowCursor(SDL_DISABLE);

    sdlMenu = SDL_LoadBMP("../images/MenuV1.bmp");
    sdlPosMenu.x = 0;
    sdlPosMenu.y = 0;

    nMenu = 1;
    while(nMenu)
    {
        Board board;
        
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                nMenu = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {   
                    case SDLK_p: // Start Game
                    case SDLK_j:
                        switch(nBoard)
                        {
                            case BOARD_BASE:
                                board = init_board1();
                                break;
                            case BOARD_1V1:
                                board = init_board1();
                                break;
                            case BOARD_WALL:
                                board = init_board1();
                                break;
                            default:
                                break;
                        }
                        SDL_FreeSurface(sdlScreen);
                        sdlScreen = SDL_SetVideoMode(board.nBoardWidth*SIZE_CASE, board.nBoardHeight*SIZE_CASE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

                        play(sdlScreen, board, nNbSnake, nSpeedInit);

                        SDL_FreeSurface(sdlScreen);
                        sdlScreen = SDL_SetVideoMode(BOARD_WIDTH*SIZE_CASE, BOARD_HEIGHT*SIZE_CASE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                        break;
                    case SDLK_o: // Option
                        printf("%d sp\n", nSpeedInit);
                        option(sdlScreen, &nNbSnake, &nBoard, &nSpeedInit);
                        printf("%d dp\n", nSpeedInit);
                        break;
                    case SDLK_a: // Help
                    case SDLK_h:
                        aide(sdlScreen);
                        break;
                    case SDLK_ESCAPE: // Leave Game
                    case SDLK_q:
                        nMenu = 0;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }


        //SDL_FillRect(sdlScreen, NULL, SDL_MapRGB(sdlScreen->format, 20, 20, 20));
        SDL_BlitSurface(sdlMenu, NULL, sdlScreen, &sdlPosMenu);
        SDL_Flip(sdlScreen);
    }


    SDL_FreeSurface(sdlMenu);
    SDL_Quit();

    return EXIT_SUCCESS;
}