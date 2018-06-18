#ifndef BOARD_H
#define BOARD_H

#include <inttypes.h>

#define NUM_ROWS 8
#define NUM_COLS 8

enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H };
enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8 };

/* forward declaration */
typedef struct piece piece_t;

typedef struct board {
    piece_t *squares[8][8];
} board_t;


board_t *make_board();
void set_square(board_t *self, uint8_t rank, uint8_t file, uint8_t type_id);
piece_t *get_square(board_t *self, uint8_t rank, uint8_t file);
void print_board(board_t *self);

#endif /* BOARD_H */
