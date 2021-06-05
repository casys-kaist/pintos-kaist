#include <syscall.h>
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void) 
{
  CHECK (mkdir ("/a"), "mkdir \"/a\"");
  CHECK (mount ("a", 1, 0) == 0, "mount the second disk at \"/a\"");
  CHECK (chdir ("a"), "chdir \"/a\"");
  CHECK (mkdir ("b"), "mkdir \"/a/b\"");
  CHECK (chdir ("b"), "chdir \"/a/b\"");
  CHECK (chdir ("/"), "pop back to \"/\"");
  CHECK (umount ("a") == 0, "unmount the second disk from \"/a\"");
  CHECK (!chdir ("a/b"), "chdir to unmounted directory (must fail)");
  CHECK (mount ("a", 1, 0) == 0, "mount the second disk at \"/a\"");
  CHECK (chdir ("a/b"), "chdir to re-mounted directory");
}
