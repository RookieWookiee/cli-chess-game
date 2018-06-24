#include <stdlib.h>
#include <stdio.h>

#include "include/board.h"
#include "include/piece.h"
#include "include/position.h"

void set_square(board_t *self, pos_t pos, piece_t **piece);
static void print_header();
static void print_footer();

board_t *make_board()
{
    board_t *board = malloc(sizeof(*board));
    *board = (board_t) { NULL };
    board->ply = 1;

    for(int file = FILE_A; file <= FILE_H; file++) {
        set_square(board, (pos_t) {RANK_7, file}, make_piece(RANK_7, file, PAWN_W_ID));
        set_square(board, (pos_t) {RANK_2, file}, make_piece(RANK_2, file, PAWN_B_ID));
    }

    /* white rooks */
    set_square(board, (pos_t) {RANK_8, FILE_A}, make_piece(RANK_8, FILE_A, ROOK_W_ID));
    set_square(board, (pos_t) {RANK_8, FILE_H}, make_piece(RANK_8, FILE_H, ROOK_W_ID));
    /* black rooks */
    set_square(board, (pos_t) {RANK_1, FILE_A}, make_piece(RANK_1, FILE_A, ROOK_B_ID));
    set_square(board, (pos_t) {RANK_1, FILE_H}, make_piece(RANK_1, FILE_H, ROOK_B_ID));

    /* white knights */
    set_square(board, (pos_t) {RANK_8, FILE_B}, make_piece(RANK_8, FILE_B, KNIGHT_W_ID));
    set_square(board, (pos_t) {RANK_8, FILE_G}, make_piece(RANK_8, FILE_G, KNIGHT_W_ID));
    /* black knights */
    set_square(board, (pos_t) {RANK_1, FILE_B}, make_piece(RANK_1, FILE_B, KNIGHT_B_ID));
    set_square(board, (pos_t) {RANK_1, FILE_G}, make_piece(RANK_1, FILE_G, KNIGHT_B_ID));

    /* white bishops */
    set_square(board, (pos_t) {RANK_8, FILE_C}, make_piece(RANK_8, FILE_C, BISHOP_W_ID));
    set_square(board, (pos_t) {RANK_8, FILE_F}, make_piece(RANK_8, FILE_F, BISHOP_W_ID));
    /* black bishops */
    set_square(board, (pos_t) {RANK_1, FILE_C}, make_piece(RANK_1, FILE_C, BISHOP_B_ID));
    set_square(board, (pos_t) {RANK_1, FILE_F}, make_piece(RANK_1, FILE_F, BISHOP_B_ID));

    /* white queen */
    set_square(board, (pos_t) {RANK_8, FILE_D}, make_piece(RANK_8, FILE_D, QUEEN_W_ID));
    /* black queen */
    set_square(board, (pos_t) {RANK_1, FILE_D}, make_piece(RANK_1, FILE_D, QUEEN_B_ID));

    /* white king */
    set_square(board, (pos_t) {RANK_8, FILE_E}, make_piece(RANK_8, FILE_E, KING_W_ID));
    set_square(board, (pos_t) {RANK_1, FILE_E}, make_piece(RANK_1, FILE_E, KING_B_ID));

    return board;
}

void set_square(board_t *self, pos_t pos, piece_t **piece)
{
    self->squares[pos.rank][pos.file] = piece;
}

piece_t **get_square(board_t *self, uint8_t rank, uint8_t file)
{
    return self->squares[rank][file];
}

bool is_square_empty(board_t *self, uint8_t rank, uint8_t file)
{
    return get_square(self, rank, file) == NULL || *get_square(self, rank, file) == NULL;
}

void print_board(board_t *self)
{
    print_header();

    for(int rank = RANK_1; rank <= RANK_8; rank++) {
        printf("| %d ", NUM_ROWS - rank);
        for(int file = FILE_A; file <= FILE_H; file++) {
            piece_t **curr = get_square(self, rank, file);
            char *sym = get_sym(curr, false);
            printf("%s ", sym);
        }
        printf(" %d |\n", NUM_ROWS - rank);
    }

    print_footer();
}

void update_board(board_t *self, piece_t **piece, pos_t target_pos)
{
    set_square(self, (pos_t) {(*piece)->rank, (*piece)->file}, NULL);
    set_square(self, target_pos, piece);
}

static void print_header()
{
    printf(" ______________________\n"
           "|                      |\n"
           "|   a b c d e f g h    |\n"
           "|                      |\n");
}

static void print_footer()
{
    printf("|                      |\n"
           "|   a b c d e f g h    |\n"
           "|______________________|\n");
}
