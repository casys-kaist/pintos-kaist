/* -*- c -*- */

#include <syscall.h>
#include <stdio.h>
#include "tests/filesys/seq-test.h"
#include "tests/lib.h"
#include "tests/main.h"

static char buf[512];

static size_t
return_block_size (void) 
{
  return sizeof buf;
}

void
test_main (void) 
{
  size_t i;
  
#ifdef DIRECTORY
  CHECK (mkdir (DIRECTORY), "mkdir %s", DIRECTORY);
#define DIR_PREFIX DIRECTORY "/"
#else
#define DIR_PREFIX ""
#endif
  for (i = 0; i < FILE_CNT; i++) 
    {
      char file_name[128];
      snprintf (file_name, sizeof file_name, "%sfile%zu", DIR_PREFIX, i);

      msg ("creating and checking \"%s\"", file_name);

      quiet = true;
      seq_test (file_name,
                buf, sizeof buf, sizeof buf,
                return_block_size, NULL); 
      quiet = false;
    }
}
