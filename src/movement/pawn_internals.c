#include <stdbool.h>
#include <stdio.h>

#include "include/board.h"
#include "include/piece.h"
#include "include/llist.h"

bool try_push_two_squares_ahead(piece_t *self, board_t *board, llist_t *moves)
{
    bool color = get_color(self);
    int dir = color == WHITE ? -1 : 1;

    pos_t two_ahead = { self->rank + 2 * dir, self->file };
    bool ret = is_square_empty(board, two_ahead.rank, two_ahead.file);
    if(ret)
        push(&moves, &two_ahead, sizeof(pos_t));

    return ret;
}

bool try_push_one_square_ahead(piece_t *self, board_t *board, llist_t *moves)
{
    bool color = get_color(self);
    int dir = color == WHITE ? -1 : 1;
    pos_t one_ahead = { self->rank + 1 * dir, self->file };

    bool one_ahead_empty = is_in_bounds(one_ahead) && is_square_empty(board, one_ahead.rank, one_ahead.file);
    if(one_ahead_empty)
        push(&moves, &one_ahead, sizeof(pos_t));

    return one_ahead_empty;
}

bool try_push_lsquare(piece_t *self, board_t *board, llist_t *moves)
{
    bool color = get_color(self);
    int dir = color == WHITE ? -1 : 1;

    pos_t lsquare = { self->rank + 1 * dir, self->file - 1 };

    if(is_in_bounds(lsquare)) {
        piece_t **square = get_square(board, lsquare.rank, lsquare.file);
        if(!is_square_empty(board, lsquare.rank, lsquare.file) && is_enemy(self, *square)) {
            push(&moves, &lsquare, sizeof(pos_t));
            return true;
        }
    }

    return false;
}

bool try_push_rsquare(piece_t *self, board_t *board, llist_t *moves)
{
    bool color = get_color(self);
    int dir = color == WHITE ? -1 : 1;

    pos_t rsquare = { self->rank + 1 * dir, self->file + 1};
    if(is_in_bounds(rsquare)) {
        piece_t **square = get_square(board, rsquare.rank, rsquare.file);
        if(!is_square_empty(board, rsquare.rank, rsquare.file) && is_enemy(self, *square)) {
            push(&moves, &rsquare, sizeof(pos_t));
            return true;
        }
    }

    return false;
}
