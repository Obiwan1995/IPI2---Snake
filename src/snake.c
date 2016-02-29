#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int x;
	int y;
} Point;

typedef enum Direction {top=1, right=2, bot=3, left=4} Direction;

typedef struct {
	int id;
	int vitesse;
	int taille;
	Point* tab;
	Point tete;
	Direction dir;
} Serpent;

typedef Point* Mur;

Serpent Right(Serpent snake) {
	Direction dir = snake.dir;
	Point tete = snake.tete;
	int taille = snake.taille;
	Point* tab = snake.tab;
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
	snake.tete = tete;
	snake.dir = dir;
	tab = (Point*)realloc(tab, (taille + 1)*sizeof(Point));
	tab[taille] = tete;
	snake.tab = tab;
	snake.taille = taille + 1;
	return snake;
}

Serpent Forward(Serpent snake) {
	Point tete = snake.tete;
	int taille = snake.taille;
	Point* tab = snake.tab;
	switch (snake.dir) {
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
	snake.tete = tete;
	tab = (Point*)realloc(tab, (taille + 1)*sizeof(Point));
	tab[taille] = tete;
	snake.tab = tab;
	snake.taille = taille + 1;
	return snake;
}

Serpent Left(Serpent snake) {
	Direction dir = snake.dir;
	Point tete = snake.tete;
	int taille = snake.taille;
	Point* tab = snake.tab;
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
	snake.tete = tete;
	snake.dir = dir;
	tab = (Point*)realloc(tab, (taille + 1)*sizeof(Point));
	tab[taille] = tete;
	snake.tab = tab;
	snake.taille = taille + 1;
	return snake;
}

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

void affiche_tableau(Serpent snake) {
	int taille = snake.taille;
	int i;
	for (i=0; i<taille; i++) {
		printf("(%i,%i) | ",snake.tab[i].x, snake.tab[i].y);
	}
}

/*int test_collision(Mur mur, Serpent snake, int taille) {
	Point pos = deplacement(snake);
	if ( appartient_tableau(pos, mur, taille) == 1 ) {
		return 0;
	}
	else {
		return 1;
	}
}
*/
int main () {
	Serpent snake;

	int taille = 4;
	snake.taille=4;
	affiche_tableau(snake);
	printf("\n");
	Point* tab = (Point*)malloc(taille*sizeof(Point));

	snake.tete.x=3;
	snake.tete.y=2;

	snake.tab = tab;
	snake.tab[taille-1].x=snake.tete.x;
	snake.tab[taille-1].y=snake.tete.y;
	

	snake.dir = 1;

	affiche_tableau(snake);
	printf("\n");
	snake=Forward(snake);
	printf("la tete est en position(%i,%i)\n",snake.tete.x,snake.tete.y);
	printf("la direction est %i\n",snake.dir);
	affiche_tableau(snake);
	printf("\n");
	snake=Left(snake);
	printf("la tete est en position(%i,%i)\n",snake.tete.x,snake.tete.y);
	printf("la direction est %i\n",snake.dir);
	affiche_tableau(snake);

	return 0;
}

