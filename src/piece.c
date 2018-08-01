#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "include/piece.h"
#include "include/board.h"
#include "include/llist.h"
#include "include/movement_utils.h"


static void get_attackers_on_straights(board_t *board, pos_t from_pos, bool piece_color, llist_t **attackers);
static void get_attackers_on_diagonals(board_t *board, pos_t from_pos, bool piece_color, llist_t **attackers);

/* Usage: print_matrix[unicode_or_nah][type_id]*/
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
    (*piece)->vtable = get_vtable(type_id);

    return piece;
}

const struct piece_vtable_ *get_vtable(uint8_t type_id)
{
    switch(type_id) {
        case PAWN_W_ID:     case PAWN_B_ID:     return PAWN;    break;
        case ROOK_W_ID:     case ROOK_B_ID:     return ROOK;    break;
        case BISHOP_W_ID:   case BISHOP_B_ID:   return BISHOP;  break;
        case QUEEN_W_ID:    case QUEEN_B_ID:    return QUEEN;   break;
        case KNIGHT_W_ID:   case KNIGHT_B_ID:   return KNIGHT;  break;
        case KING_W_ID:     case KING_B_ID:     return KING;  break;
        default: return NULL; break;
    }
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

bool on_same_diagonal(pos_t p1, pos_t p2)
{
    int target_diagonal = (int)p1.rank - p1.file;
    int piece_diagonal = (int)p2.rank - p2.file;

    int target_anti_diagonal = (int)p1.rank + p1.file;
    int piece_anti_diagonal = (int)p2.rank + p2.file;

    return target_diagonal == piece_diagonal || target_anti_diagonal == piece_anti_diagonal;
}

llist_t *get_piece_attackers(board_t *board, pos_t from_pos, bool piece_color)
{
    llist_t *attackers = NULL;

    get_attackers_on_straights(board, from_pos, piece_color, &attackers);

    return attackers;
}

static void get_attackers_on_straights(board_t *board, pos_t from_pos, bool piece_color, llist_t **attackers)
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
                    push(attackers, get_square(board, last.rank, last.file), sizeof(get_square(board, last.rank, last.file)));
                    break;
                }

                case KING_W_ID:     case KING_B_ID: {
                    int delta_y = abs(last.rank - from_pos.rank);
                    int delta_x = abs(last.file - from_pos.file);

                    if(delta_x == 1 || delta_y == 1)
                        push(attackers, get_square(board, last.rank, last.file), sizeof(get_square(board, last.rank, last.file)));
                    break;
                }
                default: break;
            }
        }

        destroy(&moves);
    }
}

static void get_attackers_on_diagonals(board_t *board, pos_t from_pos, bool piece_color, llist_t **attackers)
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

static void get_attackers_knight_positions(board_t *borad, pos_t from_pos, bool piece_color, llist_t **attacker)
{

}
