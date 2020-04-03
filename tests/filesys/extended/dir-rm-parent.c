/* Tries to remove a parent of the current directory.  This must
   fail, because that directory is non-empty. */

#include <syscall.h>
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void) 
{
  CHECK (mkdir ("a"), "mkdir \"a\"");
  CHECK (chdir ("a"), "chdir \"a\"");
  CHECK (mkdir ("b"), "mkdir \"b\"");
  CHECK (chdir ("b"), "chdir \"b\"");
  CHECK (!remove ("/a"), "remove \"/a\" (must fail)");
}
