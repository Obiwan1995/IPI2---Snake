#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../src/bonus.h"

#define UNIT_TESTING 1

static void test_take_bonus_self(void ** state)
{
	Board b = init_board1();
	int nb_snakes = 1;
	Serpent** snakes = malloc(nb_snakes * sizeof(Serpent*));
	Serpent* snake = malloc(sizeof(Serpent));
	Point p;
    p.x = X;
    p.y = Y;
    init_snake(snake, ID, SPEED, DIR, p);
    snakes[0] = snake;
    add_bonus(&b, snakes, nb_snakes);
    b.pTabBonus[0]->effect = self;
    b.pTabBonus[0]->type = increase_speed;
    b.pTabBonus[0]->duration = DEFAULT_DURATION;
    take_bonus(snake, b.pTabBonus[0]);
    assert_int_equal(snake->nNbBonus,1);
    assert_non_null(snake->tabBonus[0]);
    delete_bonus_snake(snake, 0);
    free_board(b);
    free_snakes(snakes, nb_snakes);
}

static void test_take_bonus_others(void ** state)
{
    Board b = init_board1();
    int nb_snakes = 2;
    Serpent** snakes = malloc(nb_snakes * sizeof(Serpent*));
    Serpent* snake = malloc(sizeof(Serpent));
    Point p;
    p.x = X;
    p.y = Y;
    init_snake(snake, ID, SPEED, DIR, p);
    Serpent* snake2 = malloc(sizeof(Serpent));
    p.x = X+1;
    p.y = Y+1;
    init_snake(snake2, ID, SPEED, DIR, p);
    snakes[0] = snake;
    snakes[1] = snake2;
    add_bonus(&b, snakes, nb_snakes);
    b.pTabBonus[0]->effect = others;
    b.pTabBonus[0]->type = increase_speed;
    b.pTabBonus[0]->duration = DEFAULT_DURATION;
    take_bonus(snake2, b.pTabBonus[0]);
    assert_int_equal(snake->nNbBonus,0);
    assert_int_equal(snake2->nNbBonus,1);
    assert_non_null(snake2->tabBonus[0]);
    delete_bonus_snake(snake2, 0);
    free_board(b);
    free_snakes(snakes, nb_snakes);
}

static void test_take_bonus_no_duration(void ** state)
{
    Board b = init_board1();
    int nb_snakes = 1;
    Serpent** snakes = malloc(nb_snakes * sizeof(Serpent*));
    Serpent* snake = malloc(sizeof(Serpent));
    Point p;
    p.x = X;
    p.y = Y;
    init_snake(snake, ID, SPEED, DIR, p);
    snakes[0] = snake;
    add_bonus(&b, snakes, nb_snakes);
    b.pTabBonus[0]->type = increase_speed;
    b.pTabBonus[0]->duration = 0;
    take_bonus(snake, b.pTabBonus[0]);
    assert_int_equal(snake->nNbBonus,0);
    assert_int_equal(b.nNbBonus, 1);
    free(b.pTabBonus[0]);
    delete_bonus_board(&b, 0);
    assert_int_equal(b.nNbBonus, 0);
    free_board(b);
    free_snakes(snakes, nb_snakes);
}

static void test_bonus_increase_speed(void ** state)
{
    Board b = init_board1();
    int nb_snakes = 1;
    Serpent** snakes = malloc(nb_snakes * sizeof(Serpent*));
    Serpent* snake = malloc(sizeof(Serpent));
    Point p;
    p.x = X;
    p.y = Y;
    init_snake(snake, ID, SPEED, DIR, p);
    snakes[0] = snake;
    add_bonus(&b, snakes, nb_snakes);
    b.pTabBonus[0]->type = increase_speed;
    b.pTabBonus[0]->duration = DEFAULT_DURATION;
    int speed = snake->vitesse;
    take_bonus(snake, b.pTabBonus[0]);
    assert_int_equal(snake->nNbBonus, 1);
    assert_int_equal(snake->vitesse, round(0.75*speed));
    delete_bonus_snake(snake, 0);
    assert_int_equal(snake->nNbBonus, 0);
    assert_int_equal(snake->vitesse, speed);
    free_board(b);
    free_snakes(snakes, nb_snakes);
}

