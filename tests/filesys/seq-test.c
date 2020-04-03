#include "tests/filesys/seq-test.h"
#include <random.h>
#include <syscall.h>
#include "tests/lib.h"

void 
seq_test (const char *file_name, void *buf, size_t size, size_t initial_size,
          size_t (*block_size_func) (void),
          void (*check_func) (int fd, long ofs)) 
{
  size_t ofs;
  int fd;
  
  random_bytes (buf, size);
  CHECK (create (file_name, initial_size), "create \"%s\"", file_name);
  CHECK ((fd = open (file_name)) > 1, "open \"%s\"", file_name);

  ofs = 0;
  msg ("writing \"%s\"", file_name);
  while (ofs < size) 
    {
      size_t block_size = block_size_func ();
      if (block_size > size - ofs)
        block_size = size - ofs;

      if (write (fd, buf + ofs, block_size) != (int) block_size)
        fail ("write %zu bytes at offset %zu in \"%s\" failed",
              block_size, ofs, file_name);

      ofs += block_size;
      if (check_func != NULL)
        check_func (fd, ofs);
    }
  msg ("close \"%s\"", file_name);
  close (fd);
  check_file (file_name, buf, size);
}
