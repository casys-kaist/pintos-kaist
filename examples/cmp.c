/* cat.c

   Compares two files. */

#include <stdio.h>
#include <syscall.h>

int
main (int argc, char *argv[]) 
{
  int fd[2];

  if (argc != 3) 
    {
      printf ("usage: cmp A B\n");
      return EXIT_FAILURE;
    }

  /* Open files. */
  fd[0] = open (argv[1]);
  if (fd[0] < 0) 
    {
      printf ("%s: open failed\n", argv[1]);
      return EXIT_FAILURE;
    }
  fd[1] = open (argv[2]);
  if (fd[1] < 0) 
    {
      printf ("%s: open failed\n", argv[1]);
      return EXIT_FAILURE;
    }

  /* Compare data. */
  for (;;) 
    {
      int pos;
      char buffer[2][1024];
      int bytes_read[2];
      int min_read;
      int i;

      pos = tell (fd[0]);
      bytes_read[0] = read (fd[0], buffer[0], sizeof buffer[0]);
      bytes_read[1] = read (fd[1], buffer[1], sizeof buffer[1]);
      min_read = bytes_read[0] < bytes_read[1] ? bytes_read[0] : bytes_read[1];
      if (min_read == 0)
        break;

      for (i = 0; i < min_read; i++)
        if (buffer[0][i] != buffer[1][i]) 
          {
            printf ("Byte %d is %02hhx ('%c') in %s but %02hhx ('%c') in %s\n",
                    pos + i,
                    buffer[0][i], buffer[0][i], argv[1],
                    buffer[1][i], buffer[1][i], argv[2]);
            return EXIT_FAILURE;
          }

      if (min_read < bytes_read[1])
        printf ("%s is shorter than %s\n", argv[1], argv[2]);
      else if (min_read < bytes_read[0])
        printf ("%s is shorter than %s\n", argv[2], argv[1]);
    }

  printf ("%s and %s are identical\n", argv[1], argv[2]);

  return EXIT_SUCCESS;
}
