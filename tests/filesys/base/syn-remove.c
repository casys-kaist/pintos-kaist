/* Verifies that a deleted file may still be written to and read
   from. */

#include <random.h>
#include <string.h>
#include <syscall.h>
#include "tests/lib.h"
#include "tests/main.h"

char buf1[1234];
char buf2[1234];

void
test_main (void) 
{
  const char *file_name = "deleteme";
  int fd;
  
  CHECK (create (file_name, sizeof buf1), "create \"%s\"", file_name);
  CHECK ((fd = open (file_name)) > 1, "open \"%s\"", file_name);
  CHECK (remove (file_name), "remove \"%s\"", file_name);
  random_bytes (buf1, sizeof buf1);
  CHECK (write (fd, buf1, sizeof buf1) > 0, "write \"%s\"", file_name);
  msg ("seek \"%s\" to 0", file_name);
  seek (fd, 0);
  CHECK (read (fd, buf2, sizeof buf2) > 0, "read \"%s\"", file_name);
  compare_bytes (buf2, buf1, sizeof buf1, 0, file_name);
  msg ("close \"%s\"", file_name);
  close (fd);
}
