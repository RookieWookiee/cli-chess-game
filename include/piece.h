#ifndef PIECE_H
#define PIECE_H

#include <inttypes.h>
#include <stdbool.h>

#include "include/position.h"

typedef struct node llist_t;
typedef struct board board_t;

/* 
 * keep in mind that the actual chess board is flipped 
 * compared to a two dimensional array
 * ranks grow from bottom to top */
typedef struct piece {
    /* rank is row (y), file is column (x) */
    uint8_t rank, file;
    uint8_t type_id;
    const struct piece_vtable_ *vtable;
} piece_t;

struct piece_vtable_ {
    int (*validate_move)(piece_t *self, pos_t target, board_t *board);
    llist_t *(*gen_moves)(piece_t *self, board_t *board);
};

piece_t **make_piece(uint8_t rank, uint8_t file, uint8_t type_id);
void kill_piece(piece_t **piece);
/* Returns the string representation of a piece */
char *get_sym(piece_t **piece, bool use_unicode); 
void move_piece(board_t *board, piece_t **piece, pos_t target_pos);
bool get_color(piece_t *piece);
bool is_enemy(piece_t *p1, piece_t *p2);

extern const struct piece_vtable_ PAWN[], BISHOP[], KNIGHT[], ROOK[], KING[], QUEEN[];

static inline int is_valid_move(piece_t *piece, pos_t target, board_t *board)
{
    return piece->vtable->validate_move(piece, target, board);
}

static inline llist_t *generate_moves(piece_t *piece, board_t *board)
{
    return piece->vtable->gen_moves(piece, board);
}

enum { /* type ids */
    EMPTY_ID,
    PAWN_W_ID, PAWN_B_ID,
    ROOK_W_ID, ROOK_B_ID,
    BISHOP_W_ID, BISHOP_B_ID,
    KNIGHT_W_ID, KNIGHT_B_ID,
    QUEEN_W_ID, QUEEN_B_ID,
    KING_W_ID, KING_B_ID,
};

enum { BLACK, WHITE };

#define EMPTY_ASCII      "."
#define PAWN_W_ASCII     "P"
#define PAWN_B_ASCII     "p"
#define ROOK_W_ASCII     "R"
#define ROOK_B_ASCII     "r"
#define BISHOP_W_ASCII   "B"
#define BISHOP_B_ASCII   "b"
#define KNIGHT_W_ASCII   "K"
#define KNIGHT_B_ASCII   "k"
#define QUEEN_W_ASCII    "Q"
#define QUEEN_B_ASCII    "q"
#define KING_W_ASCII     "K"
#define KING_B_ASCII     "k"

#define EMPTY_UNICODE    "."
#define PAWN_W_UNICODE   "♙"
#define PAWN_B_UNICODE   "♟"
#define ROOK_W_UNICODE   "♖"
#define ROOK_B_UNICODE   "♜"
#define BISHOP_W_UNICODE "♗"
#define BISHOP_B_UNICODE "♝"
#define KNIGHT_W_UNICODE "♘"
#define KNIGHT_B_UNICODE "♞"
#define QUEEN_W_UNICODE  "♕"
#define QUEEN_B_UNICODE  "♛"
#define KING_W_UNICODE   "♔"
#define KING_B_UNICODE   "♚"

#endif /* PIECE_H */
