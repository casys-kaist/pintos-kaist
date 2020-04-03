/* Starts 60 threads numbered 0 through 59.  Thread #i sleeps for
   (10+i) seconds, then spins in a loop for 60 seconds, then
   sleeps until a total of 120 seconds have passed.  Every 2
   seconds, starting 10 seconds in, the main thread prints the
   load average.

   The expected output is listed below.  Some margin of error is
   allowed.

   If your implementation fails this test but passes most other
   tests, then consider whether you are doing too much work in
   the timer interrupt.  If the timer interrupt handler takes too
   long, then the test's main thread will not have enough time to
   do its own work (printing a message) and go back to sleep
   before the next tick arrives.  Then the main thread will be
   ready, instead of sleeping, when the tick arrives,
   artificially driving up the load average.

   After 0 seconds, load average=0.00.
   After 2 seconds, load average=0.05.
   After 4 seconds, load average=0.16.
   After 6 seconds, load average=0.34.
   After 8 seconds, load average=0.58.
   After 10 seconds, load average=0.87.
   After 12 seconds, load average=1.22.
   After 14 seconds, load average=1.63.
   After 16 seconds, load average=2.09.
   After 18 seconds, load average=2.60.
   After 20 seconds, load average=3.16.
   After 22 seconds, load average=3.76.
   After 24 seconds, load average=4.42.
   After 26 seconds, load average=5.11.
   After 28 seconds, load average=5.85.
   After 30 seconds, load average=6.63.
   After 32 seconds, load average=7.46.
   After 34 seconds, load average=8.32.
   After 36 seconds, load average=9.22.
   After 38 seconds, load average=10.15.
   After 40 seconds, load average=11.12.
   After 42 seconds, load average=12.13.
   After 44 seconds, load average=13.16.
   After 46 seconds, load average=14.23.
   After 48 seconds, load average=15.33.
   After 50 seconds, load average=16.46.
   After 52 seconds, load average=17.62.
   After 54 seconds, load average=18.81.
   After 56 seconds, load average=20.02.
   After 58 seconds, load average=21.26.
   After 60 seconds, load average=22.52.
   After 62 seconds, load average=23.71.
   After 64 seconds, load average=24.80.
   After 66 seconds, load average=25.78.
   After 68 seconds, load average=26.66.
   After 70 seconds, load average=27.45.
   After 72 seconds, load average=28.14.
   After 74 seconds, load average=28.75.
   After 76 seconds, load average=29.27.
   After 78 seconds, load average=29.71.
   After 80 seconds, load average=30.06.
   After 82 seconds, load average=30.34.
   After 84 seconds, load average=30.55.
   After 86 seconds, load average=30.68.
   After 88 seconds, load average=30.74.
   After 90 seconds, load average=30.73.
   After 92 seconds, load average=30.66.
   After 94 seconds, load average=30.52.
   After 96 seconds, load average=30.32.
   After 98 seconds, load average=30.06.
   After 100 seconds, load average=29.74.
   After 102 seconds, load average=29.37.
   After 104 seconds, load average=28.95.
   After 106 seconds, load average=28.47.
   After 108 seconds, load average=27.94.
   After 110 seconds, load average=27.36.
   After 112 seconds, load average=26.74.
   After 114 seconds, load average=26.07.
   After 116 seconds, load average=25.36.
   After 118 seconds, load average=24.60.
   After 120 seconds, load average=23.81.
   After 122 seconds, load average=23.02.
   After 124 seconds, load average=22.26.
   After 126 seconds, load average=21.52.
   After 128 seconds, load average=20.81.
   After 130 seconds, load average=20.12.
   After 132 seconds, load average=19.46.
   After 134 seconds, load average=18.81.
   After 136 seconds, load average=18.19.
   After 138 seconds, load average=17.59.
   After 140 seconds, load average=17.01.
   After 142 seconds, load average=16.45.
   After 144 seconds, load average=15.90.
   After 146 seconds, load average=15.38.
   After 148 seconds, load average=14.87.
   After 150 seconds, load average=14.38.
   After 152 seconds, load average=13.90.
   After 154 seconds, load average=13.44.
   After 156 seconds, load average=13.00.
   After 158 seconds, load average=12.57.
   After 160 seconds, load average=12.15.
   After 162 seconds, load average=11.75.
   After 164 seconds, load average=11.36.
   After 166 seconds, load average=10.99.
   After 168 seconds, load average=10.62.
   After 170 seconds, load average=10.27.
   After 172 seconds, load average=9.93.
   After 174 seconds, load average=9.61.
   After 176 seconds, load average=9.29.
   After 178 seconds, load average=8.98.
*/

#include <stdio.h>
#include "tests/threads/tests.h"
#include "threads/init.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"
#include "devices/timer.h"

static int64_t start_time;

static void load_thread (void *seq_no);

#define THREAD_CNT 60

void
test_mlfqs_load_avg (void) 
{
  int i;
  
  ASSERT (thread_mlfqs);

  start_time = timer_ticks ();
  msg ("Starting %d load threads...", THREAD_CNT);
  for (i = 0; i < THREAD_CNT; i++) 
    {
      char name[16];
      snprintf(name, sizeof name, "load %d", i);
      thread_create (name, PRI_DEFAULT, load_thread, (void *) i);
    }
  msg ("Starting threads took %d seconds.",
       timer_elapsed (start_time) / TIMER_FREQ);
  thread_set_nice (-20);

  for (i = 0; i < 90; i++) 
    {
      int64_t sleep_until = start_time + TIMER_FREQ * (2 * i + 10);
      int load_avg;
      timer_sleep (sleep_until - timer_ticks ());
      load_avg = thread_get_load_avg ();
      msg ("After %d seconds, load average=%d.%02d.",
           i * 2, load_avg / 100, load_avg % 100);
    }
}

static void
load_thread (void *seq_no_) 
{
  int seq_no = (int) seq_no_;
  int sleep_time = TIMER_FREQ * (10 + seq_no);
  int spin_time = sleep_time + TIMER_FREQ * THREAD_CNT;
  int exit_time = TIMER_FREQ * (THREAD_CNT * 2);

  timer_sleep (sleep_time - timer_elapsed (start_time));
  while (timer_elapsed (start_time) < spin_time)
    continue;
  timer_sleep (exit_time - timer_elapsed (start_time));
}
