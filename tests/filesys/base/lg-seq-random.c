/* Writes out a fairly large file sequentially, one random-sized
   block at a time, then reads it back to verify that it was
   written properly. */

#define TEST_SIZE 75678
#include "tests/filesys/base/seq-random.inc"
