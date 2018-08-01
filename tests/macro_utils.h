#ifndef MACRO_UTILS_H
#define MACRO_UTILS_H

#define expect_times(mocked_func, constraint, n) \
    for(size_t i = 0; i < n; i++) { \
        expect(mocked_func, constraint); \
    }

#define expect_many(mocked_func, constraint, arr) \
    for(size_t i = 0; i < sizeof(arr); i++) { \
        expect(mocked_func, constraint(arr[i])); \
    }
 
#endif
