#include "board.h"
#include <stdio.h>

int main(void)
{
    board_t *board = make_board();
    print_board(board);
    printf("\nall is k\n");
}
