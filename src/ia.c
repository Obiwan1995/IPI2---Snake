/**
 * @file ia.c
 * @author Les Mixtes
 * @date 18/04/2016
 * @brief Fichier permettant la gestion de l'IA aléatoire
 * @details Contient la fonction deplacement_ia qui permet de faire bouger le serpent contrôlé par l'IA aléatoire
 */

#include "ia.h"

/**
* @fn         void move_random_ia(Serpent* ia, Board board, int nbSnakes, Serpent** snakes)
*
* @brief      Fait bouger le serpent contrôlé par l'IA aléatoire
*
* @param      ia 		Le serpent contrôlé par l'IA aléatoire
* @param 	  board 	Le plateau de jeu
* @param 	  nbSnakes	Le nombre de serpents dans la partie
* @param 	  snakes 	Le tableau contenant tous les serpents de la partie
*
* @details	  Ce serpent va tout droit dans 90% des cas s'il le peut. Il va de temps à temps à droite ou à gauche de façon aléatoire.
* @details	  S'il ne peut pas aller tout droit, il choisit aléatoirement d'aller à droite ou gauche s'il ne meurt pas en allant dans cette direction.
*
* @return     void
*/

void move_random_ia(Serpent* ia, Board board, int nbSnakes, Serpent** snakes) 
{
	Point pt_left;
	Point pt_forward;
	Point pt_right;
	switch(ia->dir)
	{	
	    case top:
	    	pt_right.x = ia->tete.x+1;
	    	pt_right.y = ia->tete.y;
			pt_left.x = ia->tete.x-1;
			pt_left.y = ia->tete.y;
			pt_forward.x = ia->tete.x;
			pt_forward.y = ia->tete.y-1;
	        break;
	    case right:
	   		pt_right.x = ia->tete.x;
	    	pt_right.y = ia->tete.y+1;
			pt_left.x = ia->tete.x;
			pt_left.y = ia->tete.y-1;
			pt_forward.x = ia->tete.x+1;
			pt_forward.y = ia->tete.y;
	        break;
	     case bot:
	     	pt_right.x = ia->tete.x-1;
	    	pt_right.y = ia->tete.y;
			pt_left.x = ia->tete.x+1;
			pt_left.y = ia->tete.y;
			pt_forward.x = ia->tete.x;
			pt_forward.y = ia->tete.y+1;
	        break;
	    case left:
	    	pt_right.x = ia->tete.x;
	    	pt_right.y = ia->tete.y-1;
			pt_left.x = ia->tete.x;
			pt_left.y = ia->tete.y+1;
			pt_forward.x = ia->tete.x-1;
			pt_forward.y = ia->tete.y;
	        break;
	}
	int collision_forward = test_collision(&board, snakes, nbSnakes, pt_forward, ia->id);

	if (collision_forward == ia->id) 
	{
		int rdm = rand()%2;
		if (rdm == 0)
		{
			int collision_left = test_collision(&board, snakes, nbSnakes, pt_left, ia->id);
			if (collision_left == ia->id) 
			{
				Right(ia);
			}
			else 
			{
				Left(ia);
			}
		}
		else
		{
			int collision_right = test_collision(&board, snakes, nbSnakes, pt_right, ia->id);
			if (collision_right == ia->id) 
			{
				Left(ia);
			}
			else 
			{
				Right(ia);
			}
		}
	}
	else
	{
		int rdm = rand()%100;
		if (rdm < 90)
		{
			Forward(ia);
		}
		else if(rdm >= 90 && rdm < 95)
		{
			int collision_left = test_collision(&board, snakes, nbSnakes, pt_left, ia->id);
			if (collision_left == ia->id && test_collision(&board, snakes, nbSnakes, pt_right, ia->id) == 0) 
			{
				Right(ia);
			}
			else if (collision_left == 0)
			{
				Left(ia);
			}
			else
			{
				Forward(ia);
			}
		}
		else
		{
			int collision_right = test_collision(&board, snakes, nbSnakes, pt_right, ia->id);
			if (collision_right == ia->id && test_collision(&board, snakes, nbSnakes, pt_left, ia->id) == 0) 
			{
				Left(ia);
			}
			else if (collision_right == 0)
			{
				Right(ia);
			}
			else
			{
				Forward(ia);
			}
		}
	}
}

int minimum(int a, int b, int c) 
{
	if (a < b) 
	{
		if (a < c) 
		{
			return a;
		}
		else 
		{
			return c;
		}
	}
	else if (b < c)
	{
		return b;
	}
	else 
	{
		return c;
	}
}




