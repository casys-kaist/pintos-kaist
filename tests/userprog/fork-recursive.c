/* Forks and waits recursively. */

#include <syscall.h>
#include "tests/lib.h"
#include "tests/main.h"

void fork_and_wait (void);
int magic = 1;

void
fork_and_wait (void){
  int pid;
  magic++;

  if (magic >= 10){
    exit(magic);
  }

  if ((pid = fork("child"))){
    magic++;
    int status = wait (pid);
    msg ("Parent: child exit status is %d", status);
  } else {
    msg ("child run");
    fork_and_wait();
    exit(magic);
  }
}

void
test_main (void) 
{
  fork_and_wait();
}
