/* Creates directories /0/0/0 through /3/2/2 and files in the
   leaf directories, then removes them. */

#include <stdarg.h>
#include <stdio.h>
#include <syscall.h>
#include "tests/filesys/extended/mk-tree.h"
#include "tests/lib.h"
#include "tests/main.h"

static void remove_tree (int at, int bt, int ct, int dt);

void
test_main (void) 
{
  make_tree (4, 3, 3, 4);
  remove_tree (4, 3, 3, 4);
}

static void do_remove (const char *format, ...) PRINTF_FORMAT (1, 2);

static void
remove_tree (int at, int bt, int ct, int dt) 
{
  char try[128];
  int a, b, c, d;

  msg ("removing /0/0/0/0 through /%d/%d/%d/%d...",
       at - 1, bt - 1, ct - 1, dt - 1);
  quiet = true;
  for (a = 0; a < at; a++) 
    {
      for (b = 0; b < bt; b++) 
        {
          for (c = 0; c < ct; c++) 
            {
              for (d = 0; d < dt; d++)
                do_remove ("/%d/%d/%d/%d", a, b, c, d);
              do_remove ("/%d/%d/%d", a, b, c);
            }
          do_remove ("/%d/%d", a, b);
        }
      do_remove ("/%d", a);
    }
  quiet = false;

  snprintf (try, sizeof (try), "/%d/%d/%d/%d", at - 1, 0, ct - 1, 0);
  CHECK (open (try) == -1, "open \"%s\" (must return -1)", try);
}

static void
do_remove (const char *format, ...) 
{
  char name[128];
  va_list args;

  va_start (args, format);
  vsnprintf (name, sizeof name, format, args);
  va_end (args);

  CHECK (remove (name), "remove \"%s\"", name);
}
