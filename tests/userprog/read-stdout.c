/* Try reading from fd 1 (stdout), 
   which may just fail or terminate the process with -1 exit
   code. */

#include <stdio.h>
#include <syscall.h>
#include "tests/main.h"

void
test_main (void) 
{
  char buf;
  read (STDOUT_FILENO, &buf, 1);
}
