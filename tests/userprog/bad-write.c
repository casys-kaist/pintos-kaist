/* This program attempts to write to memory at an address that is not mapped.
   This should terminate the process with a -1 exit code. */

#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void) 
{
  *(int *)NULL = 42;
  fail ("should have exited with -1");
}
