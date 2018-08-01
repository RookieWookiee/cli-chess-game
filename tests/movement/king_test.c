#include <cgreen/cgreen.h>
#include <cgreen/mocks.h>
#include <stdbool.h>
#include <stdio.h>

#include "include/piece.h"
#include "include/board.h"
#include "include/llist.h"
#include "tests/macro_utils.h"


/* fakes */
void standard_validation(piece_t *self, pos_t target, board_t *board) { }
piece_t **get_square(board_t *self, uint8_t rank, uint8_t file) { return calloc(1, sizeof(piece_t*)); }
void push(llist_t **head_ref, void *new_data, size_t data_size);

/* mocks */
bool is_square_empty(board_t *self, uint8_t rank, uint8_t file);
bool is_enemy(piece_t *p1, piece_t *p2);
bool is_in_bounds(pos_t pos);

piece_t *king;
board_t *board;

Describe(King);
BeforeEach(King)
{
    king = malloc(sizeof(piece_t));
    king->vtable = KING;
    king->type_id = KING_W_ID;
    board = calloc(1, sizeof(board_t));
}
AfterEach(King) {}

Ensure(King, bound_checks_are_respected_in_move_generation)
{
    always_expect(is_in_bounds, will_return(false));
    always_expect(is_square_empty, will_return(true));
    always_expect(is_enemy, will_return(true));
    
    never_expect(push);

    generate_moves(king, board);
}

Ensure(King, failed_empty_square_checks_are_respected_no_push_in_move_generation)
{
    expect(is_in_bounds, will_return(true));
    expect(is_square_empty, will_return(false));
    expect(is_enemy, will_return(false));
    never_expect(push);

    always_expect(is_in_bounds, will_return(false));

    generate_moves(king, board);
}

Ensure(King, push_occurs_on_empty_squares)
{
    expect(is_in_bounds, will_return(true));
    expect(is_square_empty, will_return(true));

    always_expect(is_in_bounds, will_return(false));
    never_expect(is_square_empty);
    never_expect(is_enemy);

    expect(push);

    generate_moves(king, board);
}

Ensure(King, failed_enemy_checks_are_respected_no_push)
{
    expect(is_in_bounds, will_return(true));
    expect(is_square_empty, will_return(false));
    expect(is_enemy, will_return(false));

    always_expect(is_in_bounds, will_return(false));
    never_expect(push);

    generate_moves(king, board);
}

Ensure(King, push_occurs_when_enemy_is_occupying_target_square)
{
    expect(is_in_bounds, will_return(true));
    expect(is_square_empty, will_return(false));
    expect(is_enemy, will_return(true));
    always_expect(is_in_bounds, will_return(false));
    
    expect(push);

    generate_moves(king, board);
}

Ensure(King, eight_positions_are_tries_in_move_generation)
{
    expect_times(is_in_bounds, will_return(false), 8);

    generate_moves(king, board);
}

bool is_enemy(piece_t *p1, piece_t *p2)
{
    return (bool) mock(p1, p1);
}

void push(llist_t **head_ref, void *new_data, size_t data_size)
{
    mock(head_ref, new_data, data_size);
}

bool is_square_empty(board_t *self, uint8_t rank, uint8_t file)
{
    return (bool) mock(self, rank, file);
}

bool is_in_bounds(pos_t pos)
{
    return (bool) mock(&pos);
}
