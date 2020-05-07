/* Read from an address 4,096 bytes below the stack pointer.
   The process must be terminated with -1 exit code. */

#include <string.h>
#include "tests/arc4.h"
#include "tests/cksum.h"
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void)
{
  asm volatile ("movq -4096(%rsp), %rax");
}
