#include <cgreen/cgreen.h>
#include <cgreen/mocks.h>
#include <stdbool.h>
#include <stdio.h>

#include "include/piece.h"
#include "include/board.h"

Describe(Piece);
BeforeEach(Piece) {}
AfterEach(Piece) {}

/* to keep the linker happy */
static int fake_validate(piece_t *self, pos_t target, board_t *board) { return 0; }
static llist_t *fake_gen_moves(piece_t *self, board_t *board) { return NULL; }
void add_moves_while_empty(board_t * b, piece_t * p, direction_t d, llist_t **l) {}
piece_t **get_square(board_t *s, uint8_t r, uint8_t f) { return NULL; }
bool is_square_empty(board_t *s, uint8_t r, uint8_t f) { return false; }

const struct piece_vtable_ PAWN[] = { { fake_validate, fake_gen_moves } };
const struct piece_vtable_ ROOK[] = { { fake_validate, fake_gen_moves } };
const struct piece_vtable_ BISHOP[] = { { fake_validate, fake_gen_moves } };
const struct piece_vtable_ QUEEN[] = { { fake_validate, fake_gen_moves } };
const struct piece_vtable_ KNIGHT[] = { { fake_validate, fake_gen_moves } };
const struct piece_vtable_ KING[] = { { fake_validate, fake_gen_moves } };

void update_board(board_t *self, piece_t **piece, pos_t target_pos) 
{
    mock(self, piece, &target_pos);
}

Ensure(Piece, make_piece_initializes_properly)
{
    int expected_rank = RANK_1,
        expected_file = FILE_H,
        expected_type = PAWN_W_ID;

    piece_t **actual = make_piece(expected_rank, expected_file, expected_type);

    assert_that(actual, is_not_null);
    piece_t *piece = *actual;

    assert_that(piece, is_not_null);
    assert_that(piece->rank, is_equal_to(expected_rank));
    assert_that(piece->file, is_equal_to(expected_file));
    assert_that(piece->type_id, is_equal_to(expected_type));
    assert_that(piece->vtable, is_equal_to_hex(PAWN));
}

Ensure(Piece, get_color_correctness) 
{
    uint8_t ids[] = {
        PAWN_W_ID, PAWN_B_ID, BISHOP_W_ID, BISHOP_B_ID, KING_W_ID, KING_B_ID,
        KNIGHT_W_ID, KNIGHT_B_ID, ROOK_W_ID, ROOK_B_ID, QUEEN_W_ID, QUEEN_B_ID
    };

    piece_t base_piece;

    for(size_t i = 0; i < sizeof(ids)/sizeof(ids[0]); i++) {
        base_piece.type_id = ids[i];
        bool expected_color = i % 2 == 0 ? WHITE : BLACK;

        assert_that(get_color(&base_piece), is_equal_to(expected_color));
    }
}

Ensure(Piece, is_enemy_correctness) 
{
    uint8_t ids[][3] = { {PAWN_W_ID, PAWN_W_ID, false}, {PAWN_B_ID, PAWN_W_ID, true}, {PAWN_W_ID, PAWN_B_ID, true} };

    piece_t p1, p2;

    for(size_t i = 0; i < sizeof(ids)/sizeof(ids[0]); i++) {
        p1.type_id = ids[i][0];
        p2.type_id = ids[i][1];
        bool expected = ids[i][2];

        assert_that(is_enemy(&p1, &p2), is_equal_to(expected));
    }
}

Ensure(Piece, get_sym_returns_correct_representations_non_unicode) 
{
    uint8_t ids[] = {
        PAWN_W_ID, PAWN_B_ID, BISHOP_W_ID, BISHOP_B_ID, KING_W_ID, KING_B_ID,
        KNIGHT_W_ID, KNIGHT_B_ID, ROOK_W_ID, ROOK_B_ID, QUEEN_W_ID, QUEEN_B_ID
    };

    char *expected[] = {
        PAWN_W_ASCII, PAWN_B_ASCII, BISHOP_W_ASCII, BISHOP_B_ASCII, KING_W_ASCII, KING_B_ASCII,
        KNIGHT_W_ASCII, KNIGHT_B_ASCII, ROOK_W_ASCII, ROOK_B_ASCII, QUEEN_W_ASCII, QUEEN_B_ASCII
    };

    piece_t *test_piece = malloc(sizeof(piece_t));
    *test_piece = (piece_t){ };
    bool use_unicode = false;

    for(size_t i = 0; i < sizeof(ids)/sizeof(ids[0]); i++) {
        test_piece->type_id = ids[i];
        char *expected_sym = expected[i];

        assert_that(get_sym(&test_piece, use_unicode), is_equal_to_string(expected_sym));
    }

    assert_that(get_sym(NULL, use_unicode), is_equal_to_string(EMPTY_ASCII));
}

