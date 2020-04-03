/* tar.c

   Creates a tar archive. */

#include <syscall.h>
#include <stdio.h>
#include <string.h>

static void usage (void);
static bool make_tar_archive (const char *archive_name,
                              char *files[], size_t file_cnt);

int
main (int argc, char *argv[]) 
{
  if (argc < 3)
    usage ();

  return (make_tar_archive (argv[1], argv + 2, argc - 2)
          ? EXIT_SUCCESS : EXIT_FAILURE);
}

static void
usage (void) 
{
  printf ("tar, tar archive creator\n"
          "Usage: tar ARCHIVE FILE...\n"
          "where ARCHIVE is the tar archive to create\n"
          "  and FILE... is a list of files or directories to put into it.\n"
          "(ARCHIVE itself will not be included in the archive, even if it\n"
          "is in a directory to be archived.)\n");
  exit (EXIT_FAILURE);
}

static bool archive_file (char file_name[], size_t file_name_size,
                          int archive_fd, bool *write_error);

static bool archive_ordinary_file (const char *file_name, int file_fd,
                                   int archive_fd, bool *write_error);
static bool archive_directory (char file_name[], size_t file_name_size,
                               int file_fd, int archive_fd, bool *write_error);
static bool write_header (const char *file_name,
                          char type_flag, int size, unsigned mode,
                          int archive_fd, bool *write_error);

static bool do_write (int fd, const char *buffer, int size, bool *write_error);

static bool
make_tar_archive (const char *archive_name, char *files[], size_t file_cnt) 
{
  static const char zeros[512];
  int archive_fd;
  bool success = true;
  bool write_error = false;
  size_t i;
  
  if (!create (archive_name, 0)) 
    {
      printf ("%s: create failed\n", archive_name);
      return false;
    }
  archive_fd = open (archive_name);
  if (archive_fd < 0)
    {
      printf ("%s: open failed\n", archive_name);
      return false;
    }

  for (i = 0; i < file_cnt; i++) 
    {
      char file_name[128];
      
      strlcpy (file_name, files[i], sizeof file_name);
      if (!archive_file (file_name, sizeof file_name,
                         archive_fd, &write_error))
        success = false;
    }

  if (!do_write (archive_fd, zeros, 512, &write_error)
      || !do_write (archive_fd, zeros, 512, &write_error)) 
    success = false;

  close (archive_fd);

  return success;
}

static bool
archive_file (char file_name[], size_t file_name_size,
              int archive_fd, bool *write_error) 
{
  int file_fd = open (file_name);
  if (file_fd >= 0) 
    {
      bool success;

      if (inumber (file_fd) != inumber (archive_fd)) 
        {
          if (!isdir (file_fd))
            success = archive_ordinary_file (file_name, file_fd,
                                             archive_fd, write_error);
          else
            success = archive_directory (file_name, file_name_size, file_fd,
                                         archive_fd, write_error);      
        }
      else
        {
          /* Nothing to do: don't try to archive the archive file. */
          success = true;
        }
  
      close (file_fd);

      return success;
    }
  else
    {
      printf ("%s: open failed\n", file_name);
      return false;
    }
}

static bool
archive_ordinary_file (const char *file_name, int file_fd,
                       int archive_fd, bool *write_error)
{
  bool read_error = false;
  bool success = true;
  int file_size = filesize (file_fd);

  if (!write_header (file_name, '0', file_size, 0644, archive_fd, write_error))
    return false;

  while (file_size > 0) 
    {
      static char buf[512];
      int chunk_size = file_size > 512 ? 512 : file_size;
      int read_retval = read (file_fd, buf, chunk_size);
      int bytes_read = read_retval > 0 ? read_retval : 0;

      if (bytes_read != chunk_size && !read_error) 
        {
          printf ("%s: read error\n", file_name);
          read_error = true;
          success = false;
        }

      memset (buf + bytes_read, 0, 512 - bytes_read);
      if (!do_write (archive_fd, buf, 512, write_error))
        success = false;

      file_size -= chunk_size;
    }

  return success;
}

static bool
archive_directory (char file_name[], size_t file_name_size, int file_fd,
                   int archive_fd, bool *write_error)
{
  size_t dir_len;
  bool success = true;

  dir_len = strlen (file_name);
  if (dir_len + 1 + READDIR_MAX_LEN + 1 > file_name_size) 
    {
      printf ("%s: file name too long\n", file_name);
      return false;
    }

  if (!write_header (file_name, '5', 0, 0755, archive_fd, write_error))
    return false;
      
  file_name[dir_len] = '/';
  while (readdir (file_fd, &file_name[dir_len + 1])) 
    if (!archive_file (file_name, file_name_size, archive_fd, write_error))
      success = false;
  file_name[dir_len] = '\0';

  return success;
}

static bool
write_header (const char *file_name,
              char type_flag, int size, unsigned mode,
              int archive_fd, bool *write_error) 
{
  static char header[512];
  unsigned chksum;
  size_t i;

  memset (header, 0, sizeof header);

  /* Drop confusing and possibly dangerous prefixes from
     FILE_NAME. */
  while (*file_name == '/'
         || !memcmp (file_name, "./", 2)
         || !memcmp (file_name, "../", 3))
    file_name = strchr (file_name, '/') + 1;
  if (*file_name == '\0') 
    {
      /* Dropped *everything* from FILE_NAME.
         Should only be possible for a directory. */
      ASSERT (type_flag == '5');
      return true; 
    }
  else if (strlen (file_name) > 99)
    {
      printf ("%s: file name too long\n", file_name);
      return false;
    }

  /* Fill in header except for final checksum. */
  strlcpy (header, file_name, 100);                 /* name */
  snprintf (header + 100, 8, "%07o", mode);         /* mode */
  strlcpy (header + 108, "0000000", 8);             /* uid */
  strlcpy (header + 116, "0000000", 8);             /* gid */
  snprintf (header + 124, 12, "%011o", size);       /* size */
  snprintf (header + 136, 12, "%011o", 1136102400); /* mtime (2006-01-01) */
  memset (header + 148, ' ', 8);                    /* chksum */
  header[156] = type_flag;                          /* typeflag */
  strlcpy (header + 257, "ustar", 6);               /* magic */
  strlcpy (header + 263, "00", 3);                  /* version */

  /* Compute and fill in final checksum. */
  chksum = 0;
  for (i = 0; i < 512; i++)
    chksum += (uint8_t) header[i];
  snprintf (header + 148, 8, "%07o", chksum);

  /* Write header. */
  return do_write (archive_fd, header, 512, write_error);
}

static bool
do_write (int fd, const char *buffer, int size, bool *write_error) 
{
  if (write (fd, buffer, size) == size) 
    return true;
  else
    {
      if (!*write_error) 
        {
          printf ("error writing archive\n");
          *write_error = true; 
        }
      return false; 
    }
}
