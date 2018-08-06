#include <cgreen/cgreen.h>
#include <cgreen/mocks.h>
#include <stdbool.h>
#include <stdio.h>

#include "include/piece.h"
#include "include/board.h"
#include "include/llist.h"

/* to keep the linker happy */
static int fake_validate(piece_t *self, pos_t target, board_t *board) { return 0; }
static llist_t *fake_gen_moves(piece_t *self, board_t *board) { return NULL; }

const struct piece_vtable_ ROOK[] = { { fake_validate, fake_gen_moves } };
const struct piece_vtable_ QUEEN[] = { { fake_validate, fake_gen_moves } };
const struct piece_vtable_ KNIGHT[] = { { fake_validate, fake_gen_moves } };
const struct piece_vtable_ BISHOP[] = { { fake_validate, fake_gen_moves } };
const struct piece_vtable_ KING[] = { { fake_validate, fake_gen_moves } };

bool position_equals(const void *p1, const void *p2) { return false; }
int standard_validation(piece_t *self, pos_t target, board_t *board) { return 1; }

/* calloc because the return value is being dereferenced in the SUT */
piece_t **get_square(board_t *self, uint8_t rank, uint8_t file) { return calloc(1, sizeof(piece_t*)); }

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
    free(pawn);
    free(board);
}

Ensure(Pawn, move_gen_pushes_two_squares_at_starting_pos)
{
    expect(get_color, will_return(WHITE));
    expect(try_push_one_square_ahead, will_return(true));
    expect(try_push_two_squares_ahead);
    generate_moves(pawn, board);
}

Ensure(Pawn, move_gen_tries_to_push_one_square_ahead)
{
    expect(try_push_one_square_ahead);
    generate_moves(pawn, board);
}

Ensure(Pawn, move_gen_tries_to_push_left_square)
{
    expect(try_push_lsquare);
    generate_moves(pawn, board);
}

Ensure(Pawn, move_gen_tries_to_push_right_square)
{
    expect(try_push_rsquare);
    generate_moves(pawn, board);
}

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
