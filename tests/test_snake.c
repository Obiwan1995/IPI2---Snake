#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../src/snake.h"
#include "../src/obstacle.h"

#define UNIT_TESTING 1
#define ID 1
#define SPEED 10
#define DIR 1
#define X 10
#define Y 10

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

static void test_turn_left_right_snake(void ** state)
{
    Serpent* snake = *state;
    snake->dir = 2;
    Left(snake);
    assert_non_null(snake);
    assert_int_equal(snake->tete.x, X);
    assert_int_equal(snake->tete.y, Y-1);
    assert_int_equal(snake->dir, 1);
}

static void test_turn_left_bot_snake(void ** state)
{
    Serpent* snake = *state;
    snake->dir = 3;
    Left(snake);
    assert_non_null(snake);
    assert_int_equal(snake->tete.x, X+1);
    assert_int_equal(snake->tete.y, Y);
    assert_int_equal(snake->dir, 2);
}

static void test_turn_left_left_snake(void ** state)
{
    Serpent* snake = *state;
    snake->dir = 4;
    Left(snake);
    assert_non_null(snake);
    assert_int_equal(snake->tete.x, X);
    assert_int_equal(snake->tete.y, Y+1);
    assert_int_equal(snake->dir, 3);
}

static void test_turn_right_top_snake(void ** state)
{
    Serpent* snake = *state;
    Right(snake);
    assert_non_null(snake);
    assert_int_equal(snake->tete.x, X+1);
    assert_int_equal(snake->tete.y, Y);
    assert_int_equal(snake->dir, 2);
}

static void test_turn_right_right_snake(void ** state)
{
    Serpent* snake = *state;
    snake->dir = 2;
    Right(snake);
    assert_non_null(snake);
    assert_int_equal(snake->tete.x, X);
    assert_int_equal(snake->tete.y, Y+1);
    assert_int_equal(snake->dir, 3);
}

static void test_turn_right_bot_snake(void ** state)
{
    Serpent* snake = *state;
    snake->dir = 3;
    Right(snake);
    assert_non_null(snake);
    assert_int_equal(snake->tete.x, X-1);
    assert_int_equal(snake->tete.y, Y);
    assert_int_equal(snake->dir, 4);
}

static void test_turn_right_left_snake(void ** state)
{
    Serpent* snake = *state;
    snake->dir = 4;
    Right(snake);
    assert_non_null(snake);
    assert_int_equal(snake->tete.x, X);
    assert_int_equal(snake->tete.y, Y-1);
    assert_int_equal(snake->dir, 1);
}

static void test_collision_no_collision_forward(void ** state)
{
    Serpent* snake = *state;
    int nb_snakes = 1;
    Serpent** snakes = malloc(nb_snakes * sizeof(Serpent));
    snakes[0] = snake;
    Board b = init_board1();
    // 1 time forward
    Forward(snake);
    assert_int_equal(test_collision(&b, snakes, nb_snakes), 0);
}

static void test_collision_no_collision_left(void ** state)
{
    Serpent* snake = *state;
    int nb_snakes = 1;
    Serpent** snakes = malloc(nb_snakes * sizeof(Serpent));
    snakes[0] = snake;
    Board b = init_board1();
    // Turn left
    Left(snake);
    assert_int_equal(test_collision(&b, snakes, nb_snakes), 0);
}

static void test_collision_no_collision_right(void ** state)
{
    Serpent* snake = *state;
    int nb_snakes = 1;
    Serpent** snakes = malloc(nb_snakes * sizeof(Serpent));
    snakes[0] = snake;
    Board b = init_board1();
    // Turn right
    Right(snake);
    assert_int_equal(test_collision(&b, snakes, nb_snakes), 0);
}

static void test_collision_head_body(void ** state)
{
    srand(time(NULL));
    Serpent* snake = *state;
    int nb_snakes = 1;
    Serpent** snakes = malloc(nb_snakes * sizeof(Serpent));
    snakes[0] = snake;
    Board b = init_board1();
    // 8 times forward (just to be sure we have at least one point)
    int i;
    for (i = 0; i < 8; i++)
    {
        Forward(snake);
    }
    
    // We move the head to the previous position
    snake->tete.x = X;
    snake->tete.y = Y-7;
    assert_int_equal(test_collision(&b, snakes, nb_snakes), ID);
}

static void test_collision_head_wall_forward(void ** state)
{
    srand(time(NULL));
    Serpent* snake = *state;
    int nb_snakes = 1;
    Serpent** snakes = malloc(nb_snakes * sizeof(Serpent));
    snakes[0] = snake;
    Board b = init_board1();

    // We move the head next to a wall
    snake->tete.x = X;
    snake->tete.y = Y-9;
    assert_int_equal(test_collision(&b, snakes, nb_snakes), 0);

    Forward(snake);    
    assert_int_equal(test_collision(&b, snakes, nb_snakes), ID);
}

