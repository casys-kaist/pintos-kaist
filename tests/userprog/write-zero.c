/* Try a 0-byte write, which should return 0 without writing
   anything. */

#include <syscall.h>
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void) 
{
  int handle, byte_cnt;
  char buf;

  CHECK ((handle = open ("sample.txt")) > 1, "open \"sample.txt\"");

  buf = 123;
  byte_cnt = write (handle, &buf, 0);
  if (byte_cnt != 0)
    fail("write() returned %d instead of 0", byte_cnt);
}