static void test_bonus_decrease_speed(void ** state)
{
    Board b = init_board1();
    int nb_snakes = 1;
    Serpent** snakes = malloc(nb_snakes * sizeof(Serpent*));
    Serpent* snake = malloc(sizeof(Serpent));
    Point p;
    p.x = X;
    p.y = Y;
    init_snake(snake, ID, SPEED, DIR, p);
    snakes[0] = snake;
    add_bonus(&b, snakes, nb_snakes);
    b.pTabBonus[0]->type = decrease_speed;
    b.pTabBonus[0]->duration = DEFAULT_DURATION;
    int speed = snake->vitesse;
    take_bonus(snake, b.pTabBonus[0]);
    assert_int_equal(snake->nNbBonus, 1);
    assert_int_equal(snake->vitesse, round(1.25*speed));
    delete_bonus_snake(snake, 0);
    assert_int_equal(snake->nNbBonus, 0);
    assert_int_equal(snake->vitesse, speed);
    free_board(b);
    free_snakes(snakes, nb_snakes);
}

static void test_bonus_increase_size(void ** state)
{
    Board b = init_board1();
    int nb_snakes = 1;
    Serpent** snakes = malloc(nb_snakes * sizeof(Serpent*));
    Serpent* snake = malloc(sizeof(Serpent));
    Point p;
    p.x = X;
    p.y = Y;
    init_snake(snake, ID, SPEED, DIR, p);
    snakes[0] = snake;
    add_bonus(&b, snakes, nb_snakes);
    b.pTabBonus[0]->type = increase_size;
    b.pTabBonus[0]->duration = DEFAULT_DURATION;
    int gainSize = snake->pGainSize;
    take_bonus(snake, b.pTabBonus[0]);
    assert_int_equal(snake->nNbBonus, 1);
    assert_int_equal(snake->pGainSize, 100);
    delete_bonus_snake(snake, 0);
    assert_int_equal(snake->nNbBonus, 0);
    assert_int_equal(snake->pGainSize, gainSize);
    free_board(b);
    free_snakes(snakes, nb_snakes);
}

static void test_bonus_decrease_size(void ** state)
{
    Board b = init_board1();
    int nb_snakes = 1;
    Serpent** snakes = malloc(nb_snakes * sizeof(Serpent*));
    Serpent* snake = malloc(sizeof(Serpent));
    Point p;
    p.x = X;
    p.y = Y;
    init_snake(snake, ID, SPEED, DIR, p);
    snakes[0] = snake;
    add_bonus(&b, snakes, nb_snakes);
    b.pTabBonus[0]->type = decrease_size;
    b.pTabBonus[0]->duration = DEFAULT_DURATION;
    int gainSize = snake->pGainSize;
    take_bonus(snake, b.pTabBonus[0]);
    assert_int_equal(snake->nNbBonus, 1);
    assert_int_equal(snake->pGainSize, 0);
    delete_bonus_snake(snake, 0);
    assert_int_equal(snake->nNbBonus, 0);
    assert_int_equal(snake->pGainSize, gainSize);
    free_board(b);
    free_snakes(snakes, nb_snakes);
}

static void test_bonus_reverse_snake(void ** state)
{
    Board b = init_board1();
    int nb_snakes = 1;
    Serpent** snakes = malloc(nb_snakes * sizeof(Serpent*));
    Serpent* snake = malloc(sizeof(Serpent));
    Point p;
    p.x = X*2;
    p.y = Y*2;
    init_snake(snake, ID, SPEED, DIR, p);
    snakes[0] = snake;
    int i;
    int rand_move = rand()%10+10;
    for (i = 0; i < rand_move; i++)
    {
        Forward(snake);
    }

    Point pts[snake->taille];
    for (i = 0; i < snake->taille; i++)
    {
        pts[i] = snake->tab[i];
    }
    Point queue = snake->tab[0];

    add_bonus(&b, snakes, nb_snakes);
    b.pTabBonus[0]->type = reverse;
    b.pTabBonus[0]->duration = 0;

    take_bonus(snake, b.pTabBonus[0]);

    assert_int_equal(snake->nNbBonus, 0);
    assert_int_equal(snake->dir, bot);

    // On vérifie que les cases ont bien été inversées
    for (i = 0; i < snake->taille; i++)
    {
        assert_int_equal(snake->tab[i].x, pts[snake->taille-i-1].x);
        assert_int_equal(snake->tab[i].y, pts[snake->taille-i-1].y);
    }

    // On vérifie que la queue est bien passée en tête
    assert_int_equal(snake->tete.x, queue.x);
    assert_int_equal(snake->tete.y, queue.y);

    // On vérifie que l'ancienne queue se retrouve à la fin du tableau
    assert_int_equal(snake->tab[snake->taille-1].x, queue.x);
    assert_int_equal(snake->tab[snake->taille-1].y, queue.y);

    free(b.pTabBonus[0]);
    delete_bonus_board(&b, 0);
    assert_int_equal(snake->nNbBonus, 0);
    free_board(b);
    free_snakes(snakes, nb_snakes);
}

