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
    player->color = color; 

    int p_id  = get_piece_id(PAWN, color);
    int b_id  = get_piece_id(BISHOP, color);
    int r_id = get_piece_id(ROOK, color);
    int n_id = get_piece_id(KNIGHT, color);
    int q_id = get_piece_id(QUEEN, color);
    int k_id = get_piece_id(KING, color);

    uint8_t *num_pieces = player->num_pieces;

    num_pieces[p_id] = num_pieces[b_id] = num_pieces[r_id] = 0;
    num_pieces[n_id] = num_pieces[q_id] = num_pieces[k_id] = 0;

    for(int file = FILE_A; file <= FILE_H; file++) {
        int rank = color == WHITE ? RANK_7 : RANK_2;

        piece_t **piece = get_square(board, rank, file);
        if(piece) {
            uint8_t *count_pawns = &(player->num_pieces[p_id]);
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
    int king_id = self->color == WHITE ? KING_W_ID : KING_B_ID;

    return *self->pieces[king_id][0];
}
