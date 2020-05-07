/* Child process for mmap-inherit test.
   Tries to write to a mapping present in the parent.
   The process must be terminated with -1 exit code. */

#include <string.h>
#include "tests/vm/sample.inc"
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void)
{
  memset ((char *) 0x54321000, 0, 4096);
  fail ("child can modify parent's memory mappings");
}

