#define UNIT_TESTING 1
#define ID 1
#define SPEED 10
#define DIR 1
#define X 10
#define Y 10

#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../src/snake.h"

static int setup(void **state) 
{
    Serpent* snake = malloc(sizeof(Serpent));
    Point p;
    p.x = X;
    p.y = Y;
    init_snake(snake, ID, SPEED, DIR, p);
    assert_non_null(snake);
    *state = snake;
    return 0;
}

static int teardown(void **state) 
{
    free(*state);
    return 0;
}

static void test_init_snake(void **state) 
{
    Serpent* snake = *state;
    assert_int_equal(snake->id, ID);
    assert_int_equal(snake->vitesse, SPEED);
    assert_int_equal(snake->dir, DIR);
    assert_int_equal(snake->taille, 1);
    assert_int_equal(snake->tete.x, X);
    assert_int_equal(snake->tete.y, Y);
    assert_non_null(snake->tab);
    assert_int_equal(snake->tab[0].x, X);
    assert_int_equal(snake->tab[0].y, Y);
}

static void test_forward_top_snake(void ** state)
{
    Serpent* snake = *state;
    Forward(snake);
    assert_non_null(snake);
    assert_int_equal(snake->tete.x, X);
    assert_int_equal(snake->tete.y, Y-1);
}

static void test_forward_right_snake(void ** state)
{
    Serpent* snake = *state;
    snake->dir = 2;
    Forward(snake);
    assert_non_null(snake);
    assert_int_equal(snake->tete.x, X+1);
    assert_int_equal(snake->tete.y, Y);
}

static void test_forward_bot_snake(void ** state)
{
    Serpent* snake = *state;
    snake->dir = 3;
    Forward(snake);
    assert_non_null(snake);
    assert_int_equal(snake->tete.x, X);
    assert_int_equal(snake->tete.y, Y+1);
}

static void test_forward_left_snake(void ** state)
{
    Serpent* snake = *state;
    snake->dir = 4;
    Forward(snake);
    assert_non_null(snake);
    assert_int_equal(snake->tete.x, X-1);
    assert_int_equal(snake->tete.y, Y);
}

static void test_turn_left_top_snake(void ** state)
{
    Serpent* snake = *state;
    Left(snake);
    assert_non_null(snake);
    assert_int_equal(snake->tete.x, X-1);
    assert_int_equal(snake->tete.y, Y);
    assert_int_equal(snake->dir, 4);
}

int main(void) 
{
    const struct CMUnitTest tests[] = 
    {
        cmocka_unit_test_setup_teardown(test_init_snake, setup, teardown), 
        cmocka_unit_test_setup_teardown(test_forward_top_snake, setup, teardown),
        cmocka_unit_test_setup_teardown(test_forward_right_snake, setup, teardown),
        cmocka_unit_test_setup_teardown(test_forward_bot_snake, setup, teardown),
        cmocka_unit_test_setup_teardown(test_forward_left_snake, setup, teardown), 
        cmocka_unit_test_setup_teardown(test_turn_left_top_snake, setup, teardown)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}