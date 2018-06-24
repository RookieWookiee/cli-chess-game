#include "include/piece.h"
#include "include/position.h"
#include "include/llist.h"

static int validate_move(piece_t *self, pos_t target, board_t *board)
{
    return 0;
}

static llist_t *gen_moves(piece_t *self, board_t *board)
{
    return NULL;
}

const struct piece_vtable_ ROOK[] = { { validate_move, gen_moves } };
