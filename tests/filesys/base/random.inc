/* -*- c -*- */

#include <random.h>
#include <stdio.h>
#include <string.h>
#include <syscall.h>
#include "tests/lib.h"
#include "tests/main.h"

#if TEST_SIZE % BLOCK_SIZE != 0
#error TEST_SIZE must be a multiple of BLOCK_SIZE
#endif

#define BLOCK_CNT (TEST_SIZE / BLOCK_SIZE)

char buf[TEST_SIZE];
int order[BLOCK_CNT];

void
test_main (void) 
{
  const char *file_name = "bazzle";
  int fd;
  size_t i;

  random_init (57);
  random_bytes (buf, sizeof buf);

  for (i = 0; i < BLOCK_CNT; i++)
    order[i] = i;

  CHECK (create (file_name, TEST_SIZE), "create \"%s\"", file_name);
  CHECK ((fd = open (file_name)) > 1, "open \"%s\"", file_name);

  msg ("write \"%s\" in random order", file_name);
  shuffle (order, BLOCK_CNT, sizeof *order);
  for (i = 0; i < BLOCK_CNT; i++) 
    {
      size_t ofs = BLOCK_SIZE * order[i];
      seek (fd, ofs);
      if (write (fd, buf + ofs, BLOCK_SIZE) != BLOCK_SIZE)
        fail ("write %d bytes at offset %zu failed", (int) BLOCK_SIZE, ofs);
    }

  msg ("read \"%s\" in random order", file_name);
  shuffle (order, BLOCK_CNT, sizeof *order);
  for (i = 0; i < BLOCK_CNT; i++) 
    {
      char block[BLOCK_SIZE];
      size_t ofs = BLOCK_SIZE * order[i];
      seek (fd, ofs);
      if (read (fd, block, BLOCK_SIZE) != BLOCK_SIZE)
        fail ("read %d bytes at offset %zu failed", (int) BLOCK_SIZE, ofs);
      compare_bytes (block, buf + ofs, BLOCK_SIZE, ofs, file_name);
    }

  msg ("close \"%s\"", file_name);
  close (fd);
}
