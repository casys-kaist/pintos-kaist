/* Grows a file in chunks while subprocesses read the growing
   file. */

#include <random.h>
#include <syscall.h>
#include "tests/filesys/extended/syn-rw.h"
#include "tests/lib.h"
#include "tests/main.h"

char buf[BUF_SIZE];

#define CHILD_CNT 4

void
test_main (void) 
{
  pid_t children[CHILD_CNT];
  size_t ofs;
  int fd;

  CHECK (create (file_name, 0), "create \"%s\"", file_name);
  CHECK ((fd = open (file_name)) > 1, "open \"%s\"", file_name);

  exec_children ("child-syn-rw", children, CHILD_CNT);

  random_bytes (buf, sizeof buf);
  quiet = true;
  for (ofs = 0; ofs < BUF_SIZE; ofs += CHUNK_SIZE)
    CHECK (write (fd, buf + ofs, CHUNK_SIZE) > 0,
           "write %d bytes at offset %zu in \"%s\"",
           (int) CHUNK_SIZE, ofs, file_name);
  quiet = false;

  wait_children (children, CHILD_CNT);
}
