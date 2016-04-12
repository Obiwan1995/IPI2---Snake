#include "ia.h"

int deplacement_ia(Serpent* ia, Board board, int nbSnakes, Serpent** snakes) 
{
	Point left;
	Point forward;
	Point right;
	switch(ia->dir)
	{	
	    case 1: //top
	    	right.x = ia->tete.x+1;
	    	right.y = ia->tete.y;
			left.x = ia->tete.x-1;
			left.y = ia->tete.y;
			forward.x = ia->tete.x;
			forward.y = ia->tete.y-1;
	        break;
	    case 2: //right
	   		right.x = ia->tete.x;
	    	right.y = ia->tete.y+1;
			left.x = ia->tete.x;
			left.y = ia->tete.y-1;
			forward.x = ia->tete.x+1;
			forward.y = ia->tete.y;
	        break;
	     case 3: //bot
	     	right.x = ia->tete.x-1;
	    	right.y = ia->tete.y;
			left.x = ia->tete.x+1;
			left.y = ia->tete.y;
			forward.x = ia->tete.x;
			forward.y = ia->tete.y+1;
	        break;
	    case 4: //left
	    	right.x = ia->tete.x;
	    	right.y = ia->tete.y-1;
			left.x = ia->tete.x;
			left.y = ia->tete.y+1;
			forward.x = ia->tete.x-1;
			forward.y = ia->tete.y;
	        break;
	}
	int collision_forward = test_collision(&board, snakes, nbSnakes, forward, ia->id);

	if (collision_forward == 1) 
	{
		int rdm = rand()%2;
		if (rdm == 0)
		{
			int collision_left = test_collision(&board, snakes, nbSnakes, left, ia->id);
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
			int collision_right = test_collision(&board, snakes, nbSnakes, right, ia->id);
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
			int collision_left = test_collision(&board, snakes, nbSnakes, left, ia->id);
			if (collision_left == 1 && test_collision(&board, snakes, nbSnakes, right, ia->id) == 0) 
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
			int collision_right = test_collision(&board, snakes, nbSnakes, right, ia->id);
			if (collision_right == 1 && test_collision(&board, snakes, nbSnakes, left, ia->id) == 0) 
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