/* Grows two files in parallel and checks that their contents are
   correct. */

#include <random.h>
#include <syscall.h>
#include "tests/lib.h"
#include "tests/main.h"

#define FILE_SIZE 8143
static char buf_a[FILE_SIZE];
static char buf_b[FILE_SIZE];

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
  int fd_a, fd_b;
  size_t ofs_a = 0, ofs_b = 0;

  random_init (0);
  random_bytes (buf_a, sizeof buf_a);
  random_bytes (buf_b, sizeof buf_b);

  CHECK (create ("a", 0), "create \"a\"");
  CHECK (create ("b", 0), "create \"b\"");

  CHECK ((fd_a = open ("a")) > 1, "open \"a\"");
  CHECK ((fd_b = open ("b")) > 1, "open \"b\"");

  msg ("write \"a\" and \"b\" alternately");
  while (ofs_a < FILE_SIZE || ofs_b < FILE_SIZE) 
    {
      write_some_bytes ("a", fd_a, buf_a, &ofs_a);
      write_some_bytes ("b", fd_b, buf_b, &ofs_b);
    }

  msg ("close \"a\"");
  close (fd_a);

  msg ("close \"b\"");
  close (fd_b);

  check_file ("a", buf_a, FILE_SIZE);
  check_file ("b", buf_b, FILE_SIZE);
}
