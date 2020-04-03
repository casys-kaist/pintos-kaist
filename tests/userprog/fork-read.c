/* After fork, the child process will read and close the opened file
   and the parent will access the closed file. */

#include <string.h>
#include <syscall.h>
#include "tests/userprog/boundary.h"
#include "tests/userprog/sample.inc"
#include "tests/lib.h"
#include "tests/main.h"

void
test_main (void) 
{
  pid_t pid;
  int handle;
  int byte_cnt;
  char *buffer;

  CHECK ((handle = open ("sample.txt")) > 1, "open \"sample.txt\"");
  buffer = get_boundary_area () - sizeof sample / 2;
  byte_cnt = read (handle, buffer, 20);
  
  if ((pid = fork("child"))){
    wait (pid);

    byte_cnt = read (handle, buffer + 20, sizeof sample - 21);
    if (byte_cnt != sizeof sample - 21)
      fail ("read() returned %d instead of %zu", byte_cnt, sizeof sample - 21);
    else if (strcmp (sample, buffer)) {
        msg ("expected text:\n%s", sample);
        msg ("text actually read:\n%s", buffer);
        fail ("expected text differs from actual");
    } else {
      msg ("Parent success");
    }

    close(handle);
  } else {
    msg ("child run");

    byte_cnt = read (handle, buffer + 20, sizeof sample - 21);
    if (byte_cnt != sizeof sample - 21)
      fail ("read() returned %d instead of %zu", byte_cnt, sizeof sample - 21);
    else if (strcmp (sample, buffer)) 
      {
        msg ("expected text:\n%s", sample);
        msg ("text actually read:\n%s", buffer);
        fail ("expected text differs from actual");
      }

    char magic_sentence[17] = "pintos is funny!";
    memcpy(buffer, magic_sentence, 17);

    msg ("Child: %s", buffer);
    close(handle);
  }
}
