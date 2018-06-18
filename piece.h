#ifndef PIECE_H
#define PIECE_H

#include <inttypes.h>

enum { /* type ids */
    EMPTY_ID,
    PAWN_W_ID, PAWN_B_ID,
    ROOK_W_ID, ROOK_B_ID,
    BISHOP_W_ID, BISHOP_B_ID,
    KNIGHT_W_ID, KNIGHT_B_ID,
    QUEEN_W_ID, QUEEN_B_ID,
    KING_W_ID, KING_B_ID,
};

typedef struct piece {
    uint8_t rank, file;
    uint8_t type_id;
} piece_t;

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

piece_t *make_piece(uint8_t rank, uint8_t file, uint8_t type_id);

#endif /* PIECE_H */
