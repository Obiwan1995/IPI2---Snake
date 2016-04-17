/**
 * @file ia.c
 * @author Les Mixtes
 * @date 17/04/2016
 * @brief Fichier permettant la gestion de l'IA aléatoire
 * @details Contient la fonction deplacement_ia qui permet de faire bouger le serpent contrôlé par l'IA aléatoire
 */

#include "ia.h"

/**
* @fn         int deplacement_ia(Serpent* ia, Board board, int nbSnakes, Serpent** snakes)
*
* @brief      Fait bouger le serpent contrôlé par l'IA aléatoire
*
* @param      ia 		Le serpent contrôlé par l'IA aléatoire
* @param 	  board 	Le plateau de jeu
* @param 	  nbSnakes	Le nombre de serpents dans la partie
* @param 	  snakes 	Le tableau contenant tous les serpents de la partie
*
* @return     1 ?
*/

int deplacement_ia(Serpent* ia, Board board, int nbSnakes, Serpent** snakes) 
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

	if (collision_forward == 1) 
	{
		int rdm = rand()%2;
		if (rdm == 0)
		{
			int collision_left = test_collision(&board, snakes, nbSnakes, pt_left, ia->id);
			if (collision_left == 1) 
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
			if (collision_right == 1) 
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
			if (collision_left == 1 && test_collision(&board, snakes, nbSnakes, pt_right, ia->id) == 0) 
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
			if (collision_right == 1 && test_collision(&board, snakes, nbSnakes, pt_left, ia->id) == 0) 
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

	return 0;
}