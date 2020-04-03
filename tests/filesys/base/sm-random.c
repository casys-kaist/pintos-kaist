/* Writes out the content of a fairly small file in random order,
   then reads it back in random order to verify that it was
   written properly. */

#define BLOCK_SIZE 13
#define TEST_SIZE (13 * 123)
#include "tests/filesys/base/random.inc"
