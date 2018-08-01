#include <cgreen/cgreen.h>
#include <cgreen/mocks.h>
#include <stdio.h>

#include "include/piece.h"
#include "include/board.h"
#include "include/llist.h"


int add_while_empty_num_calls_by_direction[MAX_DIRECTION] = { 0 };
piece_t *rook;
board_t *board;

/* fakes */
void standard_validation(piece_t *self, pos_t target, board_t *board) { }
void add_moves_while_empty(board_t *board, piece_t *self, direction_t direction, llist_t **moves)
{
    add_while_empty_num_calls_by_direction[direction]++;
}

Describe(Rook);
BeforeEach(Rook)
{
    cgreen_mocks_are(loose_mocks);
    rook = malloc(sizeof(piece_t));
    board = calloc(1, sizeof(board_t));

    rook->type_id = ROOK_W_ID;
    rook->vtable = ROOK;
}
AfterEach(Rook) {}

Ensure(Rook, move_generation_tries_to_push_correct_directions)
{
    generate_moves(rook, board);

    assert_that(add_while_empty_num_calls_by_direction[NORTH], is_equal_to(1));
    assert_that(add_while_empty_num_calls_by_direction[EAST], is_equal_to(1));
    assert_that(add_while_empty_num_calls_by_direction[SOUTH], is_equal_to(1));
    assert_that(add_while_empty_num_calls_by_direction[WEST], is_equal_to(1));

    assert_that(add_while_empty_num_calls_by_direction[NORTH_EAST], is_equal_to(0));
    assert_that(add_while_empty_num_calls_by_direction[SOUTH_EAST], is_equal_to(0));
    assert_that(add_while_empty_num_calls_by_direction[SOUTH_WEST], is_equal_to(0));
    assert_that(add_while_empty_num_calls_by_direction[NORTH_WEST], is_equal_to(0));
}
