#include <cgreen/cgreen.h>
#include <cgreen/mocks.h>
#include <stdbool.h>
#include <stdio.h>

#include "include/piece.h"
#include "include/board.h"
#include "include/llist.h"
#include "include/pawn_internals.h"
#include "tests/macro_utils.h"

/* to keep the linker happy */
const struct piece_vtable_ ROOK[1], QUEEN[1], KNIGHT[1], BISHOP[1], KING[1], PAWN[1];

piece_t **get_square(board_t *self, uint8_t rank, uint8_t file) { return calloc(1, sizeof(piece_t*)); }

/* mocks */
bool is_in_bounds(pos_t pos);
bool is_square_empty(board_t *self, uint8_t rank, uint8_t file);
bool is_enemy(piece_t *p1, piece_t *p2);
void push(llist_t **head_ref, void *new_data, size_t data_size);
bool get_color(piece_t *piece);

piece_t *pawn;
board_t *board;

Describe(PawnInternals);
BeforeEach(PawnInternals)
{
    cgreen_mocks_are(loose_mocks);
    pawn = malloc(sizeof(*pawn)); pawn->type_id = PAWN_W_ID; pawn->vtable = PAWN;
    board = calloc(1, sizeof(board_t));
}
AfterEach(PawnInternals)
{
    free(pawn);
    free(board);
}

Ensure(PawnInternals, try_push_two_ahead_will_push_if_the_square_is_empty)
{
    always_expect(get_color, will_return(WHITE));
    expect(is_square_empty, will_return(true));
    expect(push);

    try_push_two_squares_ahead(pawn, board, NULL);
}

Ensure(PawnInternals, try_push_two_ahead_will_push_with_correct_position)
{
    always_expect(get_color, will_return(WHITE));
    pawn->rank = RANK_7; pawn->file = FILE_A;
    pos_t expected_push = { RANK_5, FILE_A };
    expect(is_square_empty, will_return(true));

    expect(push, when(new_data, is_equal_to_contents_of(&expected_push, sizeof(pos_t))));

    try_push_two_squares_ahead(pawn, board, NULL);
}

Ensure(PawnInternals, try_push_two_ahead_will_not_push_if_square_is_occupied)
{
    always_expect(get_color, will_return(WHITE));
    expect(is_square_empty, will_return(false));
    never_expect(push);

    try_push_two_squares_ahead(pawn, board, NULL);
}

Ensure(PawnInternals, try_push_one_ahead_will_push_if_in_bounds_and_square_is_empty)
{
    always_expect(get_color, will_return(WHITE));
    expect(is_square_empty, will_return(true));
    expect(is_in_bounds, will_return(true));
    expect(push);

    try_push_one_square_ahead(pawn, board, NULL);
}

Ensure(PawnInternals, try_push_one_ahead_will_not_push_if_either_condition_is_not_met)
{
    always_expect(get_color, will_return(WHITE));
    bool in_bounds_returns[] = { true, false };

    expect_many(is_in_bounds, will_return, in_bounds_returns);
    expect(is_square_empty, will_return(false));
    never_expect(is_square_empty);
    never_expect(push);

    try_push_one_square_ahead(pawn, board, NULL);
    try_push_one_square_ahead(pawn, board, NULL);
}

Ensure(PawnInternals, try_push_lsquare_will_push_if_not_empty_and_in_bounds_and_is_enemy)
{
    always_expect(get_color, will_return(WHITE));
    expect(is_square_empty, will_return(false));
    expect(is_in_bounds, will_return(true));
    expect(is_enemy, will_return(true));
    expect(push);

    try_push_lsquare(pawn, board, NULL);
}

Ensure(PawnInternals, try_push_lsquare_will_push_with_correct_pos)
{
    always_expect(get_color, will_return(WHITE));
    pawn->rank = RANK_6, pawn->file = FILE_B;
    pos_t expected_push = { RANK_5, FILE_A };

    expect(is_square_empty, will_return(false));
    expect(is_in_bounds, will_return(true));
    expect(is_enemy, will_return(true));
    expect(push, when(new_data, is_equal_to_contents_of(&expected_push, sizeof(pos_t))));

    try_push_lsquare(pawn, board, NULL);
}

