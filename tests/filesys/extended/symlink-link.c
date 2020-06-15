/* Grows two files in parallel and checks that their contents are
   correct using symlink. */

#include <random.h>
#include <syscall.h>
#include "tests/lib.h"
#include "tests/main.h"

#define FILE_SIZE 72943
static char buf_a[FILE_SIZE];

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
	int fd;
	size_t ofs = 0;

	random_init (0);
	random_bytes (buf_a, sizeof buf_a);

	CHECK (symlink ("file", "link_a") == 0, "create symlink \"link_a\"");
	CHECK (symlink ("link_a", "link_b") == 0, "create symlink \"link_b\"");
	CHECK (symlink ("link_b", "link_c") == 0, "create symlink \"link_c\"");
	CHECK (create ("file", 0), "create \"file\"");

	CHECK ((fd = open ("link_c")) > 1, "open \"link_c\"");

	msg ("write \"link_c\"");
	while (ofs < FILE_SIZE)
	{
		write_some_bytes ("link_c", fd, buf_a, &ofs);
	}

	msg ("close \"link_c\"");
	close (fd);

	check_file ("file", buf_a, FILE_SIZE);
	check_file ("link_a", buf_a, FILE_SIZE);
	check_file ("link_b", buf_a, FILE_SIZE);
	check_file ("link_c", buf_a, FILE_SIZE);
}
