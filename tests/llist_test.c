#include <cgreen/cgreen.h>

#include "include/llist.h"

llist_t *head;

Describe(LinkedList);
BeforeEach(LinkedList) { head = NULL; }
AfterEach(LinkedList) {}

bool int_equals(const void * a, const void *b)
{
    int _a = *(int *)a, _b = *(int *)b;

    return _a == _b;
}

Ensure(LinkedList, count_is_correct)
{
    for(int value = 1; value < 5; value++) {
        push(&head, &value, sizeof(int));
        assert_that(count(head) == value);
    }
}

Ensure(LinkedList, is_empty_is_correct)
{
    int value = 5;

    assert_that(is_empty(head));
    push(&head, &value, sizeof(int));
    assert_that(!is_empty(head));
}

Ensure(LinkedList, contains_correctness)
{
    int value = 5;

    assert_that(!contains(head, &value, int_equals));
    push(&head, &value, sizeof(5));
    assert_that(contains(head, &value, int_equals));

    int not_found = 3;
    assert_that(!contains(head, &not_found, int_equals));
}

Ensure(LinkedList, primitive_types_are_not_mutable)
{
    int value = 5;
    push(&head, &value, sizeof(5));
    value = 3;
    assert_that(!contains(head, &value, int_equals));
}

Ensure(LinkedList, popleft_correctness)
{
    int values[] = { 1, 2, 3 };
    push(&head, &values[0], sizeof(int));
    push(&head, &values[1], sizeof(int));

    assert_that(*((int *)popleft(&head)) == values[1]);
    assert_that(*((int *)popleft(&head)) == values[0]);
}

Ensure(LinkedList, popleft_decreases_count)
{
    int values[] = { 1, 2, 3 };
    push(&head, &values[0], sizeof(int));
    push(&head, &values[1], sizeof(int));

    assert_that(count(head) == 2);
    popleft(&head);
    assert_that(count(head) == 1);
}
