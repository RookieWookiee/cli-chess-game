#include <stdlib.h>
#include <stdio.h>

#include "include/player.h"
#include "include/board.h"
#include "include/piece.h"

#define get_piece_id(piece, color)\
    color == WHITE ? piece##_W_ID : piece##_B_ID

player_t* make_player(bool color, board_t *board)
{
    player_t *player = calloc(1, sizeof(player_t));
    player->p_color = color; 

    int pawn_id  = get_piece_id(PAWN, color);
    int bishop_id  = get_piece_id(BISHOP, color);
    int rook_id = get_piece_id(ROOK, color);
    int knight_id = get_piece_id(KNIGHT, color);
    int queen_id = get_piece_id(QUEEN, color);
    int kind_id = get_piece_id(KING, color);

    player->num_pieces[pawn_id]   = 0;
    player->num_pieces[bishop_id] = 0;
    player->num_pieces[rook_id]   = 0;
    player->num_pieces[knight_id] = 0;
    player->num_pieces[queen_id]  = 0;
    player->num_pieces[kind_id]   = 0;

    for(int file = FILE_A; file <= FILE_H; file++) {
        int rank = color == WHITE ? RANK_7 : RANK_2;

        piece_t **piece = get_square(board, rank, file);
        if(piece) {
            uint8_t *count_pawns = &(player->num_pieces[pawn_id]);
            player->pieces[get_piece_id(PAWN, color)][*count_pawns] = piece;
            (*count_pawns)++;
        }

        rank = color == WHITE ? RANK_8 : RANK_1;
        piece = get_square(board, rank, file);
        if(*piece) {
            uint8_t *count_piece = &(player->num_pieces[(*piece)->type_id]);
            player->pieces[(*piece)->type_id][*count_piece] = piece;
            (*count_piece)++;
        }
    }

    return player;
}

piece_t *get_king(player_t *self)
{
    int king_id = self->p_color == WHITE ? KING_W_ID : KING_B_ID;

    return *self->pieces[king_id][0];
}
