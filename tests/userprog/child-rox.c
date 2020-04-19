/* Child process run by rox-child and rox-multichild tests.
   Opens and tries to write to its own executable, verifying that
   that is disallowed.
   Then recursively executes itself to the depth indicated by the
   first command-line argument. */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <syscall.h>
#include "tests/lib.h"

const char *test_name = "child-rox";

static void
try_write (void) 
{
  int handle;
  char buffer[19];

  quiet = true;
  CHECK ((handle = open ("child-rox")) > 1, "open \"child-rox\"");
  quiet = false;

  CHECK (write (handle, buffer, sizeof buffer) == 0,
         "try to write \"child-rox\"");
  
  close (handle);
}

int
main (int argc UNUSED, char *argv[]) 
{
  msg ("begin");
  try_write ();

  if (!isdigit (*argv[1]))
    fail ("bad command-line arguments");
  if (atoi (argv[1]) > 1) 
    {
      char cmd[128];
      int child;
      
      snprintf (cmd, sizeof cmd, "child-rox %d", atoi (argv[1]) - 1);
      msg ("exec \"%s\"", cmd);
      if (!(child = fork ("child-rox"))){
        exec (cmd);
      }

      if (child < 0)
        fail ("fork() returned %d", child);
      quiet = true;
      CHECK (wait (child) == 12, "wait for \"child-rox\"");
      quiet = false;
    }

  try_write ();
  msg ("end");

  return 12;
}
