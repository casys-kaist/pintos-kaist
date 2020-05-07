/* Checks if fork is implemented properly with copy-on-write */

#include <string.h>
#include <syscall.h>
#include <stdio.h>
#include <stdint.h>
#include "tests/lib.h"
#include "tests/main.h"
#include "tests/vm/large.inc"

#define CHUNK_SIZE (128 * 1024)

void
test_main (void)
{
	pid_t child;
	void *pa_parent;
	void *pa_child;
	char *buf = "Lorem ipsum";

	CHECK (memcmp (buf, large, strlen (buf)) == 0, "check data consistency");
	pa_parent = get_phys_addr((void*)large);

	child = fork ("child");
	if (child == 0) {
		CHECK (memcmp (buf, large, strlen (buf)) == 0, "check data consistency");

		pa_child = get_phys_addr((void*)large);
		CHECK (pa_parent == pa_child, "two phys addrs should be the same.");

		large[0] = '@';
		CHECK (memcmp (buf, large, strlen (buf)) != 0, "check data change");

		pa_child = get_phys_addr((void*)large);
		CHECK (pa_parent != pa_child, "two phys addrs should not be the same.");
		return;
	}
	wait (child);
	CHECK (pa_parent == get_phys_addr((void*)large), "two phys addrs should be the same.");
	CHECK (memcmp (buf, large, strlen (buf)) == 0, "check data consistency");
	return;
}

