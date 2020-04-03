/* Reads data spanning two pages in virtual address space,
   which must succeed. */

#include <string.h>
#include <syscall.h>
#include "tests/userprog/boundary.h"
#include "tests/userprog/sample.inc"
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void) 
{
  int handle;
  int byte_cnt;
  char *buffer;

  CHECK ((handle = open ("sample.txt")) > 1, "open \"sample.txt\"");

  buffer = get_boundary_area () - sizeof sample / 2;
  byte_cnt = read (handle, buffer, sizeof sample - 1);
  if (byte_cnt != sizeof sample - 1)
    fail ("read() returned %d instead of %zu", byte_cnt, sizeof sample - 1);
  else if (strcmp (sample, buffer)) 
    {
      msg ("expected text:\n%s", sample);
      msg ("text actually read:\n%s", buffer);
      fail ("expected text differs from actual");
    }
}
