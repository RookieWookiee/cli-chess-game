#include "include/board.h"
#include "include/piece.h"
#include "include/player.h"
#include "include/llist.h"

#include <stdio.h>

int main(void)
{
    player_t *players[2];

    board_t *board = make_board();
    players[WHITE] = make_player(WHITE, board);
    players[BLACK] = make_player(BLACK, board);

    piece_t **pawn = players[WHITE]->pieces[PAWN_W_ID][0];
    piece_t **pawn1 = players[WHITE]->pieces[PAWN_W_ID][3];

    pos_t target_pawn1 = { (*pawn)->rank-1, (*pawn)->file };
    move_piece(board, pawn1, target_pawn1);

    print_board(board);

    piece_t *bishop = *players[WHITE]->pieces[BISHOP_W_ID][0];

    printf("list start: \n");
    llist_t *bishop_moves = generate_moves(bishop, board);
    print_list(bishop_moves, position_print);
    printf("\n");
    
    pos_t target = { RANK_6, FILE_E };
    printf(is_legal_move(bishop, target, board) ? "true" : "false");

    printf("\nAll is k\n");
}

void start_repl(player_t *white, player_t *black, board_t* board)
{
    //while(true) {
    //    player_t *attacker = players[board->ply % 2];
    //    player_t *attacked = players[(board->ply+1) % 2];
    //}

}
