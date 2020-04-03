/* -*- c -*- */

#include "tests/filesys/seq-test.h"
#include "tests/main.h"

static char buf[TEST_SIZE];

static size_t
return_test_size (void) 
{
  return TEST_SIZE;
}

void
test_main (void) 
{
  seq_test ("quux",
            buf, sizeof buf, sizeof buf,
            return_test_size, NULL);
}
