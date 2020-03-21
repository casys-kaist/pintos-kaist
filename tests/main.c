#include <random.h>
#include "tests/lib.h"
#include "tests/main.h"

int
main (int argc UNUSED, char *argv[]) 
{
  test_name = argv[0];

  msg ("begin");
  random_init (0);
  test_main ();
  msg ("end");
  return 0;
}
