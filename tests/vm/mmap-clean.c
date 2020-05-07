/* Verifies that mmap'd regions are only written back on munmap
   if the data was actually modified in memory. */

#include <string.h>
#include <syscall.h>
#include "tests/vm/sample.inc"
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void)
{
  static const char overwrite[] = "Now is the time for all good...";
  static char buffer[sizeof sample - 1];
  char *actual = (char *) 0x54321000;
  int handle;
  void *map;

  /* Open file, map, verify data. */
  CHECK ((handle = open ("sample.txt")) > 1, "open \"sample.txt\"");
 
	CHECK ((map = mmap (actual, 4096, 0, handle, 0)) != MAP_FAILED, "mmap \"sample.txt\"");
  if (memcmp (actual, sample, strlen (sample)))
    fail ("read of mmap'd file reported bad data");

  /* Modify file. */
  CHECK (write (handle, overwrite, strlen (overwrite))
         == (int) strlen (overwrite),
         "write \"sample.txt\"");

  /* Close mapping.  Data should not be written back, because we
     didn't modify it via the mapping. */
  msg ("munmap \"sample.txt\"");
  munmap (map);

  /* Read file back. */
  msg ("seek \"sample.txt\"");
  seek (handle, 0);
  CHECK (read (handle, buffer, sizeof buffer) == sizeof buffer,
         "read \"sample.txt\"");

  /* Verify that file overwrite worked. */
  if (memcmp (buffer, overwrite, strlen (overwrite))
      || memcmp (buffer + strlen (overwrite), sample + strlen (overwrite),
                 strlen (sample) - strlen (overwrite))) 
    {
      if (!memcmp (buffer, sample, strlen (sample)))
        fail ("munmap wrote back clean page");
      else
        fail ("read surprising data from file"); 
    }
  else
    msg ("file change was retained after munmap");
}
