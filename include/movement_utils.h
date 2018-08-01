#ifndef MOVEMENT_UTILS_H
#define MOVEMENT_UTILS_H

#include "include/board.h"

int standard_validation(piece_t *self, pos_t target, board_t *board);
void add_moves_while_empty(board_t *board, piece_t *piece, direction_t direction, llist_t **moves);

#endif
