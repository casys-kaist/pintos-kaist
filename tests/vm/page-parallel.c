/* Runs 4 child-linear processes at once. */

#include <syscall.h>
#include "tests/lib.h"
#include "tests/main.h"

#define CHILD_CNT 4

void
test_main (void)
{
  pid_t children[CHILD_CNT];
  int i;

  for (i = 0; i < CHILD_CNT; i++) {
    children[i] = fork ("child-linear");
    if (children[i] == 0) {
      if (exec ("child-linear") == -1)
        fail ("failed to exec child-linear");
    }
  }
  for (i = 0; i < CHILD_CNT; i++) {
    CHECK (wait (children[i]) == 0x42, "wait for child %d", i);
  }
}
