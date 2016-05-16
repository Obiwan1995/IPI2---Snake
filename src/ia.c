/**
 * @file ia.c
 * @author Les Mixtes
 * @date 14/05/2016
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

/**
 * @fn 			Direction minimum(int choix, Point centre_right, Point centre_forward, Point centre_left, Serpent** tab_serpent, int nb_snakes, Serpent* snake)
 * 
 * @brief     Permet de trouver la direction dans laquelle il y ale moins d'obstacle afin que l'ia évite au maximum les obstacles
 *
 * @param  choix           Permet de faire la différence entre le minimum entre 3 entiers et celui entre deux entiers en différiencant les cas étudiés (suivant les directions à comparer)
 * @param  centre_right    Point nécessaire pour calculer le nombre d'obstacle dans la zone
 * @param  centre_forward  Point nécessaire pour calculer le nombre d'obstacle dans la zone
 * @param  centre_left     Point nécessaire pour calculer le nombre d'obstacle dans la zone
 * @param      tab_serpent     tableau des serpents
 * @param  nb_snakes       nombre de serpents
 * @param b					Board 
 * @param      snake           le serpent à partir duquel on cherche la direction optimale
 *
 * @return     Direction Direction dans laquelle le snake se dirigera , ie direction où il y a le moins d'obstacle
 */