/**
* @fn         void move_def_ia(Serpent* ia, Board board, int nbSnakes, Serpent** snakes)
*
* @brief      Fait bouger le serpent contrôlé par l'IA défensive
*
* @param      ia 		Le serpent contrôlé par l'IA défensive
* @param 	  board 	Le plateau de jeu
* @param 	  nbSnakes	Le nombre de serpents dans la partie
* @param 	  snakes 	Le tableau contenant tous les serpents de la partie	  
*
* @return     void
*/

void move_def_ia(Serpent* ia, Board board, int nbSnakes, Serpent** snakes)
{
	Point centre_right;
	Point centre_left;
	Point centre_forward;

	Point pt_left;
	Point pt_forward;
	Point pt_right;

	switch(ia->dir)
	{	
	    case top:
	    	centre_right.x = ia->tete.x + 2;
	    	centre_right.y = ia->tete.y;
	    	centre_left.x = ia->tete.x - 2;
	    	centre_left.y = ia->tete.y;
	    	centre_forward.x = ia->tete.x;
	    	centre_forward.y = ia->tete.y - 2;

	    	pt_right.x = ia->tete.x+1;
	    	pt_right.y = ia->tete.y;
			pt_left.x = ia->tete.x-1;
			pt_left.y = ia->tete.y;
			pt_forward.x = ia->tete.x;
			pt_forward.y = ia->tete.y-1;
	        break;

	    case right:
	    	centre_right.x = ia->tete.x;
	    	centre_right.y = ia->tete.y + 2;
	    	centre_left.x = ia->tete.x;
	    	centre_left.y = ia->tete.y - 2;
	    	centre_forward.x = ia->tete.x + 2;
	    	centre_forward.y = ia->tete.y;

	   		pt_right.x = ia->tete.x;
	    	pt_right.y = ia->tete.y+1;
			pt_left.x = ia->tete.x;
			pt_left.y = ia->tete.y-1;
			pt_forward.x = ia->tete.x+1;
			pt_forward.y = ia->tete.y;
	        break;

	     case bot:
	     	centre_right.x = ia->tete.x - 2;
	    	centre_right.y = ia->tete.y;
	    	centre_left.x = ia->tete.x + 2;
	    	centre_left.y = ia->tete.y;
	    	centre_forward.x = ia->tete.x;
	    	centre_forward.y = ia->tete.y + 2;

	     	pt_right.x = ia->tete.x-1;
	    	pt_right.y = ia->tete.y;
			pt_left.x = ia->tete.x+1;
			pt_left.y = ia->tete.y;
			pt_forward.x = ia->tete.x;
			pt_forward.y = ia->tete.y+1;
	        break;

	    case left:
	    	centre_right.x = ia->tete.x;
	    	centre_right.y = ia->tete.y - 2;
	    	centre_left.x = ia->tete.x;
	    	centre_left.y = ia->tete.y + 2;
	    	centre_forward.x = ia->tete.x - 2;
	    	centre_forward.y = ia->tete.y;

	    	pt_right.x = ia->tete.x;
	    	pt_right.y = ia->tete.y-1;
			pt_left.x = ia->tete.x;
			pt_left.y = ia->tete.y+1;
			pt_forward.x = ia->tete.x-1;
			pt_forward.y = ia->tete.y;
	        break;
	}

	int nb_obs_right = nb_obstacles_around(centre_right, &board, snakes, nbSnakes, ia);
	int nb_obs_left = nb_obstacles_around(centre_left, &board, snakes, nbSnakes, ia);
	int nb_obstacles_forward = nb_obstacles_around(centre_forward, &board, snakes, nbSnakes, ia);

	int min = minimum(nb_obs_right, nb_obs_left, nb_obstacles_forward);

	int collision_right = test_collision(&board, snakes, nbSnakes, pt_right, ia->id);
	int collision_left = test_collision(&board, snakes, nbSnakes, pt_left, ia->id);
	int collision_forward = test_collision(&board, snakes, nbSnakes, pt_forward, ia->id);

	if (min == nb_obs_right) 
	{
		if (collision_right == 0) 
		{
			Right(ia);
		}
		else if (minimum (10000, nb_obs_left, nb_obstacles_forward) == nb_obs_left ) {
			if (collision_left == 0)
			{
				Left(ia);
			}
			else 
			{
				Forward(ia);
			}
		}	
	}
	else if (min == nb_obs_left)
	{
		if (collision_left == 0)
		{
			Left(ia);
		}
		else if (minimum (nb_obs_right, 10000, nb_obstacles_forward) == nb_obs_right) 
		{
			if (collision_right == 0) 
			{
				Right(ia);
			}
			else 
			{
				Forward(ia);
			}
		}
	}
	else 
	{
		if (collision_forward == 0)
		{
			Forward(ia);
		}
		else if (minimum(nb_obs_right, nb_obs_left, 100000) == nb_obs_left)
		{
			if (collision_left == 0)
			{
				Left(ia);
			}
			else 
			{
				Right(ia);
			}
		}
	}
}