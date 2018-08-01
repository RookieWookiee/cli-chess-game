#ifndef PAWN_INTERNALS_H
#define PAWN_INTERNALS_H

bool try_push_two_squares_ahead(piece_t *self, board_t *board, llist_t *moves);
bool try_push_one_square_ahead(piece_t *self, board_t *board, llist_t *moves);
bool try_push_lsquare(piece_t *self, board_t *board, llist_t *moves);
bool try_push_rsquare(piece_t *self, board_t *board, llist_t *moves);

#endif /* PAWN_INTERNALS_H */
