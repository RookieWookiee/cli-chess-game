#include "include/piece.h"
#include "include/position.h"
#include "include/llist.h"
#include "include/board.h"
#include "include/movement_utils.h"

#include <assert.h>

static int validate_move(piece_t *self, pos_t target, board_t *board)
{
    assert(self);
    assert(board && board->squares);

    if(self->rank != target.rank && self->file != target.file)
        return 0;

    return standard_validation(self, target, board);
}

static llist_t *gen_moves(piece_t *self, board_t *board)
{
    llist_t *moves = NULL;

    add_moves_while_empty(board, self, EAST, &moves);
    add_moves_while_empty(board, self, SOUTH, &moves);
    add_moves_while_empty(board, self, WEST, &moves);
    add_moves_while_empty(board, self, NORTH, &moves);

    return moves;
}

const struct piece_vtable_ ROOK[] = { { validate_move, gen_moves } };
