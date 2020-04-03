/* Wait for a process that will be killed for bad behavior. */

#include <syscall.h>
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void) 
{
  pid_t child;
  if ((child = fork ("child-bad"))){
    msg ("wait(exec()) = %d", wait (child));
  } else {
    exec ("child-bad");
  }
}
