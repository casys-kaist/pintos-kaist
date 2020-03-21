/* Checks that when the alarm clock wakes up threads, the
   higher-priority threads run first. */

#include <stdio.h>
#include "tests/threads/tests.h"
#include "threads/init.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"
#include "devices/timer.h"

static thread_func alarm_priority_thread;
static int64_t wake_time;
static struct semaphore wait_sema;

void
test_alarm_priority (void) 
{
  int i;
  
  /* This test does not work with the MLFQS. */
  ASSERT (!thread_mlfqs);

  wake_time = timer_ticks () + 5 * TIMER_FREQ;
  sema_init (&wait_sema, 0);
  
  for (i = 0; i < 10; i++) 
    {
      int priority = PRI_DEFAULT - (i + 5) % 10 - 1;
      char name[16];
      snprintf (name, sizeof name, "priority %d", priority);
      thread_create (name, priority, alarm_priority_thread, NULL);
    }

  thread_set_priority (PRI_MIN);

  for (i = 0; i < 10; i++)
    sema_down (&wait_sema);
}

static void
alarm_priority_thread (void *aux UNUSED) 
{
  /* Busy-wait until the current time changes. */
  int64_t start_time = timer_ticks ();
  while (timer_elapsed (start_time) == 0)
    continue;

  /* Now we know we're at the very beginning of a timer tick, so
     we can call timer_sleep() without worrying about races
     between checking the time and a timer interrupt. */
  timer_sleep (wake_time - timer_ticks ());

  /* Print a message on wake-up. */
  msg ("Thread %s woke up.", thread_name ());

  sema_up (&wait_sema);
}
