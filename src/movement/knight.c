#include "include/piece.h"
#include "include/position.h"
#include "include/board.h"
#include "include/llist.h"
#include "include/movement_utils.h"

#include <assert.h>

static int validate_move(piece_t *self, pos_t target, board_t *board)
{
    return standard_validation(self, target, board);
}

static llist_t *gen_moves(piece_t *self, board_t *board)
{
    llist_t *moves = NULL;
    int r = self->rank, f = self->file;

    /*  . . . . . . .
     *  . . 8 . 1 . .
     *  . 7 . . . 2 .
     *  . . . N . . .
     *  . 6 . . . 3 .
     *  . . 5 . 4 . . */
    pos_t positions[] = {
        { r - 2, f + 1 }, { r - 1, f + 2},
        { r + 1, f + 2 }, { r + 2, f + 1},
        { r + 2, f - 1 }, { r - 1, f + 2},
        { r - 1, f - 2 }, { r - 2, f - 1},
    };

    for(size_t i = 0; i < 8; i++) {
        if(!is_in_bounds(positions[i]))
            continue;

        int curr_rank = positions[i].rank,
            curr_file = positions[i].file;

        if(is_square_empty(board, curr_rank, curr_file)) {
            push(&moves, &positions[i], sizeof(pos_t));
        } else if(is_enemy(self, *get_square(board, curr_rank, curr_file))) {
            push(&moves, &positions[i], sizeof(pos_t));
        }
    }
    
    return moves;
}

const struct piece_vtable_ KNIGHT[] = { { validate_move, gen_moves } };
