#define UNIT_TESTING 1
#define SPEED 10
#define ID 1

#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../src/snake.h"

static int setup(void **state) {
    Serpent* snake = malloc(sizeof(Serpent));
    init_snake(snake, 10, ID, SPEED);
    assert_non_null(snake);
    *state = snake;
    return 0;
}

static int teardown(void **state) {
    free(*state);
    return 0;
}

static void test_init_id(void **state) {
    Serpent* snake = *state;
    assert_int_equal(snake->id, ID);
}

static void test_init_speed(void **state) {
	Serpent* snake = *state;
	assert_int_equal(snake->vitesse, SPEED);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(test_init_id, setup, teardown),
        cmocka_unit_test_setup_teardown(test_init_speed, setup, teardown)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}