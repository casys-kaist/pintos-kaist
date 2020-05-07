/* Tries to mmap with fd 1,
   which is the file descriptor for console output. 
	 mmap must fail silently or terminate the process with  
   exit code -1. */

#include <syscall.h>
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void) 
{
  CHECK (mmap ((void *) 0x10000000, 4096, 0, 1, 0) == MAP_FAILED,
         "try to mmap stdout");
}

