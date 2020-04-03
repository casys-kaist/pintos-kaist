/* Starts 60 threads that each sleep for 10 seconds, then spin in
   a tight loop for 60 seconds, and sleep for another 60 seconds.
   Every 2 seconds after the initial sleep, the main thread
   prints the load average.

   The expected output is this (some margin of error is allowed):

   After 0 seconds, load average=1.00.
   After 2 seconds, load average=2.95.
   After 4 seconds, load average=4.84.
   After 6 seconds, load average=6.66.
   After 8 seconds, load average=8.42.
   After 10 seconds, load average=10.13.
   After 12 seconds, load average=11.78.
   After 14 seconds, load average=13.37.
   After 16 seconds, load average=14.91.
   After 18 seconds, load average=16.40.
   After 20 seconds, load average=17.84.
   After 22 seconds, load average=19.24.
   After 24 seconds, load average=20.58.
   After 26 seconds, load average=21.89.
   After 28 seconds, load average=23.15.
   After 30 seconds, load average=24.37.
   After 32 seconds, load average=25.54.
   After 34 seconds, load average=26.68.
   After 36 seconds, load average=27.78.
   After 38 seconds, load average=28.85.
   After 40 seconds, load average=29.88.
   After 42 seconds, load average=30.87.
   After 44 seconds, load average=31.84.
   After 46 seconds, load average=32.77.
   After 48 seconds, load average=33.67.
   After 50 seconds, load average=34.54.
   After 52 seconds, load average=35.38.
   After 54 seconds, load average=36.19.
   After 56 seconds, load average=36.98.
   After 58 seconds, load average=37.74.
   After 60 seconds, load average=37.48.
   After 62 seconds, load average=36.24.
   After 64 seconds, load average=35.04.
   After 66 seconds, load average=33.88.
   After 68 seconds, load average=32.76.
   After 70 seconds, load average=31.68.
   After 72 seconds, load average=30.63.
   After 74 seconds, load average=29.62.
   After 76 seconds, load average=28.64.
   After 78 seconds, load average=27.69.
   After 80 seconds, load average=26.78.
   After 82 seconds, load average=25.89.
   After 84 seconds, load average=25.04.
   After 86 seconds, load average=24.21.
   After 88 seconds, load average=23.41.
   After 90 seconds, load average=22.64.
   After 92 seconds, load average=21.89.
   After 94 seconds, load average=21.16.
   After 96 seconds, load average=20.46.
   After 98 seconds, load average=19.79.
   After 100 seconds, load average=19.13.
   After 102 seconds, load average=18.50.
   After 104 seconds, load average=17.89.
   After 106 seconds, load average=17.30.
   After 108 seconds, load average=16.73.
   After 110 seconds, load average=16.17.
   After 112 seconds, load average=15.64.
   After 114 seconds, load average=15.12.
   After 116 seconds, load average=14.62.
   After 118 seconds, load average=14.14.
   After 120 seconds, load average=13.67.
   After 122 seconds, load average=13.22.
   After 124 seconds, load average=12.78.
   After 126 seconds, load average=12.36.
   After 128 seconds, load average=11.95.
   After 130 seconds, load average=11.56.
   After 132 seconds, load average=11.17.
   After 134 seconds, load average=10.80.
   After 136 seconds, load average=10.45.
   After 138 seconds, load average=10.10.
   After 140 seconds, load average=9.77.
   After 142 seconds, load average=9.45.
   After 144 seconds, load average=9.13.
   After 146 seconds, load average=8.83.
   After 148 seconds, load average=8.54.
   After 150 seconds, load average=8.26.
   After 152 seconds, load average=7.98.
   After 154 seconds, load average=7.72.
   After 156 seconds, load average=7.47.
   After 158 seconds, load average=7.22.
   After 160 seconds, load average=6.98.
   After 162 seconds, load average=6.75.
   After 164 seconds, load average=6.53.
   After 166 seconds, load average=6.31.
   After 168 seconds, load average=6.10.
   After 170 seconds, load average=5.90.
   After 172 seconds, load average=5.70.
   After 174 seconds, load average=5.52.
   After 176 seconds, load average=5.33.
   After 178 seconds, load average=5.16.
*/

#include <stdio.h>
#include "tests/threads/tests.h"
#include "threads/init.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"
#include "devices/timer.h"

static int64_t start_time;

static void load_thread (void *aux);

#define THREAD_CNT 60

void
test_mlfqs_load_60 (void) 
{
  int i;
  
  ASSERT (thread_mlfqs);

  start_time = timer_ticks ();
  msg ("Starting %d niced load threads...", THREAD_CNT);
  for (i = 0; i < THREAD_CNT; i++) 
    {
      char name[16];
      snprintf(name, sizeof name, "load %d", i);
      thread_create (name, PRI_DEFAULT, load_thread, NULL);
    }
  msg ("Starting threads took %d seconds.",
       timer_elapsed (start_time) / TIMER_FREQ);
  
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
load_thread (void *aux UNUSED) 
{
  int64_t sleep_time = 10 * TIMER_FREQ;
  int64_t spin_time = sleep_time + 60 * TIMER_FREQ;
  int64_t exit_time = spin_time + 60 * TIMER_FREQ;

  thread_set_nice (20);
  timer_sleep (sleep_time - timer_elapsed (start_time));
  while (timer_elapsed (start_time) < spin_time)
    continue;
  timer_sleep (exit_time - timer_elapsed (start_time));
}
