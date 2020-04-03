/* Passes an invalid pointer to the open system call.
   The process must be terminated with -1 exit code. */

#include <syscall.h>
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void) 
{
  msg ("open(0x20101234): %d", open ((char *) 0x20101234));
  fail ("should have called exit(-1)");
}
