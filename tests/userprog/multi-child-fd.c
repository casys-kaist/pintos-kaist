/* Opens a file and then runs a subprocess that tries to close
   the file.  (Pintos does not have inheritance of file handles,
   so this must fail.)  The parent process then attempts to use
   the file handle, which must succeed. */

#include <stdio.h>
#include <syscall.h>
#include "tests/userprog/sample.inc"
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void) 
{
  char child_cmd[128];
  int handle;

  CHECK ((handle = open ("sample.txt")) > 1, "open \"sample.txt\"");

  snprintf (child_cmd, sizeof child_cmd, "child-close %d", handle);
  
  pid_t pid;
  if (!(pid = fork("child-close"))){
    exec (child_cmd);
  }
  msg ("wait(exec()) = %d", wait (pid));

  check_file_handle (handle, "sample.txt", sample, sizeof sample - 1);
}
