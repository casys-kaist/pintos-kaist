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

	CHECK (mkdir ("/a"), "mkdir \"/a\"");
	CHECK (mkdir ("a/b"), "mkdir \"a/b\"");
	CHECK (symlink ("/a/b", "/a/link_b") == 0, "create symlink \"a/link_b\"");

	CHECK (create ("a/link_b/file", 0), "create \"a/link_b/file\"");
	CHECK ((fd = open ("/a/link_b/file")) > 1, "open \"file\"");

	msg ("write \"file\"");
	while (ofs < FILE_SIZE)
	{
		write_some_bytes ("a/link_b/file", fd, buf_a, &ofs);
	}

	msg ("close \"file\"");
	close (fd);

	check_file ("a/b/file", buf_a, FILE_SIZE);
}
