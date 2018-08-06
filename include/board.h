#ifndef BOARD_H
#define BOARD_H

#include <inttypes.h>
#include "position.h"

#define NUM_ROWS 8
#define NUM_COLS 8

#define MAX_DIRECTION 7

enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H };
enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8 };
typedef enum { NORTH_EAST, SOUTH_EAST, SOUTH_WEST, NORTH_WEST, NORTH, SOUTH, EAST, WEST = MAX_DIRECTION } direction_t;
enum { DOWN = 1, UP = -1, LEFT = -1, RIGHT = 1, NONE = 0 };

/* forward declaration */
typedef struct piece piece_t;
typedef struct node llist_t;

typedef struct board {
    piece_t **squares[8][8];

    pos_t *pawns[2][8];
    pos_t *rooks[2][10];
    pos_t *bishops[2][10];
    pos_t *knights[2][10];
    pos_t *queens[2][10];
    pos_t *kings[2];

    int ply;
} board_t;


board_t *make_board();
void set_square(board_t *self, pos_t pos, piece_t **piece);
piece_t **get_square(board_t *self, uint8_t rank, uint8_t file);
void print_board(board_t *self);
void update_board(board_t *self, piece_t **piece, pos_t target_pos);
bool is_square_empty(board_t *self, uint8_t rank, uint8_t file);
bool is_in_bounds(pos_t pos);
board_t *make_empty_board();
llist_t *get_piece_attackers(board_t *board, pos_t from_pos, bool piece_color);

#endif /* BOARD_H */
