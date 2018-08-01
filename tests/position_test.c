#include <cgreen/cgreen.h>

#include "include/position.h"

Describe(Position);
BeforeEach(Position) {}
AfterEach(Position) {}

Ensure(Position, is_in_bounds_correctness)
{
    pos_t left_corner = { 0, 0 };
    pos_t right_corner = { 7, 7 };
    pos_t rank_out1 = { 8, 0 };
    pos_t file_out1 = { 0, 8 };
    pos_t rank_out2 = { -1, 0 };
    pos_t file_out2 = { 0, -1 };

    assert_that(is_in_bounds(left_corner));
    assert_that(is_in_bounds(right_corner));
    assert_that(!is_in_bounds(rank_out1));
    assert_that(!is_in_bounds(file_out1));
    assert_that(!is_in_bounds(rank_out2));
    assert_that(!is_in_bounds(file_out2));
}

Ensure(Position, equals_correctness)
{
    pos_t pos1 = { 0, 0 };
    pos_t pos2 = { 1, 0 };
    pos_t pos3 = { 1, 0 };
    pos_t pos4 = { 0, 1 };

    assert_that(position_equals(&pos1, &pos1));
    assert_that(position_equals(&pos2, &pos3));
    assert_that(!position_equals(&pos1, &pos2));
    assert_that(!position_equals(&pos1, &pos3));
    assert_that(!position_equals(&pos1, &pos4));
}
