#include "include/piece.h"
#include "include/position.h"
#include "include/llist.h"
#include "include/board.h"
#include "include/pawn_internals.h"
#include "include/movement_utils.h"

#include <stdbool.h>
#include <assert.h>

static int validate_move(piece_t *self, pos_t target, board_t *board)
{
    assert(self);
    assert(self->type_id == PAWN_W_ID || self->type_id == PAWN_B_ID);

    int is_valid = standard_validation(self, target, board);

    if(is_valid) {
        if(get_color(self) == WHITE ? target.rank == RANK_1 : target.rank == RANK_8)
            return 15; //TODO: make a PROMOTION constant and return that instead
    }

    return is_valid;
}

static llist_t *gen_moves(piece_t *self, board_t *board)
{
    assert(self);
    assert(board);
    assert(self->type_id == PAWN_W_ID || self->type_id == PAWN_B_ID);

    llist_t *moves = NULL;

    bool color = get_color(self);
    int start_rank = color == WHITE ? RANK_7 : RANK_2;

    bool one_ahead_is_empty = try_push_one_square_ahead(self, board, moves);

    if(self->rank == start_rank && one_ahead_is_empty)
        try_push_two_squares_ahead(self, board, moves); 

    try_push_lsquare(self, board, moves);
    try_push_rsquare(self, board, moves);

    return moves;
}

const struct piece_vtable_ PAWN[] = { { validate_move, gen_moves } };
