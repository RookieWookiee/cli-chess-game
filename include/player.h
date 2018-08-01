#ifndef PLAYER_H
#define PLAYER_H

#include <inttypes.h>
#include <stdbool.h>

typedef struct piece piece_t;
typedef struct board board_t;

typedef struct player {
    /* 13 is the count of the type id enums*/
    uint8_t num_pieces[13]; 
    piece_t **pieces[13][10];
    /* player color */
    bool color;
} player_t;

player_t *make_player(bool color, board_t *board);
piece_t *get_king(player_t *self);

#endif /* PLAYER_H */
