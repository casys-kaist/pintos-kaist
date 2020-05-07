/* Allocates and writes to a 64 kB object on the stack.
   This must succeed. */

#include <string.h>
#include "tests/arc4.h"
#include "tests/cksum.h"
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void)
{
  char stk_obj[65536];
  struct arc4 arc4;

  arc4_init (&arc4, "foobar", 6);
  memset (stk_obj, 0, sizeof stk_obj);
  arc4_crypt (&arc4, stk_obj, sizeof stk_obj);
  msg ("cksum: %lu", cksum (stk_obj, sizeof stk_obj));
}
