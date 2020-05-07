/* Checks if file-mapped pages are lazy loaded  */

#include <string.h>
#include <syscall.h>
#include <stdio.h>
#include <stdint.h>
#include "tests/lib.h"
#include "tests/main.h"
#include "tests/vm/small.inc"

#define PAGE_SIZE 4096
#define PAGE_SHIFT 12
#define PAGE_ALIGN_CEIL(x) ((x % PAGE_SIZE ? (x+PAGE_SIZE) : x) >> PAGE_SHIFT << PAGE_SHIFT)

void
test_main (void)
{
	size_t handle;
	size_t small_size;
	char *actual = (char *) 0x10000000;
	void *map;
	size_t i, j;
	size_t page_cnt;
	void *pa;

	/* Map pages to a file */
	CHECK ((handle = open ("small.txt")) > 1, "open \"small.txt\"");
	small_size = sizeof small;
	msg ("sizeof small: %zu", small_size);
	msg ("page aligned size of small: %zu", PAGE_ALIGN_CEIL(small_size));
	CHECK ((map = mmap (actual, PAGE_ALIGN_CEIL(small_size), 0, handle, 0)) != MAP_FAILED, "mmap \"small.txt\"");
	page_cnt = PAGE_ALIGN_CEIL(small_size) / PAGE_SIZE;

	msg ("initial pages status");
	for (i = 0 ; i < page_cnt ; i++) {
		// All pages for the file should not be loaded yet.
		pa = get_phys_addr(&actual[i*PAGE_SIZE]);
		CHECK (pa == 0, "check if page is not loaded");
	}
	msg ("load pages (%zu)", page_cnt);
	for (i = 0 ; i < page_cnt ; i++) {
		msg ("load page [%zu]", i);
		if (memcmp (actual+i*PAGE_SIZE, small+i*PAGE_SIZE, 10))
			fail ("read of mmap'd file reported bad data");
		for (j = 0 ; j < page_cnt ; j++) {
			pa = get_phys_addr(&actual[j*PAGE_SIZE]);
			if (j <= i) {
				// Pages that have been accessed should be loaded
				CHECK (pa != 0, "check if page is loaded");
			}
			else {
				// Pages that have not been accessed should not be loaded.
				CHECK (pa == 0, "check if page is not loaded");
			}
		}
	}
	munmap (map);
	close (handle);
}

