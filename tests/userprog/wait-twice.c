/* Wait for a subprocess to finish, twice.
   The first call must wait in the usual way and return the exit code.
   The second wait call must return -1 immediately. */

#include <syscall.h>
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void) 
{
  pid_t child;
  if ((child = fork ("child-simple"))){
    msg ("wait(exec()) = %d", wait (child));
    msg ("wait(exec()) = %d", wait (child));
  } else {
    exec ("child-simple");
  }
}
