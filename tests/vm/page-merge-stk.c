#include "tests/main.h"
#include "tests/vm/parallel-merge.h"

void
test_main (void) 
{
  parallel_merge ("child-qsort", 72);
}
