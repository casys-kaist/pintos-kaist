/* Tries to mmap a zero length. mmap should fail if legnth is 0. 
 * In Linux kernels before 2.6.12, mmap succeeded even with length0. 
 * In this case: no mapping was created and the call returned addr.  
 * Since kernel 2.6.12, mapping zero length fails. We expect 
 * mmap in Pintos to fail (i.e. return MAP_FAILED) when length is 0. */

#include <string.h>
#include <syscall.h>
#include "tests/vm/sample.inc"
#include "tests/lib.h"
#include "tests/main.h"

#define ACTUAL ((void *) 0x10000000)

void
test_main (void)
{
  int handle;
  void *map;

  /* Write file via mmap. */
  CHECK (create ("sample.txt", strlen (sample)), "create \"sample.txt\"");
  CHECK ((handle = open ("sample.txt")) > 1, "open \"sample.txt\"");
  CHECK ((map = mmap (ACTUAL, 0, 0, handle, 0)) == MAP_FAILED, 
			"try to mmap zero length");
 
}
