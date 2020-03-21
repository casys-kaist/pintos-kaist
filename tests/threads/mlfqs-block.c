/* Checks that recent_cpu and priorities are updated for blocked
   threads.

   The main thread sleeps for 25 seconds, spins for 5 seconds,
   then releases a lock.  The "block" thread spins for 20 seconds
   then attempts to acquire the lock, which will block for 10
   seconds (until the main thread releases it).  If recent_cpu
   decays properly while the "block" thread sleeps, then the
   block thread should be immediately scheduled when the main
   thread releases the lock. */

#include <stdio.h>
#include "tests/threads/tests.h"
#include "threads/init.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"
#include "devices/timer.h"

static void block_thread (void *lock_);

void
test_mlfqs_block (void) 
{
  int64_t start_time;
  struct lock lock;
  
  ASSERT (thread_mlfqs);

  msg ("Main thread acquiring lock.");
  lock_init (&lock);
  lock_acquire (&lock);
  
  msg ("Main thread creating block thread, sleeping 25 seconds...");
  thread_create ("block", PRI_DEFAULT, block_thread, &lock);
  timer_sleep (25 * TIMER_FREQ);

  msg ("Main thread spinning for 5 seconds...");
  start_time = timer_ticks ();
  while (timer_elapsed (start_time) < 5 * TIMER_FREQ)
    continue;

  msg ("Main thread releasing lock.");
  lock_release (&lock);

  msg ("Block thread should have already acquired lock.");
}

static void
block_thread (void *lock_) 
{
  struct lock *lock = lock_;
  int64_t start_time;

  msg ("Block thread spinning for 20 seconds...");
  start_time = timer_ticks ();
  while (timer_elapsed (start_time) < 20 * TIMER_FREQ)
    continue;

  msg ("Block thread acquiring lock...");
  lock_acquire (lock);

  msg ("...got it.");
}
