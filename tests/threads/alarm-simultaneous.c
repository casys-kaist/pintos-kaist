/* Creates N threads, each of which sleeps a different, fixed
   duration, M times.  Records the wake-up order and verifies
   that it is valid. */

#include <stdio.h>
#include "tests/threads/tests.h"
#include "threads/init.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"
#include "devices/timer.h"

static void test_sleep (int thread_cnt, int iterations);

void
test_alarm_simultaneous (void) 
{
  test_sleep (3, 5);
}

/* Information about the test. */
struct sleep_test 
  {
    int64_t start;              /* Current time at start of test. */
    int iterations;             /* Number of iterations per thread. */
    int *output_pos;            /* Current position in output buffer. */
  };

static void sleeper (void *);

/* Runs THREAD_CNT threads thread sleep ITERATIONS times each. */
static void
test_sleep (int thread_cnt, int iterations) 
{
  struct sleep_test test;
  int *output;
  int i;

  /* This test does not work with the MLFQS. */
  ASSERT (!thread_mlfqs);

  msg ("Creating %d threads to sleep %d times each.", thread_cnt, iterations);
  msg ("Each thread sleeps 10 ticks each time.");
  msg ("Within an iteration, all threads should wake up on the same tick.");

  /* Allocate memory. */
  output = malloc (sizeof *output * iterations * thread_cnt * 2);
  if (output == NULL)
    PANIC ("couldn't allocate memory for test");

  /* Initialize test. */
  test.start = timer_ticks () + 100;
  test.iterations = iterations;
  test.output_pos = output;

  /* Start threads. */
  ASSERT (output != NULL);
  for (i = 0; i < thread_cnt; i++)
    {
      char name[16];
      snprintf (name, sizeof name, "thread %d", i);
      thread_create (name, PRI_DEFAULT, sleeper, &test);
    }
  
  /* Wait long enough for all the threads to finish. */
  timer_sleep (100 + iterations * 10 + 100);

  /* Print completion order. */
  msg ("iteration 0, thread 0: woke up after %d ticks", output[0]);
  for (i = 1; i < test.output_pos - output; i++) 
    msg ("iteration %d, thread %d: woke up %d ticks later",
         i / thread_cnt, i % thread_cnt, output[i] - output[i - 1]);
  
  free (output);
}

/* Sleeper thread. */
static void
sleeper (void *test_) 
{
  struct sleep_test *test = test_;
  int i;

  /* Make sure we're at the beginning of a timer tick. */
  timer_sleep (1);

  for (i = 1; i <= test->iterations; i++) 
    {
      int64_t sleep_until = test->start + i * 10;
      timer_sleep (sleep_until - timer_ticks ());
      *test->output_pos++ = timer_ticks () - test->start;
      thread_yield ();
    }
}
