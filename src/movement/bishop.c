#include "include/board.h"
#include "include/piece.h"
#include "include/position.h"
#include "include/llist.h"

#include <assert.h>

static llist_t *gen_moves(piece_t *self, board_t *board);

static int validate_move(piece_t *self, pos_t target, board_t *board)
{
    llist_t *legal_moves = gen_moves(self, board);

    int is_valid = contains(legal_moves, &target, position_equals);
    destroy(&legal_moves);
    assert(!legal_moves);

    return is_valid;
}

static llist_t *gen_moves(piece_t *self, board_t *board)
{
    llist_t *moves = NULL;

    for(int diagonal = 0; diagonal < 4; diagonal++) {
        int dx, dy,
            rank = self->rank,
            file = self->file;

        switch(diagonal) {
            case 0: dy = UP,    dx = RIGHT; break;
            case 1: dy = DOWN,  dx = RIGHT; break;
            case 2: dy = DOWN,  dx = LEFT;  break;
            case 3: dy = UP,    dx = LEFT;  break;
        }

        while(true) {
            rank += 1 * dy;
            file += 1 * dx;
            pos_t curr_pos = { rank, file };

            if(!is_in_bounds(curr_pos))
                break;

            if(is_square_empty(board, rank, file)) {
                push(&moves, &curr_pos, sizeof(curr_pos));
            } else {
                if(is_enemy(self, *get_square(board, rank, file))) {
                    push(&moves, &curr_pos, sizeof(curr_pos));
                }
                break;
            }
        }
    }

    return moves;
}

const struct piece_vtable_ BISHOP[] = { { validate_move, gen_moves } };
