/* Tries to map a zero-length file, which may or may not work but
   should not terminate the process or crash.
   Then dereferences the address that we tried to map,
   and the process must be terminated with -1 exit code. */

#include <syscall.h>
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void)
{
  char *data = (char *) 0x7f000000;
  int handle;

  CHECK (create ("empty", 0), "create empty file \"empty\"");
  CHECK ((handle = open ("empty")) > 1, "open \"empty\"");

  /* Calling mmap() might succeed or fail.  We don't care. */
  msg ("mmap \"empty\"");
  mmap (data, 0, 0, handle, 0);

  /* Regardless of whether the call worked, *data should cause
     the process to be terminated. */
  fail ("unmapped memory is readable (%d)", *data);
}

