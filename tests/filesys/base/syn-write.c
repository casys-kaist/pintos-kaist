/* Spawns several child processes to write out different parts of
   the contents of a file and waits for them to finish.  Then
   reads back the file and verifies its contents. */

#include <random.h>
#include <stdio.h>
#include <string.h>
#include <syscall.h>
#include "tests/filesys/base/syn-write.h"
#include "tests/lib.h"
#include "tests/main.h"

char buf1[BUF_SIZE];
char buf2[BUF_SIZE];

void
test_main (void) 
{
  pid_t children[CHILD_CNT];
  int fd;

  CHECK (create (file_name, sizeof buf1), "create \"%s\"", file_name);

  exec_children ("child-syn-wrt", children, CHILD_CNT);
  wait_children (children, CHILD_CNT);

  CHECK ((fd = open (file_name)) > 1, "open \"%s\"", file_name);
  CHECK (read (fd, buf1, sizeof buf1) > 0, "read \"%s\"", file_name);
  random_bytes (buf2, sizeof buf2);
  compare_bytes (buf1, buf2, sizeof buf1, 0, file_name);
}
