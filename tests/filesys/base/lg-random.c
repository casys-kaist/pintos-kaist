/* Writes out the content of a fairly large file in random order,
   then reads it back in random order to verify that it was
   written properly. */

#define BLOCK_SIZE 512
#define TEST_SIZE (512 * 150)
#include "tests/filesys/base/random.inc"
