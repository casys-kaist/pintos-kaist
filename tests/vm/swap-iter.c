/* Checks if any type of memory is properly swapped out and swapped in 
 * For this test, Pintos memory size is 128MB */ 

#include <string.h>
#include <syscall.h>
#include <stdio.h>
#include "tests/lib.h"
#include "tests/main.h"
#include "tests/vm/large.inc"


#define PAGE_SHIFT 12
#define PAGE_SIZE (1 << PAGE_SHIFT)
#define ONE_MB (1 << 20) // 1MB
#define CHUNK_SIZE (20*ONE_MB)
#define PAGE_COUNT (CHUNK_SIZE / PAGE_SIZE)

static char big_chunks[CHUNK_SIZE];

void
test_main (void)
{
    size_t i, handle;
    char *actual = (char *) 0x10000000;
    void *map;

    for (i = 0 ; i < PAGE_COUNT ; i++) {
        if ((i & 0x1ff) == 0)
            msg ("write sparsely over page %zu", i);
        big_chunks[i*PAGE_SIZE] = (char) i;
    }

    CHECK ((handle = open ("large.txt")) > 1, "open \"large.txt\"");
    CHECK ((map = mmap (actual, sizeof(large), 0, handle, 0)) != MAP_FAILED, "mmap \"large.txt\"");

    /* Read in file map'd page */
    if (memcmp (actual, large, strlen (large)))
        fail ("read of mmap'd file reported bad data");


    /* Read in anon page */
    for (i = 0; i < PAGE_COUNT; i++) {
        if (big_chunks[i*PAGE_SIZE] != (char) i)
            fail ("data is inconsistent");
        if ((i & 0x1ff) == 0)
            msg ("check consistency in page %zu", i);
    }

    /* Check file map'd page again */
    if (memcmp (actual, large, strlen (large)))
        fail ("read of mmap'd file reported bad data");

    /* Unmap and close opend file */
    munmap (map);
    close (handle);
}

