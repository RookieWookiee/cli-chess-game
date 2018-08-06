#ifndef MOVEMENT_UTILS_H
#define MOVEMENT_UTILS_H

#include "include/board.h"

/* Uses generate_moves for the particular piece and returns the result
 * of a contains call on the generated moves as *target* as a target */
int standard_validation(piece_t *self, pos_t target, board_t *board);

/* Will push pos_t * pointers in the particular direction while they are in bounds
 * or while a chess piece is encounterd, when a piece is encountered there are two 
 * possible outcomes: if said piece is friendly it's position will not be added
 * if it's hostile - it will be added. The current implementation starts from 
 * *piece*'s position and traverses the board outwards. */
void add_moves_while_empty(board_t *board, piece_t *piece, direction_t direction, llist_t **moves);

void get_attackers_on_straights(board_t *board, pos_t from_pos, bool piece_color, llist_t **attackers);
void get_attackers_on_diagonals(board_t *board, pos_t from_pos, bool piece_color, llist_t **attackers);
void get_attackers_knight_positions(board_t *borad, pos_t from_pos, bool piece_color, llist_t **attacker);

#endif
