#include "piece.h"

#include <stdlib.h>

piece_t *make_piece(uint8_t rank, uint8_t file, uint8_t type_id)
{
    piece_t *piece = malloc(sizeof(piece_t));
    piece->rank = rank;
    piece->file = file;
    piece->type_id = type_id;
}
