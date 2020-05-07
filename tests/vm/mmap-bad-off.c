/* Tries to mmap an invalid offset,
   which must either fail silently or terminate the process with
   exit code -1. */

#include <syscall.h>
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void) 
{
  int handle;
  CHECK ((handle = open ("large.txt")) > 1, "open \"large.txt\"");

  CHECK (mmap ((void *) 0x10000000, 4096, 0, handle, 0x1234) == MAP_FAILED,
         "try to mmap invalid offset");
}
