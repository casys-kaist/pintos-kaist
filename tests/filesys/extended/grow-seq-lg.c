/* Grows a file from 0 bytes to 72,943 bytes, 1,234 bytes at a
   time. */

#define TEST_SIZE 72943
#include "tests/filesys/extended/grow-seq.inc"
