#include "include/piece.h"
#include "include/board.h"
#include "include/position.h"
#include "include/llist.h"
#include "include/movement_utils.h"

#include <assert.h>

static int validate_move(piece_t *self, pos_t target, board_t *board)
{
    assert(self);
    assert(board && board->squares);

    return standard_validation(self, target, board);
}

static llist_t *gen_moves(piece_t *self, board_t *board)
{
    llist_t *moves = NULL;

    add_moves_while_empty(board, self, EAST, &moves);
    add_moves_while_empty(board, self, SOUTH, &moves);
    add_moves_while_empty(board, self, WEST, &moves);
    add_moves_while_empty(board, self, NORTH, &moves);
    add_moves_while_empty(board, self, NORTH_EAST, &moves);
    add_moves_while_empty(board, self, SOUTH_EAST, &moves);
    add_moves_while_empty(board, self, SOUTH_WEST, &moves);
    add_moves_while_empty(board, self, NORTH_WEST, &moves);

    return moves;
}

const struct piece_vtable_ QUEEN[] = { { validate_move, gen_moves } };
