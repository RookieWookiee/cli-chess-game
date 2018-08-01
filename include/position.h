#ifndef POSITION_H
#define POSITION_H

#include <inttypes.h>
#include <stdbool.h>

typedef struct pos {
    uint8_t rank;
    uint8_t file;
} pos_t;

bool position_equals(const void *a, const void *b);
void position_print(const void *a);
bool is_in_bounds(pos_t pos);

#endif /* POSITION_H */
