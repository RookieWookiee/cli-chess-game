#include <cgreen/cgreen.h>
#include <cgreen/mocks.h>
#include <stdbool.h>
#include <stdio.h>

#include "include/piece.h"
#include "include/board.h"
#include "include/llist.h"
#include "tests/macro_utils.h"


void standard_validation(piece_t *self, pos_t target, board_t *board) { }

piece_t **get_square(board_t *self, uint8_t rank, uint8_t file) { return calloc(1, sizeof(piece_t*)); }

bool is_in_bounds(pos_t pos);
bool is_square_empty(board_t *self, uint8_t rank, uint8_t file);
bool is_enemy(piece_t *p1, piece_t *p2);

piece_t *knight;
board_t *board;

Describe(Knight);
BeforeEach(Knight)
{
    cgreen_mocks_are(loose_mocks);
    knight = malloc(sizeof(*knight)); knight->type_id = KNIGHT_W_ID; knight->vtable = KNIGHT;
    board = calloc(1, sizeof(board_t));
    always_expect(get_color, will_return(WHITE));
}
AfterEach(Knight)
{
    free(knight);
    free(board);
}

Ensure(Knight, generated_moves_tries_eight_positions)
{
    for(int i = 0; i < 8; i++)
        expect(is_in_bounds);

    generate_moves(knight, board);
}

Ensure(Knight, bound_checking_is_respected_in_move_generation)
{
    always_expect(is_in_bounds, will_return(false));

    llist_t *moves = generate_moves(knight, board);
    assert_that(count(moves), is_equal_to(0));
}

Ensure(Knight, empty_square_checking_is_respected_in_move_generation)
{
    always_expect(is_in_bounds, will_return(true));
    always_expect(is_square_empty, will_return(false));

    llist_t *moves = generate_moves(knight, board);
    assert_that(count(moves), is_equal_to(0));
}

Ensure(Knight, enemy_checking_is_respected_in_move_generation)
{
    always_expect(is_in_bounds, will_return(true));
    always_expect(is_square_empty, will_return(false));
    always_expect(is_enemy, will_return(false));

    llist_t *moves = generate_moves(knight, board);
    assert_that(count(moves), is_equal_to(0));
}

Ensure(Knight, push_occurs_if_all_checks_are_met)
{
    expect(is_in_bounds, will_return(true));
    expect(is_square_empty, will_return(false));
    expect(is_enemy, will_return(true));

    always_expect(is_in_bounds, will_return(false));
    always_expect(is_enemy, will_return(false));
    always_expect(is_square_empty, will_return(false));

    llist_t *moves = generate_moves(knight, board);
    assert_that(count(moves), is_equal_to(1));
}

bool is_in_bounds(pos_t pos)
{
    return (bool) mock(&pos);
}

bool is_square_empty(board_t *self, uint8_t rank, uint8_t file)
{
    return (bool) mock(self, rank, file);
}

bool is_enemy(piece_t *p1, piece_t *p2)
{
    return (bool) mock(p1, p1);
}
