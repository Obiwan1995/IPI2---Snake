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

	if (collision_forward) 
	{
		int rdm = rand()%2;
		if (rdm == 0)
		{
			int collision_left = test_collision(&board, snakes, nbSnakes, pt_left, ia->id);
			if (collision_left) 
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
			if (collision_right) 
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
			if (collision_left && test_collision(&board, snakes, nbSnakes, pt_right, ia->id) == 0) 
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
			if (collision_right && test_collision(&board, snakes, nbSnakes, pt_left, ia->id) == 0) 
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
				if (rdm == 0) 
				{
					res = right;
				}
				else 
				{
					res = top;
				}
			}
			else if ((nb_obs_left == nb_obstacles_forward) && (nb_obs_left < nb_obstacles_forward))
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
			else if (test_collision(&board, snakes, nbSnakes, pt_forward, ia->id) == 0)
			{
				Forward(ia);
			}
			else
			{
				Right(ia);
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
			else if (test_collision(&board, snakes, nbSnakes, pt_forward, ia->id) == 0) 
			{
				Forward(ia);
			}
			else
			{
				Left(ia);
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
			else if (test_collision(&board, snakes, nbSnakes, pt_right, ia->id) == 0 )
			{
				Right(ia);
			}
			else
			{
				Forward(ia);
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


Direction minimum_2(int choix, Serpent** snakes, int nb_snakes, Serpent* ia, Point pt_right, Point pt_left, Point pt_forward) 
{

	Direction res;
	int dist_forward = sqrt(((pt_forward.x-snakes[1]->tete.x)^2)+((pt_forward.y-snakes[1]->tete.y)^2));
	int dist_right = sqrt(((pt_right.x-snakes[1]->tete.x)^2)+((pt_right.y-snakes[1]->tete.y)^2));
	int dist_left = sqrt(((pt_left.x-snakes[1]->tete.x)^2)+((pt_left.y-snakes[1]->tete.y)^2));

	int rdm = rand()%2;

	switch(choix) 
	{
		case -1:
			if (dist_right == dist_left)
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
			else if (dist_right == dist_forward)
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
			else if (dist_left == dist_forward)
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

			else if (dist_right < dist_left) 
			{
				if (dist_right < dist_forward) 
				{
					res=right;
				}
				else 
				{
					res = top;
				}
			}
			else if (dist_left < dist_forward)
			{
				res = left;
			}
			else 
			{
				res = top;
			}

			break;

		case 0: //on ne compare pas right
		    if (dist_left == dist_forward)
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
			else if (dist_left < dist_forward) 
			{
				res=left;
			}
			else 
			{
				res = top;
			}
			break;

		case 1: //on ne compare pas left
		    if (dist_right == dist_forward)
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
		   	else if (dist_forward < dist_right)
		   	{
		   		res = top;
		   	}
		   	else 
		   	{
		   		res = right;
		   	}
		   	break;

		case 2: //on ne compte pas forward
		    if (dist_right == dist_left)
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
			else if (dist_right < dist_left)
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


void move_off_ia(Serpent* ia, Board board, int nbSnakes, Serpent** snakes)
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

	Direction min = minimum_2(0, snakes, nbSnakes, ia, pt_right, pt_left, pt_forward);

	if (min == right) 
	{
		if (test_collision(&board, snakes, nbSnakes, pt_right, ia->id) == 0) 
		{
			Right(ia);
		}

		else if (minimum_2(0, snakes, nbSnakes, ia, pt_right, pt_left, pt_forward) == left ) 
		{
			if (test_collision(&board, snakes, nbSnakes, pt_left, ia->id) == 0)
			{
				Left(ia);
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
		else if (minimum_2 (1, snakes, nbSnakes, ia, pt_right, pt_left, pt_forward) == right) 
		{
			if (test_collision(&board, snakes, nbSnakes, pt_right, ia->id) == 0) 
			{
				Right(ia);
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
		else if (minimum_2(2, snakes, nbSnakes, ia, pt_right, pt_left, pt_forward) == left)
		{
			if (test_collision(&board, snakes, nbSnakes, pt_left, ia->id) == 0)
			{
				Left(ia);
			}
			else if (test_collision(&board, snakes, nbSnakes, pt_right, ia->id) == 0 )
			{
				Right(ia);
			}
			else
			{
				Forward(ia);
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

