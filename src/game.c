#include "game.h"

void play(SDL_Surface* sdlScreen)
{
    SDL_Event event;
	int nInGame;
	int red;
	int blue;

	nInGame = 1;
	red = 0;
	blue = 0;
    int Time =0;
	while(nInGame)
    {
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
                    case SDLK_q:
                    case SDLK_RIGHT:
                        if (Time > 2)
                        {
                            red = (red + 1)%10;
                        }
                        Time++;
                        break;
                    case SDLK_d:
                    case SDLK_LEFT:
                        if (Time > 2)
                        {
                            red = (red - 1)%10;
                        }
                        Time++;
                        break;
                }
                break;
        }


        if (Time > 2)
        {
            Time =0;
            SDL_FillRect(sdlScreen, NULL, SDL_MapRGB(sdlScreen->format, 255, 255, 255)); 
        	
            int x, y;
            for (x = red; x != 9+red; ++x)
            {
                for (y = blue; y != 9+blue; ++y)
                {
                    paint(sdlScreen, x, y, (x+y)%3);
                }    
            }
    	    SDL_Flip(sdlScreen);
            printf("top, \n");
        }
        Time++;

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