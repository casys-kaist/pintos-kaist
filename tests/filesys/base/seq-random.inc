/* -*- c -*- */

#include <random.h>
#include "tests/filesys/seq-test.h"
#include "tests/main.h"

static char buf[TEST_SIZE];

static size_t
return_random (void) 
{
  return random_ulong () % 1031 + 1;
}

void
test_main (void) 
{
  random_init (-1);
  seq_test ("nibble",
            buf, sizeof buf, sizeof buf,
            return_random, NULL);
}
