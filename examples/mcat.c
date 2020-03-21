/* mcat.c

   Prints files specified on command line to the console, using
   mmap. */

#include <stdio.h>
#include <syscall.h>

int
main (int argc, char *argv[]) 
{
  int i;
  
  for (i = 1; i < argc; i++) 
    {
      int fd;
      mapid_t map;
      void *data = (void *) 0x10000000;
      int size;

      /* Open input file. */
      fd = open (argv[i]);
      if (fd < 0) 
        {
          printf ("%s: open failed\n", argv[i]);
          return EXIT_FAILURE;
        }
      size = filesize (fd);

      /* Map files. */
      map = mmap (fd, data);
      if (map == MAP_FAILED) 
        {
          printf ("%s: mmap failed\n", argv[i]);
          return EXIT_FAILURE;
        }

      /* Write file to console. */
      write (STDOUT_FILENO, data, size);

      /* Unmap files (optional). */
      munmap (map);
    }
  return EXIT_SUCCESS;
}
