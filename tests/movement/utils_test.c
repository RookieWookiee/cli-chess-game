#include <cgreen/cgreen.h>
#include <cgreen/mocks.h>
#include <stdbool.h>
#include <stdio.h>

#include "include/piece.h"
#include "include/board.h"
#include "include/llist.h"
#include "include/movement_utils.h"

/* fakes */
bool position_equals(const void *a, const void *b) {}
bool contains(llist_t *head_ref, void * const obj, bool (*equals)(const void *, const void *)) {}
void destroy(llist_t **head_ref) {}
piece_t **get_square(board_t *self, uint8_t rank, uint8_t file) { return calloc(1, sizeof(piece_t*)); }

/* mocks */
void push(llist_t **head_ref, void *new_data, size_t data_size);
bool is_in_bounds(pos_t pos);
bool is_square_empty(board_t *self, uint8_t rank, uint8_t file);
bool is_enemy(piece_t *p1, piece_t *p2);

piece_t *piece;
board_t *board;

Describe(Utils);
BeforeEach(Utils)
{
    cgreen_mocks_are(loose_mocks);
    piece = malloc(sizeof(piece_t));
    board = calloc(1, sizeof(board_t));
}
AfterEach(Utils) {}

Ensure(Utils, add_moves_respects_bound_checks_in_all_directions)
{

    direction_t dirs[] = { NORTH_EAST, SOUTH_EAST, SOUTH_WEST, NORTH_WEST, NORTH, SOUTH, EAST, WEST };

    never_expect(is_square_empty);
    never_expect(is_enemy);
    never_expect(push);
    always_expect(is_in_bounds, will_return(false));

    for(int i = 0; i < sizeof(dirs)/sizeof(dirs[0]); i++) {
        add_moves_while_empty(board, piece, dirs[i], NULL);
    }
}

Ensure(Utils, add_moves_respects_empty_squares_checks)
{
    direction_t dirs[] = { NORTH_EAST, SOUTH_EAST, SOUTH_WEST, NORTH_WEST, NORTH, SOUTH, EAST, WEST };

    /* affirmative expectations */
    for(int i = 0; i < sizeof(dirs)/sizeof(dirs[0]); i++) {
        expect(is_in_bounds, will_return(true));
        expect(is_in_bounds, will_return(false));
        expect(is_square_empty, will_return(true));
        expect(push);

        add_moves_while_empty(board, piece, dirs[i], NULL);
    }

    /* negative expectations */
    never_expect(push);
    for(int i = 0; i < sizeof(dirs)/sizeof(dirs[0]); i++) {
        expect(is_in_bounds, will_return(true));
        expect(is_square_empty, will_return(false));

        add_moves_while_empty(board, piece, dirs[i], NULL);
    }
}

Ensure(Utils, add_moves_respect_enemy_checks)
{
    direction_t dirs[] = { NORTH_EAST, SOUTH_EAST, SOUTH_WEST, NORTH_WEST, NORTH, SOUTH, EAST, WEST };

    /* affirmative expectations */
    for(int i = 0; i < sizeof(dirs)/sizeof(dirs[0]); i++) {
        expect(is_in_bounds, will_return(true));
        expect(is_square_empty, will_return(false));
        expect(is_enemy, will_return(true));
        expect(push);

        add_moves_while_empty(board, piece, dirs[i], NULL);
    }

    /* negative expectations */
    never_expect(push);
    for(int i = 0; i < sizeof(dirs)/sizeof(dirs[0]); i++) {
        expect(is_in_bounds, will_return(true));
        expect(is_square_empty, will_return(false));
        expect(is_enemy, will_return(false));

        add_moves_while_empty(board, piece, dirs[i], NULL);
    }
}

Ensure(Utils, add_moves_pushes_correct_positions)
{
    direction_t dirs[] = { NORTH_EAST, SOUTH_EAST, SOUTH_WEST, NORTH_WEST, NORTH, SOUTH, EAST, WEST };
    pos_t offsets[] = {
        {UP, RIGHT}, {DOWN, RIGHT},
        {DOWN, LEFT}, {UP, LEFT},
        {UP, NONE}, {DOWN, NONE},
        {NONE, RIGHT}, {NONE, LEFT}
    };
    piece->rank = RANK_4; piece->file = FILE_D;

    for(int i = 0; i < sizeof(dirs)/sizeof(dirs[0]); i++) {
        expect(is_in_bounds, will_return(true));
        expect(is_square_empty, will_return(true));

        pos_t curr_offset = offsets[i];
        pos_t exp_position = {
            piece->rank + 1 * curr_offset.rank,
            piece->file + 1 * curr_offset.file
        };
        expect(push, when(new_data, is_equal_to_contents_of(&exp_position, sizeof(pos_t))));

        add_moves_while_empty(board, piece, dirs[i], NULL);
    }
}

void push(llist_t **head_ref, void *new_data, size_t data_size)
{
    mock(head_ref, new_data, data_size);
}

bool is_in_bounds(pos_t pos)
{
    return (bool) mock(&pos);
}

bool is_square_empty(board_t *self, uint8_t rank, uint8_t file)
{
    return (bool) mock(self, rank, file);
}

bool is_enemy(piece_t *p1, piece_t *p2)
{
    return (bool) mock(p1, p2);
}
