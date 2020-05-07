/* Each thread will read 5MB of anonymous pages
 * Lastly, frees the allocated memory. 
 */

#include <string.h>
#include <stdint.h>
#include <syscall.h>
#include "tests/lib.h"
#include "tests/main.h"


#define PAGE_SHIFT 12
#define PAGE_SIZE (1 << PAGE_SHIFT) // 4KB
#define ONE_MB (1 << 20) // 1MB
#define CHUNK_SIZE (1*ONE_MB)
#define PAGE_COUNT (CHUNK_SIZE / PAGE_SIZE)

static char big_chunks[CHUNK_SIZE];

void
test_main (void) 
{
	size_t i;
    char *mem;

    for (i = 0 ; i < PAGE_COUNT ; i++) {
        mem = (big_chunks+(i*PAGE_SIZE));
        *mem = (char)i;
    }

    for (i = 0 ; i < PAGE_COUNT ; i++) {
        mem = (big_chunks+(i*PAGE_SIZE));
        if((char)i != *mem) {
		    fail ("data is inconsistent");
        }
    }
    exit(0);
}

