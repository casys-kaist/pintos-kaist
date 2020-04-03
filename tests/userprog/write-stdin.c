/* Try writing to fd 0 (stdin), 
   which may just fail or terminate the process with -1 exit
   code. */

#include <syscall.h>
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void) 
{
  char buf = 123;
  write (0, &buf, 1);
}
