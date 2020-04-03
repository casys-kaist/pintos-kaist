#ifndef TESTS_FILESYS_SEQ_TEST_H
#define TESTS_FILESYS_SEQ_TEST_H

#include <stddef.h>

void seq_test (const char *file_name,
               void *buf, size_t size, size_t initial_size,
               size_t (*block_size_func) (void),
               void (*check_func) (int fd, long ofs));

#endif /* tests/filesys/seq-test.h */
