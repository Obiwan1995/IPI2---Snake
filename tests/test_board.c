#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../src/obstacle.h"

#define UNIT_TESTING 1

static void test_init_board1(void ** state)
{
	Board b = init_board1();
	assert_non_null(&b);
	assert_int_equal(b.nNbPos, 4);
	assert_int_equal(b.nNbTunnels, 0);
	free_board(b);
}

static void test_init_board_1v1(void ** state)
{
	Board b = init_board_1v1();
	assert_non_null(&b);
	assert_int_equal(b.nNbPos, 2);
	assert_int_equal(b.nNbTunnels, 0);
	assert_int_equal(b.nBoardWidth, 2*b.nBoardHeight);
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