Ensure(Piece, get_sym_returns_correct_representation_unicode)
{
    uint8_t ids[] = {
        PAWN_W_ID, PAWN_B_ID, BISHOP_W_ID, BISHOP_B_ID, KING_W_ID, KING_B_ID,
        KNIGHT_W_ID, KNIGHT_B_ID, ROOK_W_ID, ROOK_B_ID, QUEEN_W_ID, QUEEN_B_ID
    };

    char *expected[] = {
        PAWN_W_UNICODE, PAWN_B_UNICODE, BISHOP_W_UNICODE, BISHOP_B_UNICODE, KING_W_UNICODE, KING_B_UNICODE,
        KNIGHT_W_UNICODE, KNIGHT_B_UNICODE, ROOK_W_UNICODE, ROOK_B_UNICODE, QUEEN_W_UNICODE, QUEEN_B_UNICODE
    };

    piece_t *test_piece = malloc(sizeof(piece_t));
    *test_piece = (piece_t){ };
    bool use_unicode = true;

    for(size_t i = 0; i < sizeof(ids)/sizeof(ids[0]); i++) {
        test_piece->type_id = ids[i];
        char *expected_sym = expected[i];

        assert_that(get_sym(&test_piece, use_unicode), is_equal_to_string(expected_sym));
    }

    assert_that(get_sym(NULL, use_unicode), is_equal_to_string(EMPTY_UNICODE));
}

Ensure(Piece, kill_piece_deals_with_dangling_pointers)
{
    piece_t *piece = malloc(sizeof(piece_t));
    *piece = (piece_t) { 0 };

    assert_that(piece, is_non_null);
    kill_piece(&piece);
    assert_that(piece, is_null);
}

Ensure(Piece, move_piece_changes_the_rank_and_the_file_of_the_piece_and_updates_the_board)
{
    piece_t *test_piece = malloc(sizeof(piece_t));
    board_t *test_board = NULL;
    pos_t *target = malloc(sizeof(pos_t));
    target->rank = RANK_8, target->file = FILE_H;

    expect(update_board,
            when(self, is_null),
            when(&target_pos, is_equal_to_contents_of(target, sizeof(pos_t))),
            when(piece, is_non_null));

    move_piece(test_board, &test_piece, *target);
    assert_that(test_piece->rank, is_equal_to(target->rank));
    assert_that(test_piece->file, is_equal_to(target->file));
}

Ensure(Piece, on_same_diagonal_anti_diagonals_returns_true)
{
    assert_that(on_same_diagonal((pos_t) {0, 0}, (pos_t) {7, 7}));
    assert_that(on_same_diagonal((pos_t) {0, 6}, (pos_t) {1, 7}));
    assert_that(on_same_diagonal((pos_t) {6, 0}, (pos_t) {7, 1}));
    assert_that(on_same_diagonal((pos_t) {1, 0}, (pos_t) {7, 6}));
}

Ensure(Piece, on_same_diagonal_diagonals_returns_true)
{
    assert_that(on_same_diagonal((pos_t) {0, 7}, (pos_t) {7, 0}));
    assert_that(on_same_diagonal((pos_t) {6, 7}, (pos_t) {7, 6}));
    assert_that(on_same_diagonal((pos_t) {0, 1}, (pos_t) {1, 0}));
    assert_that(on_same_diagonal((pos_t) {0, 6}, (pos_t) {6, 0}));
}

Ensure(Piece, diagonals_returns_false)
{
    assert_that(on_same_diagonal((pos_t) {0, 0}, (pos_t) {1, 0}), is_false);
    assert_that(on_same_diagonal((pos_t) {7, 7}, (pos_t) {0, 7}), is_false);
    assert_that(on_same_diagonal((pos_t) {3, 0}, (pos_t) {3, 7}), is_false);
    assert_that(on_same_diagonal((pos_t) {7, 7}, (pos_t) {5, 6}), is_false);
}
