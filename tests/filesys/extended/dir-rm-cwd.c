/* Tries to remove the current directory, which may succeed or
   fail.  The requirements in each case are different; refer to
   the assignment for details. */

#include <syscall.h>
#include "tests/lib.h"
#include "tests/main.h"

static int
wrap_open (const char *name) 
{
  static int fds[8], fd_cnt;
  int fd, i;

  CHECK ((fd = open (name)) > 1, "open \"%s\"", name);
  for (i = 0; i < fd_cnt; i++)
    if (fds[i] == fd)
      fail ("fd returned is not unique");
  fds[fd_cnt++] = fd;
  return fd;
}

void
test_main (void) 
{
  int root_fd, a_fd0;
  char name[READDIR_MAX_LEN + 1];

  root_fd = wrap_open ("/");
  CHECK (mkdir ("a"), "mkdir \"a\"");

  a_fd0 = wrap_open ("/a");
  CHECK (!readdir (a_fd0, name), "verify \"/a\" is empty");
  CHECK (inumber (root_fd) != inumber (a_fd0),
         "\"/\" and \"/a\" must have different inumbers");

  CHECK (chdir ("a"), "chdir \"a\"");

  msg ("try to remove \"/a\"");
  if (remove ("/a"))
    {
      msg ("remove successful");

      CHECK (open ("/a") == -1, "open \"/a\" (must fail)");
      CHECK (open (".") == -1, "open \".\" (must fail)");
      CHECK (open ("..") == -1, "open \"..\" (must fail)");
      CHECK (!create ("x", 512), "create \"x\" (must fail)");
    }
  else
    {
      int a_fd1, a_fd2, a_fd3;

      msg ("remove failed");

      CHECK (!remove ("../a"), "try to remove \"../a\" (must fail)");
      CHECK (!remove (".././a"), "try to remove \".././a\" (must fail)");
      CHECK (!remove ("/./a"), "try to remove \"/./a\" (must fail)");

      a_fd1 = wrap_open ("/a");
      a_fd2 = wrap_open (".");
      CHECK (inumber (a_fd1) == inumber (a_fd2),
             "\"/a\" and \".\" must have same inumber");
      CHECK (inumber (root_fd) != inumber (a_fd1),
             "\"/\" and \"/a\" must have different inumbers");

      CHECK (chdir ("/a"), "chdir \"/a\"");
      a_fd3 = wrap_open (".");
      CHECK (inumber (a_fd3) == inumber (a_fd1),
             "\".\" must have same inumber as before");

      CHECK (chdir ("/"), "chdir \"/\"");
      CHECK (!remove ("a"), "try to remove \"a\" (must fail: still open)");
    }
  CHECK (!readdir (a_fd0, name), "verify \"/a\" is empty");
}
