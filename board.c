#include "board.h"
#include "piece.h"

#include <stdlib.h>
#include <stdio.h>

/* print_matrix[unicode_or_nah][type_id]*/
static char* print_matrix[2][13] = {
    /* unicode == true */
    {
        EMPTY_UNICODE,
        PAWN_W_UNICODE,     PAWN_B_UNICODE,
        ROOK_W_UNICODE,     ROOK_B_UNICODE,
        BISHOP_W_UNICODE,   BISHOP_B_UNICODE,
        KNIGHT_W_UNICODE,   KNIGHT_B_UNICODE,
        QUEEN_W_UNICODE,    QUEEN_B_UNICODE,
        KING_W_UNICODE,     KING_B_UNICODE
    },
    /* unicode == false */
    {
        EMPTY_ASCII,
        PAWN_W_ASCII,       PAWN_B_ASCII,
        ROOK_W_ASCII,       ROOK_B_ASCII,
        BISHOP_W_ASCII,     BISHOP_B_ASCII,
        KNIGHT_W_ASCII,     KNIGHT_B_ASCII,
        QUEEN_W_ASCII,      QUEEN_B_ASCII,
        KING_W_ASCII,       KING_B_ASCII
    }
};

void set_square(board_t *self, uint8_t rank, uint8_t file, uint8_t type_id);

board_t *make_board()
{
    board_t *board = malloc(sizeof(*board));
    *board = (board_t) { NULL };

    for(int file = FILE_A; file <= FILE_H; file++) {
        set_square(board, RANK_7, file, PAWN_W_ID);
        set_square(board, RANK_2, file, PAWN_B_ID);
    }

    /* white rooks */
    set_square(board, RANK_8, FILE_A, ROOK_W_ID);
    set_square(board, RANK_8, FILE_H, ROOK_W_ID);
    /* black rooks */
    set_square(board, RANK_1, FILE_A, ROOK_B_ID);
    set_square(board, RANK_1, FILE_H, ROOK_B_ID);

    /* white knights */
    set_square(board, RANK_8, FILE_B, KNIGHT_W_ID);
    set_square(board, RANK_8, FILE_G, KNIGHT_W_ID);
    /* black knights */
    set_square(board, RANK_1, FILE_B, KNIGHT_B_ID);
    set_square(board, RANK_1, FILE_G, KNIGHT_B_ID);

    /* white bishops */
    set_square(board, RANK_8, FILE_C, BISHOP_W_ID);
    set_square(board, RANK_8, FILE_F, BISHOP_W_ID);
    /* black bishops */
    set_square(board, RANK_1, FILE_C, BISHOP_B_ID);
    set_square(board, RANK_1, FILE_F, BISHOP_B_ID);

    /* white queen */
    set_square(board, RANK_8, FILE_D, QUEEN_W_ID);
    /* black queen */
    set_square(board, RANK_1, FILE_D, QUEEN_B_ID);

    /* white king */
    set_square(board, RANK_8, FILE_E, KING_W_ID);
    set_square(board, RANK_1, FILE_E, KING_B_ID);

    return board;
}

void set_square(board_t *self, uint8_t rank, uint8_t file, uint8_t type_id)
{
    self->squares[rank][file] = make_piece(rank, file, type_id);
}

piece_t *get_square(board_t *self, uint8_t rank, uint8_t file)
{
    return self->squares[rank][file];
}

void print_board(board_t *self)
{
    for(int rank = RANK_1; rank <= RANK_8; rank++) {
        for(int file = FILE_A; file <= FILE_H; file++) {
            piece_t *curr = get_square(self, rank, file);
            char *sym = curr ?
                print_matrix[0][curr->type_id] :
                print_matrix[0][EMPTY_ID];

            printf("%s ", sym);
        }

        printf("\n");
    }
}
