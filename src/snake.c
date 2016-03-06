#include "snake.h"

/**
 *
 * @fn         void Right(Serpent *snake)
 * 
 * @brief      Change la direction et le serpent lorsque le déplacement choisi par le joueur est la droite.
 * 			   Enumération des 4 cas selon la direction actuelle du serpent
 * 			   On ajoute une case de plus au tableau du serpent qui correspond à la position de la nouvelle tête.
 *
 * @param      snake  serpent à déplacer
 */

void Right(Serpent *snake) {
	Direction dir = snake->dir;
	Point tete = snake->tete;
	int taille = snake->taille;
	Point* tab = snake->tab;
	switch (dir) {
			case 1 :
				tete.x = tete.x + 1;
				dir = 2;
				break;
			case 2 :
				tete.y = tete.y - 1;
				dir = 3;
				break;
			case 3 :
				tete.x = tete.x - 1;
				dir = 4;
				break;
			case 4 :
				tete.y = tete.y + 1;
				dir = 1;
				break;
	}
	snake->tete = tete;
	snake->dir = dir;
	tab = (Point*)realloc(tab, (taille + 1)*sizeof(Point));
	tab[taille] = tete;
	snake->tab = tab;
	snake->taille = taille + 1;
}

/**
 *
 * @fn         void Forward(Serpent *snake)
 * 
 * @brief      Change la direction et le serpent lorsque le déplacement choisi par le joueur est tout droit (il continue dans sa direction actuelle).
 * 			   Enumération des 4 cas selon la direction actuelle du serpent
 * 			   On ajoute une case de plus au tableau du serpent qui correspond à la position de la nouvelle tête.
 *
 * @param      snake  serpent à déplacer
 */

void Forward(Serpent *snake) {
	Point tete = snake->tete;
	int taille = snake->taille;
	Point* tab = snake->tab;
	switch (snake->dir) {
			case 1 :
				tete.y = tete.y + 1;
				break;
			case 2 :
				tete.x = tete.x + 1;
				break;
			case 3 :
				tete.y = tete.y - 1;
				break;
			case 4 :
				tete.x = tete.x - 1;
				break;
	}
	snake->tete = tete;
	tab = (Point*)realloc(tab, (taille + 1)*sizeof(Point));
	tab[taille] = tete;
	snake->tab = tab;
	snake->taille = taille + 1;
}

/**
 *
 * @fn         void Left(Serpent *snake)
 * 
 * @brief      Change la direction et le serpent lorsque le déplacement choisi par le joueur est la gauche.
 * 			   Enumération des 4 cas selon la direction actuelle du serpent
 * 			   On ajoute une case de plus au tableau du serpent qui correspond à la position de la nouvelle tête.
 *
 * @param      snake  serpent à déplacer
 */

void Left(Serpent *snake) {
	Direction dir = snake->dir;
	Point tete = snake->tete;
	int taille = snake->taille;
	Point* tab = snake->tab;
	switch (dir) {
		case 1 :
			tete.x = tete.x - 1;
			dir = 4;
			break;
		case 2 :
			tete.y = tete.y + 1;
			dir = 1;
			break;
		case 3 :
			tete.x = tete.x + 1;
			dir = 2;
			break;
		case 4 :
			tete.y = tete.y - 1;
			dir = 3;
			break;
	}
	snake->tete = tete;
	snake->dir = dir;
	tab = (Point*)realloc(tab, (taille + 1)*sizeof(Point));
	tab[taille] = tete;
	snake->tab = tab;
	snake->taille = taille + 1;
}

/**
 * @fn 		int appartient_tableau(Point point, Point* tableau, int taille)
 * 
 * @brief   teste l'appartenance d'un point (2 coordonnées x et y) à un tableau
 *
 * @param[in]  point    point dont on veut tester l'appartenance au tableau
 * @param      tableau  tableau de point 
 * @param[in]  taille   taille du tableau
 *
 * @return      0 si le point n'appartient pas au tableau
 * 				1 sinon
 */

