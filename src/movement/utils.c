#include "include/piece.h"
#include "include/position.h"
#include "include/board.h"
#include "include/llist.h"

#include <assert.h>

int standard_validation(piece_t *self, pos_t target, board_t *board)
{
    llist_t *legal_moves = generate_moves(self, board);
    int is_valid = contains(legal_moves, &target, position_equals);

    destroy(&legal_moves);
    assert(!legal_moves);

    return is_valid;
}

void add_moves_while_empty(board_t *board, piece_t *piece, direction_t direction, llist_t **moves)
{
    int dx, dy;
    switch(direction) {
        case NORTH_EAST: dy = UP;   dx = RIGHT; break;
        case SOUTH_EAST: dy = DOWN; dx = RIGHT; break;
        case SOUTH_WEST: dy = DOWN; dx = LEFT;  break;
        case NORTH_WEST: dy = UP;   dx = LEFT;  break;
        case NORTH     : dy = UP;   dx = NONE;  break;
        case SOUTH     : dy = DOWN; dx = NONE;  break;
        case EAST      : dy = NONE; dx = RIGHT; break;
        case WEST      : dy = NONE; dx = LEFT;  break;
    }

    pos_t curr_pos = { piece->rank + 1 * dy, piece->file + 1 * dx };

    while(is_in_bounds(curr_pos)) {
        if(is_square_empty(board, curr_pos.rank, curr_pos.file)) {
            push(moves, &curr_pos, sizeof(pos_t));
        } else {
            if(is_enemy(piece, *get_square(board, curr_pos.rank, curr_pos.file)))
                push(moves, &curr_pos, sizeof(pos_t));
            break;
        }

        curr_pos.rank += 1 * dy; curr_pos.file += 1 * dx;
    }
}
