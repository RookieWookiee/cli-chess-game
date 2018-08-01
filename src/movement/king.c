#include "include/piece.h"
#include "include/position.h"
#include "include/board.h"
#include "include/llist.h"
#include "include/movement_utils.h"

#include <stdlib.h>

static int validate_move(piece_t *self, pos_t target, board_t *board)
{
    int delta_rank = abs((int)self->rank - target.rank),
        delta_file = abs((int)self->file - target.file);

    if(delta_rank > 1 || delta_file > 1)
        return 0;

    return standard_validation(self, target, board);
}

static llist_t *gen_moves(piece_t *self, board_t *board)
{
    llist_t *moves = NULL;

    for(int dy = -1; dy <= 1; dy++) {
        for(int dx = -1; dx <= 1; dx++) {
            if(dy == 0 && dx == 0) continue;

            pos_t curr = { self->rank + dy, self->file + dx};

            if(!is_in_bounds(curr)) continue;

            if(is_square_empty(board, curr.rank, curr.file))
                push(&moves, &curr, sizeof(pos_t));
            else if(is_enemy(self, *get_square(board, curr.rank, curr.file)))
                push(&moves, &curr, sizeof(pos_t));
        }
    }

    return moves;
}

const struct piece_vtable_ KING[] = { { validate_move, gen_moves } };
