/* Deletes and closes file that is mapped into memory
   and verifies that it can still be read through the mapping. */

#include <string.h>
#include <syscall.h>
#include "tests/vm/sample.inc"
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void)
{
  char *actual = (char *) 0x10000000;
  int handle;
  void *map;
  size_t i;

  /* Map file. */
  CHECK ((handle = open ("sample.txt")) > 1, "open \"sample.txt\"");
  CHECK ((map = mmap (actual, 4096, 0, handle, 0)) != MAP_FAILED, "mmap \"sample.txt\"");

  /* Close file and delete it. */
  close (handle);
  CHECK (remove ("sample.txt"), "remove \"sample.txt\"");
  CHECK (open ("sample.txt") == -1, "try to open \"sample.txt\"");

  /* Create a new file in hopes of overwriting data from the old
     one, in case the file system has incorrectly freed the
     file's data. */
  CHECK (create ("another", 4096 * 10), "create \"another\"");

  /* Check that mapped data is correct. */
  if (memcmp (actual, sample, strlen (sample)))
    fail ("read of mmap'd file reported bad data");

  /* Verify that data is followed by zeros. */
  for (i = strlen (sample); i < 4096; i++)
    if (actual[i] != 0)
      fail ("byte %zu of mmap'd region has value %02hhx (should be 0)",
            i, actual[i]);

  munmap (map);
}
