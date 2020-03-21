/* lineup.c

   Converts a file to uppercase in-place.

   Incidentally, another way to do this while avoiding the seeks
   would be to open the input file, then remove() it and reopen
   it under another handle.  Because of Unix deletion semantics
   this works fine. */

#include <ctype.h>
#include <stdio.h>
#include <syscall.h>

int
main (int argc, char *argv[])
{
  char buf[1024];
  int handle;

  if (argc != 2)
    exit (1);

  handle = open (argv[1]);
  if (handle < 0)
    exit (2);

  for (;;) 
    {
      int n, i;

      n = read (handle, buf, sizeof buf);
      if (n <= 0)
        break;

      for (i = 0; i < n; i++)
        buf[i] = toupper ((unsigned char) buf[i]);

      seek (handle, tell (handle) - n);
      if (write (handle, buf, n) != n)
        printf ("write failed\n");
    }

  close (handle);

  return EXIT_SUCCESS;
}
