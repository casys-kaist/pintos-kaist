/* -*- c -*- */

#include "tests/filesys/seq-test.h"
#include "tests/main.h"

static char buf[TEST_SIZE];

static size_t
return_block_size (void) 
{
  return 1234;
}

void
test_main (void) 
{
  seq_test ("testme",
            buf, sizeof buf, 0,
            return_block_size, NULL);
}
