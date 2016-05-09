#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "test_snake.c"
#include "test_board.c"

#define UNIT_TESTING 1


int main(void) 
{
	const struct CMUnitTest tests_snake[] = 
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

    const struct CMUnitTest tests_board[] = 
    {
    	cmocka_unit_test(test_init_board1),
    	cmocka_unit_test(test_init_board_1v1),
    	cmocka_unit_test(test_init_walls)
    };

    printf("########## TESTS SNAKE ##########\n\n");
    cmocka_run_group_tests(tests_snake, NULL, NULL);
    printf("\n");
    printf("########## TESTS BOARD ##########\n\n");
    cmocka_run_group_tests(tests_board, NULL, NULL);

    return 0;
}