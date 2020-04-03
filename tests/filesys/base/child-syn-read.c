/* Child process for syn-read test.
   Reads the contents of a test file a byte at a time, in the
   hope that this will take long enough that we can get a
   significant amount of contention in the kernel file system
   code. */

#include <random.h>
#include <stdio.h>
#include <stdlib.h>
#include <syscall.h>
#include "tests/lib.h"
#include "tests/filesys/base/syn-read.h"

const char *test_name = "child-syn-read";

static char buf[BUF_SIZE];

int
main (int argc, const char *argv[]) 
{
  int child_idx;
  int fd;
  size_t i;

  quiet = true;
  
  CHECK (argc == 2, "argc must be 2, actually %d", argc);
  child_idx = atoi (argv[1]);

  random_init (0);
  random_bytes (buf, sizeof buf);

  CHECK ((fd = open (file_name)) > 1, "open \"%s\"", file_name);
  for (i = 0; i < sizeof buf; i++) 
    {
      char c;
      CHECK (read (fd, &c, 1) > 0, "read \"%s\"", file_name);
      compare_bytes (&c, buf + i, 1, i, file_name);
    }
  close (fd);

  return child_idx;
}

