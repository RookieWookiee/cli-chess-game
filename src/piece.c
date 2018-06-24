#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "include/piece.h"
#include "include/board.h"

/* print_matrix[unicode_or_nah][type_id]*/
/* lookup for printing piece symbols in print_board() */
static char* print_matrix[2][13] = {
    /* unicode == false */
    {
        EMPTY_ASCII,
        PAWN_W_ASCII,       PAWN_B_ASCII,
        ROOK_W_ASCII,       ROOK_B_ASCII,
        BISHOP_W_ASCII,     BISHOP_B_ASCII,
        KNIGHT_W_ASCII,     KNIGHT_B_ASCII,
        QUEEN_W_ASCII,      QUEEN_B_ASCII,
        KING_W_ASCII,       KING_B_ASCII
    },
    /* unicode == true */
    {
        EMPTY_UNICODE,
        PAWN_W_UNICODE,     PAWN_B_UNICODE,
        ROOK_W_UNICODE,     ROOK_B_UNICODE,
        BISHOP_W_UNICODE,   BISHOP_B_UNICODE,
        KNIGHT_W_UNICODE,   KNIGHT_B_UNICODE,
        QUEEN_W_UNICODE,    QUEEN_B_UNICODE,
        KING_W_UNICODE,     KING_B_UNICODE
    }
};

piece_t **make_piece(uint8_t rank, uint8_t file, uint8_t type_id)
{
    piece_t **piece = malloc(sizeof(piece_t*));
    *piece = malloc(sizeof(piece_t));

    (*piece)->rank = rank;
    (*piece)->file = file;
    (*piece)->type_id = type_id;

    switch(type_id) {
        case PAWN_W_ID:     case PAWN_B_ID:     (*piece)->vtable = PAWN;    break;
        case ROOK_W_ID:     case ROOK_B_ID:     (*piece)->vtable = ROOK;    break;
        case BISHOP_W_ID:   case BISHOP_B_ID:   (*piece)->vtable = BISHOP;  break;
        case QUEEN_W_ID:    case QUEEN_B_ID:    (*piece)->vtable = QUEEN;   break;
        case KNIGHT_W_ID:   case KNIGHT_B_ID:   (*piece)->vtable = KNIGHT;  break;
        case KING_W_ID:     case KING_B_ID:     (*piece)->vtable = KNIGHT;  break;
    }

    return piece;
}

bool get_color(piece_t *piece)
{
    return piece->type_id % 2;
}

bool is_enemy(piece_t *p1, piece_t *p2)
{
    return get_color(p1) != get_color(p2);
}

char *get_sym(piece_t **piece, bool use_unicode)
{
    if(piece && *piece)
        return print_matrix[use_unicode][(*piece)->type_id];
    return print_matrix[use_unicode][EMPTY_ID];
}

void kill_piece(piece_t **piece)
{
    free(*piece);
    *piece = NULL;
}

void move_piece(board_t *board, piece_t **piece, pos_t target_pos)
{
    if (!(piece && *piece))
        return;

    assert(target_pos.rank <= RANK_8 && target_pos.file <= FILE_H);

    update_board(board, piece, target_pos);
    (*piece)->rank = target_pos.rank;
    (*piece)->file = target_pos.file;
}
