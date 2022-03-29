#include <random.h>
#include <stdio.h>
#include <syscall.h>
#include "tests/lib.h"
#include "tests/main.h"
#define TEST_SIZE 4096

static const char file_name[] = "data";
static char buf[TEST_SIZE];

void
test_main (void) {
  int fd;
  char c;
  long long read_cnt, write_cnt;

  CHECK (create (file_name, sizeof buf), "create \"%s\"", file_name);
  CHECK ((fd = open (file_name)) > 1, "open \"%s\"", file_name);
  random_bytes (buf, sizeof buf);

  read_cnt = get_fs_disk_read_cnt();
  write_cnt = get_fs_disk_write_cnt();

  CHECK (write (fd, buf, sizeof buf) > 0, "write \"%s\"", file_name);

  seek(fd, 0);
  for (int i = 0; i < TEST_SIZE; i++){
    read(fd, &c, 1);
    if (buf[i] != c) fail("file content mismatch in %d : %x %x", i, buf[i], c);
    seek(fd, i);
    c = 'a';
    write(fd, &c, 1);
  }
  
  seek(fd, 0);
  for (int i = 0; i < TEST_SIZE; i++){
    read(fd, &c, 1);
    if (c != 'a') fail("file content mismatch in %d : %x %x", i, buf[i], c);
  }

  CHECK (get_fs_disk_read_cnt() <= read_cnt, 
        "check read_cnt");
  CHECK (get_fs_disk_write_cnt() <= write_cnt + TEST_SIZE / 512, 
        "check write_cnt");

  msg ("close \"%s\"", file_name);
  close (fd);
}
