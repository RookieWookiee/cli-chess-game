#ifndef POSITION_H
#define POSITION_H

#include <inttypes.h>
#include <stdbool.h>

typedef struct pos {
    uint8_t rank;
    uint8_t file;
} pos_t;

bool is_in_bounds(pos_t pos);
bool position_equals(const void *a, const void *b);
void position_print(const void *a);

enum {
    DOWN    = 1,
    UP      = -1,
    LEFT    = -1,
    RIGHT   = 1,
    NONE    = 0
};

#endif /* POSITION_H */
