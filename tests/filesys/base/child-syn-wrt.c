/* Child process for syn-read test.
   Writes into part of a test file.  Other processes will be
   writing into other parts at the same time. */

#include <random.h>
#include <stdlib.h>
#include <syscall.h>
#include "tests/lib.h"
#include "tests/filesys/base/syn-write.h"

char buf[BUF_SIZE];

int
main (int argc, char *argv[])
{
  int child_idx;
  int fd;

  quiet = true;
  
  CHECK (argc == 2, "argc must be 2, actually %d", argc);
  child_idx = atoi (argv[1]);

  random_init (0);
  random_bytes (buf, sizeof buf);

  CHECK ((fd = open (file_name)) > 1, "open \"%s\"", file_name);
  seek (fd, CHUNK_SIZE * child_idx);
  CHECK (write (fd, buf + CHUNK_SIZE * child_idx, CHUNK_SIZE) > 0,
         "write \"%s\"", file_name);
  msg ("close \"%s\"", file_name);
  close (fd);

  return child_idx;
}
