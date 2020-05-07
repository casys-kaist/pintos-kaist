/* Try to write to the code segment using a system call.
   The process must be terminated with -1 exit code. */

#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void)
{
  int handle;

  CHECK ((handle = open ("sample.txt")) > 1, "open \"sample.txt\"");
  read (handle, (void *) test_main, 1);
  fail ("survived reading data into code segment");
}
