/* This is the final boss of Pintos Project 2.
     
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

const char *test_name = "dup2-complex";

char magic[] = {
  "Pintos is funny\n"
};

int
main (int argc UNUSED, char *argv[] UNUSED) {
  char *buffer;
  int byte_cnt = 0;
  int fd1, fd2, fd3 = 0x1CE, fd4 = 0x1CE - 0xC0FFEE, fd5, fd6;

  close (0);

  CHECK ((fd1 = open ("sample.txt")) > -1, "open \"sample.txt\"");
  CHECK ((fd2 = open ("sample.txt")) > -1, "open \"sample.txt\"");

  buffer = get_boundary_area () - sizeof sample / 2;

  byte_cnt += read (fd1, buffer + byte_cnt, 10);

  seek (fd2, 10);
  byte_cnt += read (fd2, buffer + byte_cnt, 10);

  CHECK (dup2 (fd2, fd3) > 1, "first dup2()");

  byte_cnt += read (fd3, buffer + byte_cnt, 10);

  seek (fd1, 15);
  byte_cnt += (read (fd1, buffer + 15, 30) - 15);

  dup2 (dup2 (fd3, fd3), dup2 (fd1, fd2));
  seek (fd2, tell (fd1));
  
  byte_cnt += read (fd2, buffer + byte_cnt, 17 + 2 * dup2 (fd4, fd1));

  close (fd1);
  close (fd2);

  seek (fd3, 60);
  byte_cnt += read (fd3, buffer + byte_cnt, 10);

  dup2 (dup2 (fd3, fd2), fd1);
  byte_cnt += read (fd2, buffer + byte_cnt, 10);
  byte_cnt += read (fd1, buffer + byte_cnt, 10);

  for (fd5 = 10; fd5 == fd1 || fd5 == fd2 || fd5 == fd3 || fd5 == fd4; fd5++){}
  dup2 (1, fd5);

  write (fd5, magic, sizeof magic - 1);

  create ("cheer", sizeof sample);
  create ("up", sizeof sample);
  
  fd4 = open ("cheer");
  fd6 = open ("up");

  dup2 (fd6, 1);

  msg ("%d", byte_cnt);
  snprintf (magic, sizeof magic, "%d", byte_cnt);
  write (fd4, magic, strlen (magic));

  pid_t pid;
  if (!(pid = fork ("child"))){ // child
    msg ("child begin");
    close (fd1);
    close (fd2);
    dup2 (fd4, fd2);
    dup2 (fd3, fd1);

    seek (fd2, 0);
    byte_cnt = read (fd2, magic, 3);
    msg ("%d", byte_cnt);
    byte_cnt = atoi (magic);
    msg ("%d", byte_cnt);
    
    read (fd1, buffer, 20);
    seek (fd4, 0);
    int write_cnt = write (fd4, buffer, 20);

    byte_cnt += write_cnt;
    close (fd1);
    close (fd2);
    close (fd3);
    close (fd4);
    close (fd5);
    close (fd6);
    seek (fd4, 0);

    msg ("child end");
    exit (byte_cnt);
  } 

  // parent
  int cur_pos = wait (pid);
  dup2 (fd5, 1);
  
  seek (fd4, 0);
  byte_cnt += read (fd4, buffer + byte_cnt, 20);
  close (fd4);

  seek (fd2, cur_pos);
  byte_cnt += read (fd2, buffer + byte_cnt , sizeof sample - byte_cnt);

  seek (1, 0);

  if (strcmp (sample, buffer)) {
    msg ("expected text:\n%s", sample);
    msg ("text actually read:\n%s", buffer);
    fail ("expected text differs from actual");
  } else {
    msg ("Parent success");
    close (1);
  }
}
