/* Creates a 128 kB file and repeatedly shuffles data in it
   through a memory mapping. */

#include <stdio.h>
#include <string.h>
#include <syscall.h>
#include "tests/arc4.h"
#include "tests/cksum.h"
#include "tests/lib.h"
#include "tests/main.h"

#define SIZE (128 * 1024)

static char *buf = (char *) 0x10000000;

void
test_main (void)
{
  size_t i;
  int handle;

  /* Create file, mmap. */
  CHECK (create ("buffer", SIZE), "create \"buffer\"");
  CHECK ((handle = open ("buffer")) > 1, "open \"buffer\"");
  CHECK (mmap (buf, SIZE, 1, handle, 0) != MAP_FAILED, "mmap \"buffer\"");

  /* Initialize. */
  for (i = 0; i < SIZE; i++)
    buf[i] = i * 257;
  msg ("init: cksum=%lu", cksum (buf, SIZE));

  /* Shuffle repeatedly. */
  for (i = 0; i < 10; i++)
    {
      shuffle (buf, SIZE, 1);
      msg ("shuffle %zu: cksum=%lu", i, cksum (buf, SIZE));
    }
}
