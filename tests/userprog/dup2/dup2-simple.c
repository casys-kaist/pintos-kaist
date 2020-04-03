/* This is just for fun.
     
   Written by Minkyu Jung, Jinyoung Oh <cs330_ta@casys.kaist.ac.kr>
*/

#include <debug.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <syscall.h>
#include <random.h>
#include "tests/lib.h"
#include "tests/userprog/boundary.h"
#include "tests/userprog/sample.inc"

const char *test_name = "dup2-simple";

int
main (int argc UNUSED, char *argv[] UNUSED) {
  char *buffer;
  int byte_cnt = 0;
  int fd1, fd2 = 0x1CE;

  close (0);
  CHECK ((fd1 = open ("sample.txt")) > -1, "open \"sample.txt\"");
  buffer = get_boundary_area () - sizeof sample / 2;
  byte_cnt += read (fd1, buffer + byte_cnt, 10);

  CHECK (dup2 (fd1, fd2) > 1, "first dup2()");

  byte_cnt += read (fd2, buffer + byte_cnt , sizeof sample - byte_cnt);

  if (strcmp (sample, buffer)) {
    msg ("expected text:\n%s", sample);
    msg ("text actually read:\n%s", buffer);
    fail ("expected text differs from actual");
  } else {
    msg ("Parent success");
  }
}
