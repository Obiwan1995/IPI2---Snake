#include "../lib/SDL/include/SDL/SDL.h"

#include "game.h"

int main(int argc, char *argv[])
{
    SDL_Surface *sdlScreen;
    SDL_Surface *sdlMenu;
    SDL_Rect sdlPosMenu;
    SDL_Event event;
    int nMenu;

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
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                nMenu = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: // Leave Game
                    case SDLK_q: // Start Game
                        nMenu = 0;
                        break;
                    case SDLK_p: // Start Game
                        play(sdlScreen, 2);
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }


        SDL_FillRect(sdlScreen, NULL, SDL_MapRGB(sdlScreen->format, 20, 20, 20));
        SDL_BlitSurface(sdlMenu, NULL, sdlScreen, &sdlPosMenu);
        SDL_Flip(sdlScreen);
    }


    SDL_FreeSurface(sdlMenu);
    SDL_Quit();

    return EXIT_SUCCESS;
}