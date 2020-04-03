/* Library function for creating a tree of directories. */

#include <stdio.h>
#include <syscall.h>
#include "tests/filesys/extended/mk-tree.h"
#include "tests/lib.h"

static void do_mkdir (const char *format, ...) PRINTF_FORMAT (1, 2);
static void do_touch (const char *format, ...) PRINTF_FORMAT (1, 2);

void
make_tree (int at, int bt, int ct, int dt) 
{
  char try[128];
  int a, b, c, d;
  int fd;

  msg ("creating /0/0/0/0 through /%d/%d/%d/%d...",
       at - 1, bt - 1, ct - 1, dt - 1);
  quiet = true;
  for (a = 0; a < at; a++) 
    {
      do_mkdir ("/%d", a);
      for (b = 0; b < bt; b++) 
        {
          do_mkdir ("/%d/%d", a, b);
          for (c = 0; c < ct; c++) 
            {
              do_mkdir ("/%d/%d/%d", a, b, c);
              for (d = 0; d < dt; d++)
                do_touch ("/%d/%d/%d/%d", a, b, c, d);
            }
        }
    }
  quiet = false;

  snprintf (try, sizeof try, "/%d/%d/%d/%d", 0, bt - 1, 0, dt - 1);
  CHECK ((fd = open (try)) > 1, "open \"%s\"", try);
  msg ("close \"%s\"", try);
  close (fd);
}

static void
do_mkdir (const char *format, ...) 
{
  char dir[128];
  va_list args;

  va_start (args, format);
  vsnprintf (dir, sizeof dir, format, args);
  va_end (args);

  CHECK (mkdir (dir), "mkdir \"%s\"", dir);
}

static void
do_touch (const char *format, ...)
{
  char file[128];
  va_list args;

  va_start (args, format);
  vsnprintf (file, sizeof file, format, args);
  va_end (args);

  CHECK (create (file, 0), "create \"%s\"", file);
}
