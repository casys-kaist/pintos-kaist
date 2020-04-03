/* Writes out a fairly large file sequentially, one fixed-size
   block at a time, then reads it back to verify that it was
   written properly. */

#define TEST_SIZE 75678
#define BLOCK_SIZE 513
#include "tests/filesys/base/seq-block.inc"
