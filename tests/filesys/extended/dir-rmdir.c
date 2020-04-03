/* Creates and removes a directory, then makes sure that it's
   really gone. */

#include <syscall.h>
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void) 
{
  CHECK (mkdir ("a"), "mkdir \"a\"");
  CHECK (remove ("a"), "rmdir \"a\"");
  CHECK (!chdir ("a"), "chdir \"a\" (must return false)");
}
