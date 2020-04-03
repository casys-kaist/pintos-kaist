/* Ensure that the executable of a running process cannot be
   modified, even in the presence of multiple children. */

#define CHILD_CNT "5"
#include "tests/userprog/rox-child.inc"
