/* Forks a thread whose name spans the boundary between two pages.
   This is valid, so it must succeed. */

#include <syscall.h>
#include "tests/userprog/boundary.h"
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void) 
{
  pid_t pid = fork (copy_string_across_boundary ("child-simple"));
  if (pid == 0){
    msg ("child run");
    exit(54);
  } else {
    int exit_val = wait(pid);
    CHECK (pid > 0, "fork");
    CHECK (exit_val == 54, "wait");
  }
}
