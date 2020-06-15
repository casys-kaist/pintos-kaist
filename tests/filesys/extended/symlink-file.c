/* Grows two files in parallel and checks that their contents are
   correct using symlink. */

#include <stdio.h>
#include <random.h>
#include <syscall.h>
#include "tests/lib.h"
#include "tests/main.h"

#define FILE_SIZE 72943
static char buf_a[FILE_SIZE];
static char buf_b[FILE_SIZE];

#define DISK_SIZE (2 << 20) // 2MB
#define MAX_FILE_NR (DISK_SIZE / FILE_SIZE)

static void
write_some_bytes (const char *file_name, int fd, const char *buf, size_t *ofs)
{
  if (*ofs < FILE_SIZE)
    {
      size_t block_size = random_ulong () % (FILE_SIZE / 8) + 1;
      size_t ret_val;
      if (block_size > FILE_SIZE - *ofs)
        block_size = FILE_SIZE - *ofs;

      ret_val = write (fd, buf + *ofs, block_size);
      if (ret_val != block_size)
        fail ("write %zu bytes at offset %zu in \"%s\" returned %zu",
              block_size, *ofs, file_name, ret_val);
      *ofs += block_size;
    }
}

void
test_main (void)
{
  int fd_a, fd_b, fd_c;
  size_t ofs_a = 0, ofs_b = 0;
  int i;
  char fname[15];

  random_init (0);
  random_bytes (buf_a, sizeof buf_a);
  random_bytes (buf_b, sizeof buf_b);

  CHECK (create ("a", 0), "create \"a\"");
  CHECK (create ("b", 0), "create \"b\"");
  CHECK (symlink ("./a", "link_a") == 0, "create symlink \"link_a\"");
  CHECK (symlink ("./b", "link_b") == 0, "create symlink \"link_b\"");
  CHECK (symlink ("./link_b", "link_c") == 0, "create symlink \"link_c\"");

  CHECK ((fd_a = open ("link_a")) > 1, "open \"link_a\"");
  CHECK ((fd_b = open ("link_b")) > 1, "open \"link_b\"");
  CHECK ((fd_c = open ("link_c")) > 1, "open \"link_c\"");

  msg ("write \"link_a\" and \"link_b\" alternately");
  while (ofs_a < FILE_SIZE || ofs_b < FILE_SIZE)
    {
      write_some_bytes ("a", fd_a, buf_a, &ofs_a);
      write_some_bytes ("b", fd_b, buf_b, &ofs_b);
    }

  msg ("close \"link_a\"");
  close (fd_a);

  msg ("close \"link_b\"");
  close (fd_b);

  msg ("close \"link_c\"");
  close (fd_c);

  for (i = 0 ; i < 2*MAX_FILE_NR ; i++) {
    snprintf (fname, sizeof fname, "link_%d", i);
    if (symlink ("./a", fname))
        fail ("failed to create symlink: %s", fname);
  }
  for (i = 0 ; i < 2*MAX_FILE_NR ; i++) {
    snprintf (fname, sizeof fname, "link_%d", i);
    if (!remove (fname))
        fail ("failed to remove symlink: %s", fname);
  }

  check_file ("a", buf_a, FILE_SIZE);
  check_file ("b", buf_b, FILE_SIZE);
}
