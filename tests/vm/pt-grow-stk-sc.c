/* This test checks that the stack is properly extended even if
   the first access to a stack location occurs inside a system
   call.

   From Godmar Back. */

#include <string.h>
#include <syscall.h>
#include "tests/vm/sample.inc"
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void)
{
  int handle;
  int slen = strlen (sample);
  char buf2[65536];

  /* Write file via write(). */
  CHECK (create ("sample.txt", slen), "create \"sample.txt\"");
  CHECK ((handle = open ("sample.txt")) > 1, "open \"sample.txt\"");
  CHECK (write (handle, sample, slen) == slen, "write \"sample.txt\"");
  close (handle);

  /* Read back via read(). */
  CHECK ((handle = open ("sample.txt")) > 1, "2nd open \"sample.txt\"");
  CHECK (read (handle, buf2 + 32768, slen) == slen, "read \"sample.txt\"");

  CHECK (!memcmp (sample, buf2 + 32768, slen), "compare written data against read data");
  close (handle);
}