static void test_collision_head_wall_left(void ** state)
{
    srand(time(NULL));
    Serpent* snake = *state;
    int nb_snakes = 1;
    Serpent** snakes = malloc(nb_snakes * sizeof(Serpent));
    snakes[0] = snake;
    Board b = init_board1();

    // We move the head along a wall
    snake->tete.x = X-9;
    snake->tete.y = Y;
    assert_int_equal(test_collision(&b, snakes, nb_snakes), 0);

    Left(snake);    
    assert_int_equal(test_collision(&b, snakes, nb_snakes), ID);
}

static void test_collision_head_wall_right(void ** state)
{
    srand(time(NULL));
    Serpent* snake = *state;
    int nb_snakes = 1;
    Serpent** snakes = malloc(nb_snakes * sizeof(Serpent));
    snakes[0] = snake;
    Board b = init_board1();

    // We move the head along a wall
    snake->tete.x = BOARD_WIDTH-2;
    snake->tete.y = Y;
    assert_int_equal(test_collision(&b, snakes, nb_snakes), 0);

    Right(snake); 
    assert_int_equal(test_collision(&b, snakes, nb_snakes), ID);
}

static void test_collision_two_snakes_head_head(void ** state)
{
    srand(time(NULL));
    Serpent* snake = *state;
    int nb_snakes = 2;
    Serpent* snake2 = malloc(sizeof(Serpent));
    Point p;
    p.x = X+1;
    p.y = Y+1;
    init_snake(snake2, ID+1, SPEED, 3, p);
    assert_non_null(snake2);

    Serpent** snakes = malloc(nb_snakes * sizeof(Serpent));
    snakes[0] = snake;
    snakes[1] = snake2;
    Board b = init_board1();
    assert_int_equal(test_collision(&b, snakes, nb_snakes), 0);

    // We move the head of the second snake to the initial position of the first one
    snake2->tete.x = X;
    snake2->tete.y = Y;
    assert_int_equal(test_collision(&b, snakes, nb_snakes), ID+1);
}

static void test_collision_two_snakes_head_body(void ** state)
{
    srand(time(NULL));
    Serpent* snake = *state;
    int nb_snakes = 2;
    Serpent* snake2 = malloc(sizeof(Serpent));
    Point p;
    p.x = X+1;
    p.y = Y+1;
    init_snake(snake2, ID+1, SPEED, 3, p);
    assert_non_null(snake2);
    snake2->dir = 3;

    // 8 times forward (just to be sure we have at least one point)
    int i;
    for (i = 0; i < 8; i++)
    {
        Forward(snake2);
    }

    Serpent** snakes = malloc(nb_snakes * sizeof(Serpent));
    snakes[0] = snake;
    snakes[1] = snake2;
    Board b = init_board1();
    assert_int_equal(test_collision(&b, snakes, nb_snakes), 0);

    // We move the head of the first snake to a position in the body of the second one
    snake->tete.x = X+1;
    snake->tete.y = Y+8;
    assert_int_equal(test_collision(&b, snakes, nb_snakes), ID);
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
        cmocka_unit_test_setup_teardown(test_turn_left_top_snake, setup, teardown), 
        cmocka_unit_test_setup_teardown(test_turn_left_right_snake, setup, teardown),
        cmocka_unit_test_setup_teardown(test_turn_left_bot_snake, setup, teardown),
        cmocka_unit_test_setup_teardown(test_turn_left_left_snake, setup, teardown),
        cmocka_unit_test_setup_teardown(test_turn_right_top_snake, setup, teardown),
        cmocka_unit_test_setup_teardown(test_turn_right_right_snake, setup, teardown),
        cmocka_unit_test_setup_teardown(test_turn_right_bot_snake, setup, teardown),
        cmocka_unit_test_setup_teardown(test_turn_right_left_snake, setup, teardown),
        cmocka_unit_test_setup_teardown(test_collision_no_collision_forward, setup, teardown),
        cmocka_unit_test_setup_teardown(test_collision_no_collision_left, setup, teardown),
        cmocka_unit_test_setup_teardown(test_collision_no_collision_right, setup, teardown),
        cmocka_unit_test_setup_teardown(test_collision_head_body, setup, teardown),
        cmocka_unit_test_setup_teardown(test_collision_head_wall_forward, setup, teardown),
        cmocka_unit_test_setup_teardown(test_collision_head_wall_left, setup, teardown),
        cmocka_unit_test_setup_teardown(test_collision_head_wall_right, setup, teardown),
        cmocka_unit_test_setup_teardown(test_collision_two_snakes_head_head, setup, teardown),
        cmocka_unit_test_setup_teardown(test_collision_two_snakes_head_body, setup, teardown)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}