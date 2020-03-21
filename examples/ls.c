/* ls.c
  
   Lists the contents of the directory or directories named on
   the command line, or of the current directory if none are
   named.

   By default, only the name of each file is printed.  If "-l" is
   given as the first argument, the type, size, and inumber of
   each file is also printed.  This won't work until project 4. */

#include <syscall.h>
#include <stdio.h>
#include <string.h>

static bool
list_dir (const char *dir, bool verbose) 
{
  int dir_fd = open (dir);
  if (dir_fd == -1) 
    {
      printf ("%s: not found\n", dir);
      return false;
    }

  if (isdir (dir_fd))
    {
      char name[READDIR_MAX_LEN];

      printf ("%s", dir);
      if (verbose)
        printf (" (inumber %d)", inumber (dir_fd));
      printf (":\n");

      while (readdir (dir_fd, name)) 
        {
          printf ("%s", name); 
          if (verbose) 
            {
              char full_name[128];
              int entry_fd;

              snprintf (full_name, sizeof full_name, "%s/%s", dir, name);
              entry_fd = open (full_name);

              printf (": ");
              if (entry_fd != -1)
                {
                  if (isdir (entry_fd))
                    printf ("directory");
                  else
                    printf ("%d-byte file", filesize (entry_fd));
                  printf (", inumber %d", inumber (entry_fd));
                }
              else
                printf ("open failed");
              close (entry_fd);
            }
          printf ("\n");
        }
    }
  else 
    printf ("%s: not a directory\n", dir);
  close (dir_fd);
  return true;
}

int
main (int argc, char *argv[]) 
{
  bool success = true;
  bool verbose = false;
  
  if (argc > 1 && !strcmp (argv[1], "-l")) 
    {
      verbose = true;
      argv++;
      argc--;
    }
  
  if (argc <= 1)
    success = list_dir (".", verbose);
  else 
    {
      int i;
      for (i = 1; i < argc; i++)
        if (!list_dir (argv[i], verbose))
          success = false;
    }
  return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
