#include "include/board.h"
#include "include/piece.h"
#include "include/player.h"
#include "include/llist.h"
#include "include/movement_utils.h"

#include <stdio.h>

int main(void)
{
    //player_t *players[2];

    board_t *board = make_empty_board();
    //players[WHITE] = make_player(WHITE, board);
    //players[BLACK] = make_player(BLACK, board);
    
    pos_t test_pos =  {RANK_4, FILE_D};

    pos_t enemy_pos = {test_pos.rank, test_pos.file - 1};
    pos_t enemy_pos2 = {test_pos.rank, test_pos.file + 1};
    pos_t enemy_pos3 = {test_pos.rank + 1, test_pos.file};
    pos_t enemy_pos4 = {test_pos.rank - 1, test_pos.file};


    piece_t *test_piece = *make_piece(test_pos.rank, test_pos.file, PAWN_W_ID);
    piece_t *enemy = *make_piece(enemy_pos.rank, enemy_pos.file, KING_B_ID);
    piece_t *enemy2 = *make_piece(enemy_pos2.rank, enemy_pos2.file, KING_B_ID);
    piece_t *enemy3 = *make_piece(enemy_pos3.rank, enemy_pos3.file, KING_B_ID);
    piece_t *enemy4 = *make_piece(enemy_pos4.rank, enemy_pos4.file, KING_B_ID);

    set_square(board, test_pos, &test_piece);
    set_square(board, enemy_pos, &enemy);
    set_square(board, enemy_pos2, &enemy2);
    set_square(board, enemy_pos3, &enemy3);
    set_square(board, enemy_pos4, &enemy4);

    print_board(board);

    printf("list start: \n");
    llist_t *enemies = NULL;
    get_attackers_on_straights(board, test_pos, WHITE, &enemies);
    print_list(enemies, position_print);
    printf("\n");
    
    //pos_t target = { RANK_6, FILE_E };
    //printf(is_legal_move(bishop, target, board) ? "true" : "false");

    printf("\nAll is k\n");
}

void start_repl(player_t *white, player_t *black, board_t* board)
{
    //while(true) {
    //    player_t *attacker = players[board->ply % 2];
    //    player_t *attacked = players[(board->ply+1) % 2];
    //}

}
