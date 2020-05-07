/* Generates about 1 MB of random data that is then divided into
   16 chunks.  A separate subprocess sorts each chunk in
   sequence.  Then we merge the chunks and verify that the result
   is what it should be. */

#include <syscall.h>
#include "tests/arc4.h"
#include "tests/lib.h"
#include "tests/main.h"

/* This is the max file size for an older version of the Pintos
   file system that had 126 direct blocks each pointing to a
   single disk sector.  We could raise it now. */
#define CHUNK_SIZE (126 * 512)
#define CHUNK_CNT 16                            /* Number of chunks. */
#define DATA_SIZE (CHUNK_CNT * CHUNK_SIZE)      /* Buffer size. */

unsigned char buf1[DATA_SIZE], buf2[DATA_SIZE];
size_t histogram[256];

/* Initialize buf1 with random data,
   then count the number of instances of each value within it. */
static void
init (void)
{
  struct arc4 arc4;
  size_t i;

  msg ("init");

  arc4_init (&arc4, "foobar", 6);
  arc4_crypt (&arc4, buf1, sizeof buf1);
  for (i = 0; i < sizeof buf1; i++)
    histogram[buf1[i]]++;
}

/* Sort each chunk of buf1 using a subprocess. */
static void
sort_chunks (void)
{
  size_t i;

  create ("buffer", CHUNK_SIZE);
  for (i = 0; i < CHUNK_CNT; i++)
    {
      pid_t child;
      int handle;

      msg ("sort chunk %zu", i);

      /* Write this chunk to a file. */
      quiet = true;
      CHECK ((handle = open ("buffer")) > 1, "open \"buffer\"");
      write (handle, buf1 + CHUNK_SIZE * i, CHUNK_SIZE);
      close (handle);

      /* Sort with subprocess. */
      child = fork("child-sort");
			/* if (child == 0) { */
			/* 	CHECK (exec ("child-sort buffer") != -1, "exec \"child-sort buffer\""); */
			/* } else { */
			/* 	CHECK (wait (child) == 123, "wait for child-sort"); */
			if (child == 0) {
				quiet = false;
				msg ("child[%zu] exec", i);
				if (exec ("child-sort buffer") == -1)
					fail ("child[%zu] exec fail", i);
				quiet = true;
			} else {
				quiet = false;
				if (wait (child) != 123)
					fail ("child[%zu] wait fail", i);
				msg ("child[%zu] wait success", i);
				quiet = true;

				/* Read chunk back from file. */
				CHECK ((handle = open ("buffer")) > 1, "open \"buffer\"");
				read (handle, buf1 + CHUNK_SIZE * i, CHUNK_SIZE);
				close (handle);

				quiet = false;
			}
    }
}

/* Merge the sorted chunks in buf1 into a fully sorted buf2. */
static void
merge (void)
{
  unsigned char *mp[CHUNK_CNT];
  size_t mp_left;
  unsigned char *op;
  size_t i;

  msg ("merge");

  /* Initialize merge pointers. */
  mp_left = CHUNK_CNT;
  for (i = 0; i < CHUNK_CNT; i++)
    mp[i] = buf1 + CHUNK_SIZE * i;

  /* Merge. */
  op = buf2;
  while (mp_left > 0)
    {
      /* Find smallest value. */
      size_t min = 0;
      for (i = 1; i < mp_left; i++)
        if (*mp[i] < *mp[min])
          min = i;

      /* Append value to buf2. */
      *op++ = *mp[min];

      /* Advance merge pointer.
         Delete this chunk from the set if it's emptied. */
      if ((++mp[min] - buf1) % CHUNK_SIZE == 0)
        mp[min] = mp[--mp_left];
    }
}

static void
verify (void)
{
  size_t buf_idx;
  size_t hist_idx;

  msg ("verify");

  buf_idx = 0;
  for (hist_idx = 0; hist_idx < sizeof histogram / sizeof *histogram;
       hist_idx++)
    {
      while (histogram[hist_idx]-- > 0)
        {
          if (buf2[buf_idx] != hist_idx)
            fail ("bad value %d in byte %zu", buf2[buf_idx], buf_idx);
          buf_idx++;
        }
    }

  msg ("success, buf_idx=%'zu", buf_idx);
}

void
test_main (void)
{
  init ();
  sort_chunks ();
  merge ();
  verify ();
}
