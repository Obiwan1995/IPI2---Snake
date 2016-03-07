#include "game.h"

void play(SDL_Surface* sdlScreen)
{
    SDL_Event event;
    Serpent* snake = malloc(sizeof(Serpent));
    init_snake(snake, 50, 1, 10);

    int nDir = 0;
    int nKeyUp = 0;
    int nInGame = 1;
    int actualTime = 0;
    int previousTime = 0;

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
                    default:
                        break;
                }
                break;
            case SDL_KEYUP:
                        nKeyUp = 1;
            default:
                break;
        }

        if (actualTime - previousTime > SPEED) {
            switch(nDir)
            {
                case 0:
                    Forward(snake);
                    break;
                case 1:
                    Right(snake);
                    break;
                case 2:
                    Left(snake);
                    break;
            }

            SDL_FillRect(sdlScreen, NULL, SDL_MapRGB(sdlScreen->format, 255, 255, 255)); 

            int i;
            for (i=0; i< snake->taille; i++)
            {
                paint(sdlScreen, snake->tab[i].x, snake->tab[i].y, 1);
            }

            SDL_Flip(sdlScreen);

            nDir = 0;
            previousTime = actualTime;
        }

    }

}

void paint(SDL_Surface* sdlScreen, int x, int y, int nId)
{
    Uint32 color;

    switch(nId)
    {
        case 0:
            color = RED;
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
    for (i = 0; i != SIZE_PIXEL; ++i)
    {
        for (j = 0; j != SIZE_PIXEL; ++j)
        {
            if (!((i == 0 || i == SIZE_PIXEL || i == 1 || i == SIZE_PIXEL-1) && (j == 0 || j == SIZE_PIXEL || j == 1 || j == SIZE_PIXEL-1)))
                setPixel(sdlScreen, x*SIZE_PIXEL+i, y*SIZE_PIXEL+j, color);
        }    
    }
}

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