int appartient_tableau(Point point, Point* tableau, int taille) {
	int i=0;
	int flag=0;
	while (flag==0 && i!=taille) {
		if ( (tableau[i].x == point.x) && (tableau[i].y == point.y) ) {
			flag=1;
		}
		else {
			i=i+1;
		}
	}
	return flag;
}

/**
 * @fn 			void affiche_tableau(Serpent *snake)
 * 
 * @brief      affiche les coordonnées occupées par le serpent
 * 				fonction utilisée pour les tests dans le main
 *
 * @param      snake  serpent dont on veut connaître l'emplacement
 */

void affiche_tableau(Serpent* snake) {
	int taille = snake->taille;
	int i;
	for (i=0; i<taille; i++) {
		printf("(%i,%i) | ",snake->tab[i].x, snake->tab[i].y);
	}
}

/**
 * @fn         Serpent* init_snake(Serpent *snake, int taille_plateau, int id, int vitesse)
 *
 * @brief      initialise le serpent : donne une valeur à chaque champ de la structure
 *
 * @param      snake           serpent à initialiser
 * @param[in]  taille_plateau  taille du plateau de jeu
 * @param[in]  id              id du serpent
 * @param[in]  vitesse         vitesse du serpent
 *
 * @return     serpent avec des valeurs pour chaque champs de sa structure
 */


void init_snake(Serpent *snake, int taille_plateau, int id, int vitesse) {
	//snake = malloc(sizeof (Serpent));
	snake->id = id ;
	snake->vitesse = vitesse;
	snake->taille = 1;
	snake->tete.x = rand()%taille_plateau ;
	snake->tete.y = rand()%taille_plateau;
	snake->tab = (Point*)malloc(snake->taille*sizeof(Point)) ;
	snake->tab[0].x=snake->tete.x;
	snake->tab[0].y=snake->tete.y;
	snake->dir = rand()%4;
}

/**
 * @fn         int test_collision(Mur mur, Serpent** tab_serpent, int taille, int nbr_serpent)
 *
 * @brief      teste la collision d'un serpent avec le mur ou un autre serpent
 *
 * @param[in]  mur          coordonnée des emplacements du mur
 * @param      tab_serpent  tableau de serpent : nécessaire pour la collision avec les autres serpents
 * @param[in]  taille_mur   longueur du tableau mur
 * @param[in]  nbr_serpent  nombre de serpent = longueur du tableau tab_serpent
 *
 * @return     soit 0 s'il n'y a pas de collision
 * 				soit l'id du serpent qui entre en collision avec le mur ou un autre serpent
 */

int test_collision(Mur mur, Serpent** tab_serpent, int taille_mur, int nbr_serpent) {
	int i;
	int j;
	for (i=0; i<nbr_serpent; i++) {
		if (appartient_tableau(tab_serpent[i]->tete, mur, taille_mur) == 0) {
			for (j=0; j<nbr_serpent; j++) {
				if (i!=j) {
					if (appartient_tableau(tab_serpent[i]->tete, tab_serpent[j]->tab, tab_serpent[j]->taille) == 1 ) {
						return tab_serpent[i]->id;
					}	
				}
			}
		}
		else {
			return tab_serpent[i]->id;
		}
	}
	return 0;	
}


/*
int main () {
	Serpent* snake = malloc(sizeof(Serpent));
	init_snake(snake, 100, 1, 10);
	printf("%i", snake->taille);
	affiche_tableau(snake);
	printf("blala\n");
	printf("\n");
	Right(snake);
	printf("la tete est en position(%i,%i)\n",snake->tete.x,snake->tete.y);
	printf("la direction est %i\n",snake->dir);
	affiche_tableau(snake);
	printf("\n");
	Left(snake);
	printf("la tete est en position(%i,%i)\n",snake->tete.x,snake->tete.y);
	printf("la direction est %i\n",snake->dir);
	affiche_tableau(snake);
	return 0;
}
*/