static void test_bonus_clean_snake(void ** state)
{
    Board b = init_board1();
    int nb_snakes = 1;
    Serpent** snakes = malloc(nb_snakes * sizeof(Serpent*));
    Serpent* snake = malloc(sizeof(Serpent));
    Point p;
    p.x = X;
    p.y = Y;
    init_snake(snake, ID, SPEED, DIR, p);
    snakes[0] = snake;
    add_bonus(&b, snakes, nb_snakes);
    b.pTabBonus[0]->type = clean;
    b.pTabBonus[0]->duration = 0;
    take_bonus(snake, b.pTabBonus[0]);
    assert_int_equal(snake->nNbBonus, 0);
    assert_int_equal(snake->taille, 1);
    assert_int_equal(snake->tete.x, snake->tab[0].x);
    assert_int_equal(snake->tete.y, snake->tab[0].y);
    free(b.pTabBonus[0]);
    delete_bonus_board(&b, 0);
    free_board(b);
    free_snakes(snakes, nb_snakes);
}

static void test_bonus_reverse_keys(void ** state)
{
    Board b = init_board1();
    int nb_snakes = 1;
    Serpent** snakes = malloc(nb_snakes * sizeof(Serpent*));
    Serpent* snake = malloc(sizeof(Serpent));
    Point p;
    p.x = X;
    p.y = Y;
    init_snake(snake, ID, SPEED, DIR, p);
    snakes[0] = snake;
    add_bonus(&b, snakes, nb_snakes);
    b.pTabBonus[0]->type = reverse_keys;
    b.pTabBonus[0]->duration = DEFAULT_DURATION;
    take_bonus(snake, b.pTabBonus[0]);
    assert_int_equal(snake->nNbBonus, 1);
    assert_int_equal(snake->reverse, 1);
    delete_bonus_snake(snake, 0);
    assert_int_equal(snake->nNbBonus, 0);
    assert_int_equal(snake->reverse, 0);
    free_board(b);
    free_snakes(snakes, nb_snakes);
}

static void test_bonus_change_snakes(void ** state)
{
    Board b = init_board1();
    int nb_snakes = 2;
    Serpent** snakes = malloc(nb_snakes * sizeof(Serpent*));
    Serpent* snake = malloc(sizeof(Serpent));
    Point p;
    p.x = X;
    p.y = Y;
    init_snake(snake, ID, SPEED, DIR, p);
    snakes[0] = snake;
    Serpent* snake2 = malloc(sizeof(Serpent));
    p.x = X*2;
    p.y = Y*2;
    init_snake(snake2, ID, SPEED, DIR, p);
    snakes[1] = snake2;
    int i;
    for (i = 0; i < 10; i++)
    {
        Forward(snake);
        Forward(snake2);
    }
    Point tab1[snake->taille];
    Point tab2[snake2->taille];
    for (i = 0; i < snake->taille; i++)
    {
        tab1[i] = snake->tab[i];
    }
    for (i = 0; i < snake2->taille; i++)
    {
        tab2[i] = snake2->tab[i];
    }
    change_snakes(snakes, nb_snakes, 0);
    for (i = 0; i < snakes[0]->taille; i++)
    {
        assert_int_equal(snakes[0]->tab[i].x, tab2[i].x);
        assert_int_equal(snakes[0]->tab[i].y, tab2[i].y);
    }
    for (i = 0; i < snakes[1]->taille; i++)
    {
        assert_int_equal(snakes[1]->tab[i].x, tab1[i].x);
        assert_int_equal(snakes[1]->tab[i].y, tab1[i].y);
    }
    assert_int_equal(snake->nNbBonus, 0);
    assert_int_equal(snake2->nNbBonus, 0);
    free_board(b);
    free_snakes(snakes, nb_snakes);
}

static void test_bonus_close_walls(void ** state)
{
    Board b = init_board1();
    int i, j, k, nbWalls;
    Point p;
    for (k = 1; k <= 10; k++)
    {
        nbWalls = b.nSize;
        close_walls(&b, k);
        assert_int_equal(b.nSize, nbWalls + 2*(b.nBoardWidth-2*k-1)+2*(b.nBoardHeight-2*k-1));
        for (i = 0; i < b.nBoardWidth; i++)
        {
            for (j = 0; j < b.nBoardHeight; j++)
            {
                if (i == k || j == k || i == b.nBoardWidth-1-k || j == b.nBoardHeight-1-k)
                {
                    p.x = i;
                    p.y = j;
                    assert_int_equal(belongs_to_tab(p, b.pPtsMur, b.nSize), 1);
                }
            }
        }
    }
    free_board(b);
}