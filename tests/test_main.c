#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <time.h>

#include "test_snake.c"
#include "test_board.c"
#include "test_bonus.c"

#define UNIT_TESTING 1


int main(void) 
{
	srand(time(NULL));
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
        cmocka_unit_test(test_init_board_big),
    	cmocka_unit_test(test_init_walls),
        cmocka_unit_test(test_is_cell_free),
        cmocka_unit_test(test_add_wall),
        cmocka_unit_test(test_add_tunnels),
        cmocka_unit_test(test_handle_tunnels),
        cmocka_unit_test(test_add_bonus)
    };

    const struct CMUnitTest tests_bonus[] = 
    {
        cmocka_unit_test(test_take_bonus_self),
        cmocka_unit_test(test_take_bonus_others),
        cmocka_unit_test(test_take_bonus_no_duration),
        cmocka_unit_test(test_bonus_increase_speed),
        cmocka_unit_test(test_bonus_decrease_speed),
        cmocka_unit_test(test_bonus_increase_size),
        cmocka_unit_test(test_bonus_decrease_size),
        cmocka_unit_test(test_bonus_reverse_snake),
        cmocka_unit_test(test_bonus_clean_snake),
        cmocka_unit_test(test_bonus_reverse_keys),
        cmocka_unit_test(test_bonus_change_snakes),
        cmocka_unit_test(test_bonus_close_walls)
    };

    printf("########## TESTS SNAKE ##########\n\n");
    cmocka_run_group_tests(tests_snake, NULL, NULL);
    printf("\n");
    printf("########## TESTS BOARD ##########\n\n");
    cmocka_run_group_tests(tests_board, NULL, NULL);
    printf("\n");
    printf("########## TESTS BONUS ##########\n\n");
    cmocka_run_group_tests(tests_bonus, NULL, NULL);

    return 0;
}