Direction minimum(int choix, Point centre_right, Point centre_forward, Point centre_left, Board* b, Serpent** tab_serpent, int nb_snakes, Serpent* snake) 
{
	Direction res;
	int nb_obs_right = nb_obstacles_around_5(centre_right, b, tab_serpent, nb_snakes, snake);
	int nb_obs_left = nb_obstacles_around_5(centre_left, b, tab_serpent, nb_snakes, snake);
	int nb_obstacles_forward = nb_obstacles_around_5(centre_forward, b, tab_serpent, nb_snakes, snake);

	int rdm = rand()%2;

	switch(choix) 
	{
		case -1:
			if ((nb_obs_right == nb_obs_left) && (nb_obs_right < nb_obstacles_forward))
			{
				if (rdm == 0) 
				{
					res = right;
				}
				else 
				{
					res = left;
				}
			}
			else if ((nb_obs_right == nb_obstacles_forward) && (nb_obs_right < nb_obs_left))
			{
				res = right;
			}
			else if ((nb_obs_left == nb_obstacles_forward) && (nb_obs_left < nb_obstacles_forward))
			{
				res = left;
			}

			else if (nb_obs_right < nb_obs_left) 
			{
				if (nb_obs_right < nb_obstacles_forward) 
				{
					res=right;
				}
				else 
				{
					res = top;
				}
			}
			else if (nb_obs_left < nb_obstacles_forward)
			{
				res = left;
			}
			else 
			{
				res = top;
			}

			break;

		case 0: //on ne compare pas right
		    if (nb_obs_left == nb_obstacles_forward)
			{
				if (rdm == 0) 
				{
					res = left;
				}
				else 
				{
					res = top;
				}
			}
			else if (nb_obs_left < nb_obstacles_forward) 
			{
				res=left;
			}
			else 
			{
				res = top;
			}
			break;

		case 1: //on ne compare pas left
		    if (nb_obs_right == nb_obstacles_forward)
			{
				if (rdm == 0) 
				{
					res = right;
				}
				else 
				{
					res = top;
				}
			}
		   	else if (nb_obstacles_forward < nb_obs_right)
		   	{
		   		res = top;
		   	}
		   	else 
		   	{
		   		res = right;
		   	}
		   	break;

		case 2: //on ne compte pas forward
		    if (nb_obs_right == nb_obs_left)
			{
				if (rdm == 0) 
				{
					res = right;
				}
				else 
				{
					res = left;
				}
			}
			else if (nb_obs_right < nb_obs_left)
			{
				res = right;
			}
			else 
			{
				res = left;
			}
			break;
	}
	return res;
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
	    	centre_right.x = ia->tete.x + 3;
	    	centre_right.y = ia->tete.y;
	    	centre_left.x = ia->tete.x - 3;
	    	centre_left.y = ia->tete.y;
	    	centre_forward.x = ia->tete.x;
	    	centre_forward.y = ia->tete.y - 3;

	    	pt_right.x = ia->tete.x+1;
	    	pt_right.y = ia->tete.y;
			pt_left.x = ia->tete.x-1;
			pt_left.y = ia->tete.y;
			pt_forward.x = ia->tete.x;
			pt_forward.y = ia->tete.y-1;
	        break;

	    case right:
	    	centre_right.x = ia->tete.x;
	    	centre_right.y = ia->tete.y + 3;
	    	centre_left.x = ia->tete.x;
	    	centre_left.y = ia->tete.y - 3;
	    	centre_forward.x = ia->tete.x + 3;
	    	centre_forward.y = ia->tete.y;

	   		pt_right.x = ia->tete.x;
	    	pt_right.y = ia->tete.y+1;
			pt_left.x = ia->tete.x;
			pt_left.y = ia->tete.y-1;
			pt_forward.x = ia->tete.x+1;
			pt_forward.y = ia->tete.y;
	        break;

	     case bot:
	     	centre_right.x = ia->tete.x - 3;
	    	centre_right.y = ia->tete.y;
	    	centre_left.x = ia->tete.x + 3;
	    	centre_left.y = ia->tete.y;
	    	centre_forward.x = ia->tete.x;
	    	centre_forward.y = ia->tete.y + 3;

	     	pt_right.x = ia->tete.x-1;
	    	pt_right.y = ia->tete.y;
			pt_left.x = ia->tete.x+1;
			pt_left.y = ia->tete.y;
			pt_forward.x = ia->tete.x;
			pt_forward.y = ia->tete.y+1;
	        break;

	    case left:
	    	centre_right.x = ia->tete.x;
	    	centre_right.y = ia->tete.y - 3;
	    	centre_left.x = ia->tete.x;
	    	centre_left.y = ia->tete.y + 3;
	    	centre_forward.x = ia->tete.x - 3;
	    	centre_forward.y = ia->tete.y;

	    	pt_right.x = ia->tete.x;
	    	pt_right.y = ia->tete.y-1;
			pt_left.x = ia->tete.x;
			pt_left.y = ia->tete.y+1;
			pt_forward.x = ia->tete.x-1;
			pt_forward.y = ia->tete.y;
	        break;
	}

	

	Direction min = minimum(-1, centre_right, centre_forward, centre_left, &board, snakes, nbSnakes, ia);

	if (min == right) 
	{
		if (test_collision(&board, snakes, nbSnakes, pt_right, ia->id) == 0) 
		{
			Right(ia);
		}
		else if (minimum (0, centre_right, centre_forward, centre_left, &board, snakes, nbSnakes, ia) == left ) 
		{
			if (test_collision(&board, snakes, nbSnakes, pt_left, ia->id) == 0)
			{
				Left(ia);
			}
			else
			{
				Forward(ia);
			}
		}
		else if (test_collision(&board, snakes, nbSnakes, pt_forward, ia->id) == 0)
		{
			Forward(ia);				
		}
		else 
		{
			Left(ia);
		}
	}
	else if (min == left)
	{
		if (test_collision(&board, snakes, nbSnakes, pt_left, ia->id) == 0)
		{
			Left(ia);
		}
		else if (minimum (1, centre_right, centre_forward, centre_left, &board, snakes, nbSnakes, ia) == right) 
		{
			if (test_collision(&board, snakes, nbSnakes, pt_right, ia->id) == 0) 
			{
				Right(ia);
			}
			else
			{
				Forward(ia);
			}
		}
		else if (test_collision(&board, snakes, nbSnakes, pt_forward, ia->id) == 0) 
		{
			Forward(ia);
		}
		else 
		{
			Right(ia);
		}
	}
	else 
	{
		if (test_collision(&board, snakes, nbSnakes, pt_forward, ia->id) == 0)
		{
			Forward(ia);
		}
		else if (minimum(2, centre_right, centre_forward, centre_left, &board, snakes, nbSnakes, ia) == left)
		{
			if (test_collision(&board, snakes, nbSnakes, pt_left, ia->id) == 0)
			{
				Left(ia);
			}
			else
			{
				Right(ia);
			}
		}
		else if (test_collision(&board, snakes, nbSnakes, pt_right, ia->id) == 0 )
		{
			Right(ia);
		}
		else 
		{
			Left(ia);
		}
	}
}