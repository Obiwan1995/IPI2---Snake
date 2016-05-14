/**
 * @file main.c
 * @author Les Mixtes
 * @date 18/04/2016
 * @brief Fichier principal du jeu
 * @details Contient la fonction principale du snake qui permet de lancer le jeu avec le menu
 */


/*! \mainpage Snake vs Schlanga - Les Mixtes
 *
 * \section intro_sec Introduction
 *
 * Dans le cadre de l'UE Programation Impérative du deuxième semestre, nous devions réaliser un projet dont le thème était Snake vs Schlanga.
 * Nous avons donc créé une variante du jeu Snake disponible sur les anciens téléphones Nokia. 
 * Ainsi, il y a maintenant plusieurs serpents qui s'affrontent sur un plateau de jeu où la mort est sans pitié.
 *
 * <br>
 * \section install_sec Installation
 *
 * \subsection step1 Jeu
 * Pour jouer au jeu, il suffit d'exécuter le fichier play_game.sh et une fenêtre s'ouvre après quelques instants : c'est parti !
 * 
 * \subsection step2 Tests unitaires
 * Pour lancer les tests unitaires, il suffit d'exécuter le fichier run_tests.sh. Vous devez entrer votre mot de passe car le fichier tente d'installer la librairie cmocka que nous avons utilisé pour créer ces tests unitaires. Après quelques instants, vous pourrez voir le résultat des tests unitaires.
 *  
 * <br>
 * \section jeu Principe du jeu
 * 
 * \subsection jeu_base Principes de base
 * Le joueur doit tenter de survivre le plus longtemps possible sur le plateau de jeu. Pour se déplacer, le joueur peut utiliser les flèches directionnelles ou les touches q et d. Attention, la direction est en fonction de la tête du serpent, ce qui signifie que si le joueur appuie sur la flèche droite, le serpent tourne à droite.
 * Les murs sont mortels, la taille du plateau est fixe tout au long de la partie.
 *
 * \subsection jeu_ia Intelligences artificielles
 * Les serpents non contrôlés par le joueur sont régis par deux types d'intelligence artificielle : 
 *      - Une intelligence artificielle aléatoire : celle-ci teste uniquement la prochaine case et évite les collisions. Ses déplacements sont gérés de manière aléatoire.
 *      - Une intelligence artificielle défensive : celle-ci compte le nombre d'obstacles dans un carré de 5x5 à gauche, devant et à droite du snake. Ensuite, le serpent va dans la direction dans laquelle il y a le moins d'obstacles.
 *
 * <br>
 * \section options Options
 * Lors du lancement du jeu, le joueur a accès à un menu d'options accessible en appuyant sur la touche "o". Dans ce menu, le joueur peut modifier de nombreux paramètres du jeu :
 *      - La vitesse des serpents : lent, moyen ou rapide
 *      - Le nombre de serpents sur le plateau : de 1 à 4
 *      - Le type de plateau : normal, 1 contre 1 (2 serpents uniquement) ou grand
 *      - L'existence de murs au milieu du plateau
 */

#include "game.h"
#include "option.h"

/** Largeur du Menu */
#define MENU_WIDTH 800
/** Hauteur du Menu */
#define MENU_HEIGHT 600
/** Nombre de serpents */
#define NB_SNAKES 2

int main(int argc, char *argv[])
{
    SDL_Surface *sdlScreen;
    SDL_Surface *sdlMenu;
    SDL_Rect sdlPosMenu;
    SDL_Event event;
    int nMenu;
    int nBoard = BOARD_BASE;
    int nSpeedInit = SPEED_MEDIUM;
    int nNbSnake = NB_SNAKES;
    int nWalls = BOARD_WITH_WALLS;
    srand(time(NULL));

    if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    sdlScreen = SDL_SetVideoMode(MENU_WIDTH, MENU_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (sdlScreen == NULL) // Si l'ouverture a échoué, on le note et on arrête
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("Snake.. SNAKE !", NULL);
    SDL_ShowCursor(SDL_DISABLE);

    sdlMenu = SDL_LoadBMP("../images/Menu.bmp");
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
                                if (nNbSnake > 2)
                                {
                                    nNbSnake = 2;
                                }
                                board = init_board_1v1();
                                break;
                            case BIG_BOARD:
                                board = init_board_big();
                                break;
                            default:
                                break;
                        }
                        if (nWalls == 1)
                        {
                            add_walls_inside(&board);
                        }
                        SDL_FreeSurface(sdlScreen);
                        sdlScreen = SDL_SetVideoMode(board.nBoardWidth*SIZE_CASE, board.nBoardHeight*SIZE_CASE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

                        play(sdlScreen, board, nNbSnake, nSpeedInit);

                        SDL_FreeSurface(sdlScreen);
                        sdlScreen = SDL_SetVideoMode(MENU_WIDTH, MENU_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                        break;
                    case SDLK_o: // Option
                        option(sdlScreen, &nNbSnake, &nBoard, &nSpeedInit, &nWalls);
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