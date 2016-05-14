#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../src/bonus.h"

#define UNIT_TESTING 1

static void test_init_board1(void ** state)
{
	Board b = init_board1();
	assert_non_null(&b);
	assert_int_equal(b.nNbPos, 4);
	assert_int_equal(b.nNbTunnels, 0);
	assert_int_equal(b.nNbBonus, 0);
	assert_int_equal(b.nClosingWalls, 0);
	free_board(b);
}

static void test_init_board_1v1(void ** state)
{
	Board b = init_board_1v1();
	assert_non_null(&b);
	assert_int_equal(b.nNbPos, 2);
	assert_int_equal(b.nNbTunnels, 0);
	assert_int_equal(b.nNbBonus, 0);
	assert_int_equal(b.nClosingWalls, 0);
	assert_int_equal(b.nBoardWidth, 2*b.nBoardHeight);
	free_board(b);
}

static void test_init_board_big(void ** state)
{
	Board b = init_board_big();
	assert_non_null(&b);
	assert_int_equal(b.nNbPos, 4);
	assert_int_equal(b.nNbTunnels, 0);
	assert_int_equal(b.nNbBonus, 0);
	assert_int_equal(b.nClosingWalls, 0);
	free_board(b);
}

static void test_init_walls(void ** state)
{
	Board b = init_board1();
	Point p;
	int i, j;
	for (i = 0; i < b.nBoardWidth; i++)
	{
		for (j = 0; j < b.nBoardHeight; j++)
		{
			if (i == 0 || j == 0 || i == b.nBoardWidth-1 || j == b.nBoardHeight-1)
			{
				p.x = i;
				p.y = j;
				assert_int_equal(belongs_to_tab(p, b.pPtsMur, b.nSize), 1);
			}
		}
	}
	free_board(b);
}

static void test_is_cell_free(void ** state)
{
	Board b = init_board1();
	int nb_snakes = 1;
	Serpent** snakes = malloc(nb_snakes * sizeof(Serpent*));
	Serpent* snake = malloc(sizeof(Serpent));
    Point p;
    p.x = 3;
    p.y = 5;
    init_snake(snake, 1, 50, top, p);
    snakes[0] = snake;
	p.x = 10;
	p.y = 10;
	assert_int_equal(is_cell_free(p, &b, snakes, nb_snakes), 1);
	p.x = 0;
	p.y = 0;
	assert_int_equal(is_cell_free(p, &b, snakes, nb_snakes), 0);
	p.x = snake->tete.x;
	p.y = snake->tete.y;
	assert_int_equal(is_cell_free(p, &b, snakes, nb_snakes), 0);
	free_board(b);
	free_snakes(snakes, nb_snakes);
}

static void test_add_wall(void ** state)
{
	Board b = init_board1();
	int nWalls = b.nSize;
	int nb_snakes = 0;
	Serpent** snakes = malloc(nb_snakes * sizeof(Serpent*));
	add_wall(&b, snakes, nb_snakes);
	assert_int_equal(b.nSize, nWalls+1);
	free_board(b);
	free_snakes(snakes, nb_snakes);
}

static void test_add_tunnels(void ** state)
{
	Board b = init_board1();
	int nb_snakes = 0;
	Serpent** snakes = malloc(nb_snakes * sizeof(Serpent*));
	add_tunnels(&b, snakes, nb_snakes);
	assert_non_null(b.pTunnels);
	int i;
	for (i = 0; i < b.nNbTunnels; i++)
	{
		assert_non_null(b.pTunnels[i]);
	}
	assert_int_equal(b.nNbTunnels, i);
	free_board(b);
	free_snakes(snakes, nb_snakes);
}

static void test_handle_tunnels(void ** state)
{
	Board b = init_board1();
	int nb_snakes = 1;
	Serpent** snakes = malloc(nb_snakes * sizeof(Serpent*));
	Serpent* snake = malloc(sizeof(Serpent));
	Point p;
    p.x = 3;
    p.y = 5;
    init_snake(snake, 1, 50, top, p);
    snakes[0] = snake;
    add_tunnels(&b, snakes, nb_snakes);
    snake->tete.x = b.pTunnels[0]->entree.x;
    snake->tete.y = b.pTunnels[0]->entree.y;
    b.pTunnels[0]->nNbSorties = 1;
    handle_tunnels(snake, &b);
    assert_int_equal(snake->tete.x, b.pTunnels[0]->sorties[0].x);
    assert_int_equal(snake->tete.y, b.pTunnels[0]->sorties[0].y);
    free_board(b);
    free_snakes(snakes, nb_snakes);
}

static void test_add_bonus(void ** state)
{
	Board b = init_board1();
	int nb_snakes = 0;
	Serpent** snakes = malloc(nb_snakes * sizeof(Serpent*));
	add_bonus(&b, snakes, nb_snakes);
	assert_non_null(b.pTabBonus);
	assert_int_equal(b.nNbBonus, 1);
	free_board(b);
	free_snakes(snakes, nb_snakes);
}