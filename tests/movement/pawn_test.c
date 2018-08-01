#include <cgreen/cgreen.h>
#include <cgreen/mocks.h>
#include <stdbool.h>
#include <stdio.h>

#include "include/piece.h"
#include "include/board.h"
#include "include/llist.h"

/* to keep the linker happy */
static int fake_validate(piece_t *self, pos_t target, board_t *board) {}
static llist_t *fake_gen_moves(piece_t *self, board_t *board) {}

const struct piece_vtable_ ROOK[] = { { fake_validate, fake_gen_moves } };
const struct piece_vtable_ QUEEN[] = { { fake_validate, fake_gen_moves } };
const struct piece_vtable_ KNIGHT[] = { { fake_validate, fake_gen_moves } };
const struct piece_vtable_ BISHOP[] = { { fake_validate, fake_gen_moves } };
const struct piece_vtable_ KING[] = { { fake_validate, fake_gen_moves } };

bool position_equals(const void *p1, const void *p2) {}
bool contains(llist_t *node, void *obj, bool (*equals_fptr)(const void*, const void*)) {}
void destroy(llist_t **head_ref) {}

/* calloc because the return value is being dereferenced in the SUT */
piece_t **get_square(board_t *self, uint8_t rank, uint8_t file) { return calloc(1, sizeof(piece_t*)); }

//bool is_in_bounds(pos_t pos)
//{
//    return (bool) mock(&pos);
//}
//
//bool is_square_empty(board_t *self, uint8_t rank, uint8_t file)
//{
//    return (bool) mock(self, rank, file);
//}
//
//bool is_enemy(piece_t *p1, piece_t *p2)
//{
//    return (bool) mock(p1, p1);
//}
//
//void push(llist_t **head_ref, void *new_data, size_t data_size)
//{
//    mock(head_ref, new_data, data_size);
//}
//
bool get_color(piece_t *piece)
{
    return (bool) mock(piece);
}

bool try_push_two_squares_ahead(piece_t *self, board_t *board, llist_t *moves) 
{
    return (bool) mock(self, board, moves);
}

bool try_push_one_square_ahead(piece_t *self, board_t *board, llist_t *moves)
{
    return (bool) mock(self, board, moves);
}

bool try_push_lsquare(piece_t *self, board_t *board, llist_t *moves)
{
    return (bool) mock(self, board, moves);
}


bool try_push_rsquare(piece_t *self, board_t *board, llist_t *moves)
{
    return (bool) mock(self, board, moves);
}

piece_t *pawn;
board_t *board;

Describe(Pawn);
BeforeEach(Pawn)
{
    cgreen_mocks_are(loose_mocks);
    pawn = malloc(sizeof(*pawn)); pawn->type_id = PAWN_W_ID; pawn->vtable = PAWN;
    pawn->rank = RANK_7, pawn->file = FILE_A;
    board = calloc(1, sizeof(board_t));
}
/* there's no real need for freeing since the tests run in their own separate processes. */
AfterEach(Pawn)
{
    generate_moves(pawn, board);
    free(pawn);
    free(board);
}

Ensure(Pawn, move_gen_pushes_two_squares_at_starting_pos)
{
    expect(get_color, will_return(WHITE));
    expect(try_push_one_square_ahead, will_return(true));
    expect(try_push_two_squares_ahead);
}

Ensure(Pawn, move_gen_tries_to_push_one_square_ahead)
{
    expect(try_push_one_square_ahead);
}

Ensure(Pawn, move_gen_tries_to_push_left_square)
{
    expect(try_push_lsquare);
}

Ensure(Pawn, move_gen_tries_to_push_right_square)
{
    expect(try_push_rsquare);
}

//Ensure(Pawn, move_gen_push_two_squares_at_starting_pos)
//{
//    pawn->rank = RANK_7, pawn->file = FILE_A;
//
//    pos_t expected_push1 = { RANK_6, FILE_A };
//    pos_t expected_push2 = { RANK_5, FILE_A };
//
//    always_expect(get_color, will_return(WHITE));
//    expect(is_in_bounds, will_return(true));
//
//    expect(is_square_empty, will_return(true));
//    expect(is_square_empty, will_return(true));
//    expect(push, when(new_data, is_equal_to_contents_of(&expected_push1, sizeof(pos_t))));
//    expect(push, when(new_data, is_equal_to_contents_of(&expected_push2, sizeof(pos_t))));
//
//    generate_moves(pawn, board);
//}
//
//Ensure(Pawn, move_gen_still_pushes_one_square_at_start_if_second_is_occupied)
//{
//    pawn->rank = RANK_7, pawn->file = FILE_A;
//
//    pos_t expected_push = { RANK_6, FILE_A };
//
//    always_expect(get_color, will_return(WHITE));
//    expect(is_in_bounds,
//            when(&pos, is_equal_to_contents_of(&expected_push, sizeof(expected_push))),
//            will_return(true));
//
//    expect(is_square_empty,
//            when(rank, is_equal_to(expected_push.rank)),
//            when(file, is_equal_to(expected_push.file)),
//            will_return(true));
//    expect(is_square_empty, will_return(false));
//    expect(push, when(new_data, is_equal_to_contents_of(&expected_push, sizeof(pos_t))));
//
//    generate_moves(pawn, board);
//}
//
//Ensure(Pawn, move_gen_does_not_push_two_square_ahead_position_if_first_is_occupied)
//{
//    pawn->rank = RANK_7, pawn->file = FILE_A;
//
//    pos_t two_ahead = { RANK_5, FILE_A };
//
//    expect(is_in_bounds, will_return(true));
//    expect(is_square_empty, will_return(false));
//    always_expect(is_in_bounds, will_return(false));
//
//    always_expect(push, when(new_data, is_not_equal_to_contents_of(&two_ahead, sizeof(pos_t))));
//
//    generate_moves(pawn, board);
//}
//
//Ensure(Pawn, move_gen_pushes_left_square_when_there_is_an_enemy)
//{
//    pawn->rank = RANK_6, pawn->file = FILE_B;
//    pos_t expected_push = { RANK_5, FILE_A };
//
//    always_expect(get_color, will_return(WHITE));
//    expect(is_in_bounds, will_return(true));
//    expect(is_square_empty, will_return(false));
//
//    expect(is_in_bounds,
//            when(&pos, is_equal_to_contents_of(&expected_push, sizeof(pos_t))),
//            will_return(true));
//
//    expect(is_square_empty, will_return(false));
//    expect(is_enemy, will_return(true));
//
//    expect(push, when(new_data, is_equal_to_contents_of(&expected_push, sizeof(pos_t))));
//
//    generate_moves(pawn, board);
//}
//
//Ensure(Pawn, move_gen_pushes_right_square_when_there_is_an_enemy)
//{
//
//}
