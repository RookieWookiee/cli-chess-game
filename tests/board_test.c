#include <cgreen/cgreen.h>
#include <stdbool.h>
#include <stdio.h>

#include "include/piece.h"
#include "include/board.h"

Describe(Board);
BeforeEach(Board) {}
AfterEach(Board) {}

/* fakes to keep the linker happy */
piece_t **make_piece(uint8_t rank, uint8_t file, uint8_t type_id) { return NULL; }
char *get_sym(piece_t **piece, bool use_unicode) { return NULL; }

Ensure(Board, empty_board_return_an_empty_board)
{
    board_t *board = make_empty_board();

    board_t *expected = calloc(1, sizeof(board_t));
    expected->ply = 1;

    assert_that(board, is_equal_to_contents_of(expected, sizeof(board_t)));
}

Ensure(Board, set_square_works_correctly)
{
    board_t *board = calloc(1, sizeof(board_t));
    piece_t **test_piece = malloc(sizeof(piece_t*));
    pos_t pos = { RANK_1, FILE_A };

    set_square(board, pos, test_piece);

    assert_that(board->squares[pos.rank][pos.file], is_equal_to_hex(test_piece));
}

Ensure(Board, get_square_works_correctly)
{
    board_t *board = calloc(1, sizeof(board_t));
    piece_t **test_piece = malloc(sizeof(piece_t*));
    pos_t pos = { RANK_1, FILE_A };

    board->squares[pos.rank][pos.file] = test_piece;

    assert_that(get_square(board, pos.rank, pos.file), is_equal_to_hex(test_piece));
}

Ensure(Board, update_board_updates_the_squares)
{
    board_t *board = calloc(1, sizeof(board_t));
    piece_t *test_piece = malloc(sizeof(piece_t*));
    *test_piece = (piece_t) {};
    pos_t initial_pos = { RANK_1, FILE_A };
    pos_t target_pos = { RANK_1, FILE_B };

    test_piece->rank = initial_pos.rank;
    test_piece->file = initial_pos.file;

    board->squares[initial_pos.rank][initial_pos.file] = &test_piece;

    update_board(board, &test_piece, target_pos);

    assert_that(board->squares[initial_pos.rank][initial_pos.file], is_null);
    assert_that(board->squares[target_pos.rank][target_pos.file], is_equal_to_hex(&test_piece));
}

Ensure(Board, is_empty_square_correctness)
{
    board_t *board = calloc(1, sizeof(board_t));
    piece_t *test_piece1 = NULL;
    piece_t *test_piece2 = calloc(1, sizeof(piece_t));

    board->squares[RANK_1][FILE_B] = &test_piece1;
    board->squares[RANK_1][FILE_C] = &test_piece2;

    assert_that(is_square_empty(board, RANK_1, FILE_A), is_true);
    assert_that(is_square_empty(board, RANK_1, FILE_B), is_true);
    assert_that(is_square_empty(board, RANK_1, FILE_C), is_false);
}

Ensure(Board, new_test)
{
    assert_true(true);
}
