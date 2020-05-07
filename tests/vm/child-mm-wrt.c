/* Child process of mmap-exit.
   Mmaps a file and writes to it via the mmap'ing, then exits
   without calling munmap.  The data in the mapped region must be
   written out at program termination. */

#include <string.h>
#include <syscall.h>
#include "tests/vm/sample.inc"
#include "tests/lib.h"
#include "tests/main.h"

#define ACTUAL ((void *) 0x10000000)

void
test_main (void)
{
  int handle;

  CHECK (create ("sample.txt", sizeof sample), "create \"sample.txt\"");
  CHECK ((handle = open ("sample.txt")) > 1, "open \"sample.txt\"");
  CHECK (mmap (ACTUAL, sizeof sample, 1, handle, 0) != MAP_FAILED, "mmap \"sample.txt\"");
  memcpy (ACTUAL, sample, sizeof sample);
}

