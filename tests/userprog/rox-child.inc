/* -*- c -*- */

#include <syscall.h>
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void) 
{
  const char *child_cmd = "child-rox " CHILD_CNT;
  int handle;
  pid_t child;
  char buffer[16];

  /* Open child-rox, read from it, write back same data. */
  CHECK ((handle = open ("child-rox")) > 1, "open \"child-rox\"");
  CHECK (read (handle, buffer, sizeof buffer) == (int) sizeof buffer,
         "read \"child-rox\"");
  seek (handle, 0);
  CHECK (write (handle, buffer, sizeof buffer) == (int) sizeof buffer,
         "write \"child-rox\"");

  /* Execute child-rox and wait for it. */
  msg ("exec \"%s\"", child_cmd);
  if (!(child = fork ("child-rox"))){
    exec (child_cmd);
  }

  if (child < 0)
    fail ("fork() returned %d", child);
  quiet = true;
  CHECK (wait (child) == 12, "wait for child");
  quiet = false;

  /* Write to child-rox again. */
  seek (handle, 0);
  CHECK (write (handle, buffer, sizeof buffer) == (int) sizeof buffer,
         "write \"child-rox\"");
}
