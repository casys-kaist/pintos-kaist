/* Maps the same file into memory twice and verifies that the
   same data is readable in both. */

#include <string.h>
#include <syscall.h>
#include "tests/vm/sample.inc"
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void)
{
  char *actual[2] = {(char *) 0x10000000, (char *) 0x20000000};
  size_t i;
  int handle[2];

  for (i = 0; i < 2; i++) 
    {
      CHECK ((handle[i] = open ("sample.txt")) > 1,
             "open \"sample.txt\" #%zu", i);
      CHECK (mmap (actual[i], 4096, 0, handle[i], 0) != MAP_FAILED,
             "mmap \"sample.txt\" #%zu at %p", i, (void *) actual[i]);
    }

  for (i = 0; i < 2; i++)
    CHECK (!memcmp (actual[i], sample, strlen (sample)),
           "compare mmap'd file %zu against data", i);
}
