#include "include/position.h"
#include "include/board.h"

#include <stdbool.h>
#include <stdio.h>

bool is_in_bounds(pos_t pos)
{
    /* There's no checking for lower bounds because the underlying type is unsigned. */
    if(pos.rank > RANK_8 || pos.file > FILE_H) return false;

    return true;
}

bool position_equals(const void *a, const void *b)
{
    const pos_t *_a = a, *_b = b; /* for brevity */

    return _a->rank == _b->rank && _a->file == _b->file;
}

void position_print(const void *a)
{
    const pos_t *_a = a;

    int rank = 1 + RANK_8 - _a->rank;
    char file = 'A' + _a->file;
    printf("%d%c, ", rank, file);
}
