/* Creates directories /0/0/0 through /3/2/2 and creates files in
   the leaf directories. */

#include "tests/filesys/extended/mk-tree.h"
#include "tests/main.h"

void
test_main (void) 
{
  make_tree (4, 3, 3, 4);
}

