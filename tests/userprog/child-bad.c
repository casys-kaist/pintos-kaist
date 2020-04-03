/* Child process run by wait-killed test.
   Tries to execute pintos, which should then terminate the process with a
   -1 exit code because `pintos` is not present in Pintos. */

#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void) 
{
  exec ("pintos");
  fail ("should have exited with -1");
}
