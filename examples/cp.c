/* cat.c

Copies one file to another. */

#include <stdio.h>
#include <syscall.h>

int
main (int argc, char *argv[]) 
{
  int in_fd, out_fd;

  if (argc != 3) 
    {
      printf ("usage: cp OLD NEW\n");
      return EXIT_FAILURE;
    }

  /* Open input file. */
  in_fd = open (argv[1]);
  if (in_fd < 0) 
    {
      printf ("%s: open failed\n", argv[1]);
      return EXIT_FAILURE;
    }

  /* Create and open output file. */
  if (!create (argv[2], filesize (in_fd))) 
    {
      printf ("%s: create failed\n", argv[2]);
      return EXIT_FAILURE;
    }
  out_fd = open (argv[2]);
  if (out_fd < 0) 
    {
      printf ("%s: open failed\n", argv[2]);
      return EXIT_FAILURE;
    }

  /* Copy data. */
  for (;;) 
    {
      char buffer[1024];
      int bytes_read = read (in_fd, buffer, sizeof buffer);
      if (bytes_read == 0)
        break;
      if (write (out_fd, buffer, bytes_read) != bytes_read) 
        {
          printf ("%s: write failed\n", argv[2]);
          return EXIT_FAILURE;
        }
    }

  return EXIT_SUCCESS;
}
