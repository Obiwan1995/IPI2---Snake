#include "ia.h"

int deplacement_ia(Serpent* ia, Board board, int nbSnakes, Serpent** snakes) {
	int ndir=0;
	Point right;
	Point left;
	Point forward;
	int collision_right = test_collision(&board, snakes, nbSnakes, right);
	int collision_left = test_collision(&board, snakes, nbSnakes, left);
	int collision_forward = test_collision(&board, snakes, nbSnakes, forward);
	switch(nDir)
            {
                case 1: //top
                	right.x = ia->tete.x+1;
     				right.y = ia->tete.y;
     				left.x = ia->tete.x-1;
     				left.y = ia->tete.y;
     				forward.x = ia−>tete.x;
     				forward.y = ia->tete.y-1;
                    break;
                case 2: //right
                	right.x = ia->tete.x;
     				right.y = ia->tete.y+1;
     				left.x = ia->tete.x;
     				left.y = ia->tete.y-1;
     				forward.x = ia−>tete.x+1;
     				forward.y = ia->tete;
                    break;
                 case 3: //bot
                	right.x = ia->tete.x-1;
     				right.y = ia->tete.y;
     				left.x = ia->tete.x+1;
     				left.y = ia->tete.y;
     				forward.x = ia−>tete.x;
     				forward.y = ia->tete.y+1;
                    break;
                case 4: //left
                	right.x = ia->tete.x;
     				right.y = ia->tete.y-1;
     				left.x = ia->tete.x;
     				left.y = ia->tete.y+1;
     				forward.x = ia−>tete.x-1;
     				forward.y = ia->tete;
                    break;
            }

	if (collision_forward == 1) {
		if (collision_left == 0 && collision_right == 1) {
			Left(ia);
			return 0;
		}
		else if ( collision_right == 0 && collision_left == 1) {
			Right(ia);
			return 0;
		}
		else if (collision_left == 0 && collision_right == 0) {
			srand(time(NULL));
			int rdm = rand()%2;
			if (rdm == 0) {
				Left(ia);
			}
			else {
				Right(ia);
			}
			return 0;
		}
		else {
			return 1;
		}

	if ( collision_left == 1 ) {
		if (collision_right == 0 && collision_forward == 1) {
			Right(ia);
			return 0;
		}
		else if ( collision_right == 1 && collision_forward == 0) {
			Forward(ia);
			return 0;
		}
		else if (collision_right == 0 && collision_forward == 0) {
			srand(time(NULL));
			int rdm = rand()%2;
			if (rdm == 0) {
				Forward(ia);
			}
			else {
				Right(ia);
			}
			return 0;
		}
		else {
			return 1;
		}

	if ( collision_right == 1 ) {
		if (collision_left == 0 && collision_forward == 1) {
			Left(ia);
			return 0;
		}
		else if ( collision_left == 1 && collision_forward == 0) {
			Forward(ia);
			return 0;
		}
		else if (collision_left == 0 && collision_forward == 0) {
			srand(time(NULL));
			int rdm = rand()%2;
			if (rdm == 0) {
				Forward(ia);
			}
			else {
				Left(ia);
			}
			return 0;
		}
		else {
			return 1;
		}
	}

	if (collision_forward == 0 && collision_left == 0 && collision_right == 0) {
		Forward(ia);
	}
}