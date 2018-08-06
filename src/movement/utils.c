#include "include/piece.h"
#include "include/position.h"
#include "include/board.h"
#include "include/llist.h"

#include <assert.h>
#include <stdlib.h>

int standard_validation(piece_t *self, pos_t target, board_t *board)
{
    llist_t *legal_moves = generate_moves(self, board);
    int is_valid = contains(legal_moves, &target, position_equals);

    destroy(&legal_moves);
    assert(!legal_moves);

    return is_valid;
}

void add_moves_while_empty(board_t *board, piece_t *piece, direction_t direction, llist_t **moves)
{
    int dx, dy;
    switch(direction) {
        case NORTH_EAST: dy = UP;   dx = RIGHT; break;
        case SOUTH_EAST: dy = DOWN; dx = RIGHT; break;
        case SOUTH_WEST: dy = DOWN; dx = LEFT;  break;
        case NORTH_WEST: dy = UP;   dx = LEFT;  break;
        case NORTH     : dy = UP;   dx = NONE;  break;
        case SOUTH     : dy = DOWN; dx = NONE;  break;
        case EAST      : dy = NONE; dx = RIGHT; break;
        case WEST      : dy = NONE; dx = LEFT;  break;
    }

    pos_t curr_pos = { piece->rank + 1 * dy, piece->file + 1 * dx };

    while(is_in_bounds(curr_pos)) {
        if(is_square_empty(board, curr_pos.rank, curr_pos.file)) {
            push(moves, &curr_pos, sizeof(pos_t));
        } else {
            if(is_enemy(piece, *get_square(board, curr_pos.rank, curr_pos.file)))
                push(moves, &curr_pos, sizeof(pos_t));
            break;
        }

        curr_pos.rank += 1 * dy; curr_pos.file += 1 * dx;
    }
}

void get_attackers_on_straights(board_t *board, pos_t from_pos, bool piece_color, llist_t **attackers)
{
    direction_t straights[] = { NORTH, SOUTH, EAST, WEST };
    llist_t *moves = NULL;
    piece_t **dummy_piece = make_piece(from_pos.rank, from_pos.file, PAWN_W_ID);

    for(size_t i = 0; i < sizeof(straights) / sizeof(*straights); i++) {
        add_moves_while_empty(board, *dummy_piece, straights[i], &moves);
        pos_t *ret = popleft(&moves);
        pos_t last = *ret;
        free(ret);

        if(!is_square_empty(board, last.rank, last.file)) { //It's an enemy, see add_moves_while_empty declaration if that doesn't make sense
            piece_t **potential_attacker = get_square(board, last.rank, last.file);

            switch((*potential_attacker)->type_id) {
                case ROOK_W_ID:     case ROOK_B_ID:
                case QUEEN_W_ID:    case QUEEN_B_ID: {
                    push(attackers, &last, sizeof(pos_t));
                    break;
                }

                case KING_W_ID:     case KING_B_ID: {
                    int delta_y = abs(last.rank - from_pos.rank);
                    int delta_x = abs(last.file - from_pos.file);

                    if(delta_x == 1 || delta_y == 1)
                        push(attackers, &last, sizeof(pos_t));
                    break;
                }
                default: break;
            }
        }

        destroy(&moves);
    }
}

void get_attackers_on_diagonals(board_t *board, pos_t from_pos, bool piece_color, llist_t **attackers)
{
    direction_t straights[] = { NORTH_EAST, SOUTH_EAST, SOUTH_WEST, NORTH_WEST };
    llist_t *moves = NULL;
    piece_t **dummy_piece = make_piece(from_pos.rank, from_pos.file, PAWN_W_ID);

    for(size_t i = 0; i < sizeof(straights) / sizeof(*straights); i++) {
        add_moves_while_empty(board, *dummy_piece, straights[i], &moves);
        pos_t *ret = popleft(&moves);
        pos_t last = *ret;
        free(ret);

        if(!is_square_empty(board, last.rank, last.file)) { //It's an enemy, see add_moves_while_empty declaration if that doesn't make sense
            piece_t **potential_attacker = get_square(board, last.rank, last.file);

            switch((*potential_attacker)->type_id) {
                case QUEEN_W_ID:    case QUEEN_B_ID:
                case BISHOP_W_ID:   case BISHOP_B_ID: {
                    push(attackers, get_square(board, last.rank, last.file), sizeof(get_square(board, last.rank, last.file)));
                    break;
                }

                case KING_W_ID:     case KING_B_ID: {
                    int delta_y = abs(last.rank - from_pos.rank);
                    int delta_x = abs(last.file - from_pos.file);
                    if(delta_x <= 1 && delta_y <= 1)
                        push(attackers, get_square(board, last.rank, last.file), sizeof(get_square(board, last.rank, last.file)));
                    break;
                }
                case PAWN_W_ID:     case PAWN_B_ID: {
                    pos_t left_pawn = { from_pos.rank, from_pos.file + 1 * LEFT};
                    left_pawn.rank += 1 * piece_color == WHITE ? UP : DOWN;

                    pos_t right_pawn = { from_pos.rank, from_pos.file + 1 * RIGHT};
                    right_pawn.rank += 1 * piece_color == WHITE ? UP : DOWN;

                    if(last.rank == left_pawn.rank && last.file == left_pawn.file)
                        push(attackers, get_square(board, last.rank, last.file), sizeof(get_square(board, last.rank, last.file)));
                    if(last.rank == right_pawn.rank && last.file == right_pawn.file)
                        push(attackers, get_square(board, last.rank, last.file), sizeof(get_square(board, last.rank, last.file)));

                    break;
                }
                default: break;
            }
        }

        destroy(&moves);
    }
}

void get_attackers_knight_positions(board_t *borad, pos_t from_pos, bool piece_color, llist_t **attacker)
{

}