Ensure(PawnInternals, try_push_lsquare_will_not_push_if_either_condition_is_not_met)
{
    always_expect(get_color, will_return(WHITE));

    bool in_bounds_returns[] = { true, false, true };
    bool sq_empty_returns[] = { true, false };
    bool is_enemy_returns[] = { false };

    expect_many(is_square_empty, will_return, sq_empty_returns);
    expect_many(is_in_bounds, will_return, in_bounds_returns);
    expect_many(is_enemy, will_return, is_enemy_returns);
    never_expect(push);

    try_push_lsquare(pawn, board, NULL);
    try_push_lsquare(pawn, board, NULL);
    try_push_lsquare(pawn, board, NULL);
}

Ensure(PawnInternals, try_push_rsquare_will_push_if_not_empty_and_in_bounds_and_is_enemy)
{
    always_expect(get_color, will_return(WHITE));
    expect(is_square_empty, will_return(false));
    expect(is_in_bounds, will_return(true));
    expect(is_enemy, will_return(true));
    expect(push);

    try_push_lsquare(pawn, board, NULL);
}

Ensure(PawnInternals, try_push_rsquare_will_push_with_correct_pos)
{
    always_expect(get_color, will_return(WHITE));
    pawn->rank = RANK_6, pawn->file = FILE_B;

    expect(is_square_empty, will_return(false));
    expect(is_in_bounds, will_return(true));
    expect(is_enemy, will_return(true));
    pos_t expected_push = { RANK_5, FILE_C };

    expect(push, when(new_data, is_equal_to_contents_of(&expected_push, sizeof(pos_t))));

    try_push_rsquare(pawn, board, NULL);
}

Ensure(PawnInternals, try_push_rsquare_will_not_push_if_either_condition_is_not_met)
{
    always_expect(get_color, will_return(WHITE));
    never_expect(push);
    bool in_bounds_returns[] = { true, false, true };
    bool square_empty_returns[] = { true, false };

    expect_many(is_in_bounds, will_return, in_bounds_returns);
    expect_many(is_square_empty, will_return, square_empty_returns);
    expect(is_enemy, will_return(false));

    try_push_rsquare(pawn, board, NULL);
    try_push_rsquare(pawn, board, NULL);
    try_push_rsquare(pawn, board, NULL);
}

Ensure(PawnInternals, try_push_two_squares_pushes_correct_position_for_black_pawns)
{
    always_expect(get_color, will_return(BLACK));
    pawn->type_id = PAWN_B_ID;
    pawn->rank = RANK_2, pawn->file = FILE_A;

    pos_t expected_push = { RANK_4, FILE_A };

    expect(is_square_empty, will_return(true));
    expect(push, when(new_data, is_equal_to_contents_of(&expected_push, sizeof(pos_t))));

    try_push_two_squares_ahead(pawn, board, NULL);
}

Ensure(PawnInternals, try_push_one_square_pushes_correct_position_for_black_pawns)
{
    always_expect(get_color, will_return(BLACK));
    pawn->type_id = PAWN_B_ID;
    pawn->rank = RANK_2, pawn->file = FILE_A;

    pos_t expected_push = { RANK_3, FILE_A };

    expect(is_in_bounds, will_return(true));
    expect(is_square_empty, will_return(true));
    expect(push, when(new_data, is_equal_to_contents_of(&expected_push, sizeof(pos_t))));

    try_push_one_square_ahead(pawn, board, NULL);
}

Ensure(PawnInternals, try_push_lsquare_and_rsquare_pushes_correct_position_for_black_pawns)
{
    always_expect(get_color, will_return(BLACK));
    pawn->type_id = PAWN_B_ID;
    pawn->rank = RANK_2, pawn->file = FILE_B;

    pos_t expected_push1 = { RANK_3, FILE_A };
    pos_t expected_push2 = { RANK_3, FILE_C };

    expect_times(is_in_bounds, will_return(true), 2);
    expect_times(is_square_empty, will_return(false), 2);
    expect_times(is_enemy, will_return(true), 2);
    expect(push, when(new_data, is_equal_to_contents_of(&expected_push1, sizeof(pos_t))));
    expect(push, when(new_data, is_equal_to_contents_of(&expected_push2, sizeof(pos_t))));

    try_push_lsquare(pawn, board, NULL);
    try_push_rsquare(pawn, board, NULL);
}

/* mocks */
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

void push(llist_t **head_ref, void *new_data, size_t data_size)
{
    mock(head_ref, new_data, data_size);
}

bool get_color(piece_t *piece)
{
    return (bool) mock(piece);
}
