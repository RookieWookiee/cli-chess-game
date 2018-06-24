#include "include/piece.h"
#include "include/position.h"
#include "include/llist.h"
#include "include/board.h"

#include <stdbool.h>
#include <assert.h>

static llist_t *gen_moves(piece_t *self, board_t *board);

static int validate_move(piece_t *self, pos_t target, board_t *board)
{
    assert(self);
    assert(self->type_id == PAWN_W_ID || self->type_id == PAWN_B_ID);

    llist_t *legal_moves = gen_moves(self, board);
    int is_valid = contains(legal_moves, &target, position_equals);
    destroy(&legal_moves);
    assert(legal_moves == NULL);

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

    int dir = get_color(self) == WHITE ? -1 : 1;
    int start_rank = get_color(self) == WHITE ? RANK_7 : RANK_2;
    int curr_rank = self->rank,
        curr_file = self->file;

    pos_t one_ahead = { curr_rank + 1 * dir, curr_file };
    if(self->rank == start_rank) {
        pos_t two_ahead = { curr_rank + 2 * dir, curr_file};

        if(is_square_empty(board, one_ahead.rank, one_ahead.file) &&
                is_square_empty(board, two_ahead.rank, two_ahead.file))
            push(&moves, &two_ahead, sizeof(pos_t));
    }

    if(is_in_bounds(one_ahead) && is_square_empty(board, one_ahead.rank, one_ahead.file))
        push(&moves, &one_ahead, sizeof(pos_t));

    pos_t lsquare = { curr_rank + 1 * dir, curr_file - 1};
    if(is_in_bounds(lsquare)) {
        piece_t **square = get_square(board, lsquare.rank, lsquare.file);
        if(!is_square_empty(board, lsquare.rank, lsquare.file) && is_enemy(self, *square)) {
            push(&moves, &lsquare, sizeof(pos_t));
        }
    }

    pos_t rsquare = { curr_rank + 1 * dir, curr_file + 1};
    if(is_in_bounds(rsquare)) {
        piece_t **square = get_square(board, rsquare.rank, rsquare.file);
        if(!is_square_empty(board, rsquare.rank, rsquare.file) && is_enemy(self, *square)) {
            push(&moves, &rsquare, sizeof(pos_t));
        }
    }

    return moves;
}

const struct piece_vtable_ PAWN[] = { { validate_move, gen_moves } };
