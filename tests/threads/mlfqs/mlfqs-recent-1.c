/* Checks that recent_cpu is calculated properly for the case of
   a single ready process.

   The expected output is this (some margin of error is allowed):

   After 2 seconds, recent_cpu is 6.40, load_avg is 0.03.
   After 4 seconds, recent_cpu is 12.60, load_avg is 0.07.
   After 6 seconds, recent_cpu is 18.61, load_avg is 0.10.
   After 8 seconds, recent_cpu is 24.44, load_avg is 0.13.
   After 10 seconds, recent_cpu is 30.08, load_avg is 0.15.
   After 12 seconds, recent_cpu is 35.54, load_avg is 0.18.
   After 14 seconds, recent_cpu is 40.83, load_avg is 0.21.
   After 16 seconds, recent_cpu is 45.96, load_avg is 0.24.
   After 18 seconds, recent_cpu is 50.92, load_avg is 0.26.
   After 20 seconds, recent_cpu is 55.73, load_avg is 0.29.
   After 22 seconds, recent_cpu is 60.39, load_avg is 0.31.
   After 24 seconds, recent_cpu is 64.90, load_avg is 0.33.
   After 26 seconds, recent_cpu is 69.27, load_avg is 0.35.
   After 28 seconds, recent_cpu is 73.50, load_avg is 0.38.
   After 30 seconds, recent_cpu is 77.60, load_avg is 0.40.
   After 32 seconds, recent_cpu is 81.56, load_avg is 0.42.
   After 34 seconds, recent_cpu is 85.40, load_avg is 0.44.
   After 36 seconds, recent_cpu is 89.12, load_avg is 0.45.
   After 38 seconds, recent_cpu is 92.72, load_avg is 0.47.
   After 40 seconds, recent_cpu is 96.20, load_avg is 0.49.
   After 42 seconds, recent_cpu is 99.57, load_avg is 0.51.
   After 44 seconds, recent_cpu is 102.84, load_avg is 0.52.
   After 46 seconds, recent_cpu is 106.00, load_avg is 0.54.
   After 48 seconds, recent_cpu is 109.06, load_avg is 0.55.
   After 50 seconds, recent_cpu is 112.02, load_avg is 0.57.
   After 52 seconds, recent_cpu is 114.89, load_avg is 0.58.
   After 54 seconds, recent_cpu is 117.66, load_avg is 0.60.
   After 56 seconds, recent_cpu is 120.34, load_avg is 0.61.
   After 58 seconds, recent_cpu is 122.94, load_avg is 0.62.
   After 60 seconds, recent_cpu is 125.46, load_avg is 0.64.
   After 62 seconds, recent_cpu is 127.89, load_avg is 0.65.
   After 64 seconds, recent_cpu is 130.25, load_avg is 0.66.
   After 66 seconds, recent_cpu is 132.53, load_avg is 0.67.
   After 68 seconds, recent_cpu is 134.73, load_avg is 0.68.
   After 70 seconds, recent_cpu is 136.86, load_avg is 0.69.
   After 72 seconds, recent_cpu is 138.93, load_avg is 0.70.
   After 74 seconds, recent_cpu is 140.93, load_avg is 0.71.
   After 76 seconds, recent_cpu is 142.86, load_avg is 0.72.
   After 78 seconds, recent_cpu is 144.73, load_avg is 0.73.
   After 80 seconds, recent_cpu is 146.54, load_avg is 0.74.
   After 82 seconds, recent_cpu is 148.29, load_avg is 0.75.
   After 84 seconds, recent_cpu is 149.99, load_avg is 0.76.
   After 86 seconds, recent_cpu is 151.63, load_avg is 0.76.
   After 88 seconds, recent_cpu is 153.21, load_avg is 0.77.
   After 90 seconds, recent_cpu is 154.75, load_avg is 0.78.
   After 92 seconds, recent_cpu is 156.23, load_avg is 0.79.
   After 94 seconds, recent_cpu is 157.67, load_avg is 0.79.
   After 96 seconds, recent_cpu is 159.06, load_avg is 0.80.
   After 98 seconds, recent_cpu is 160.40, load_avg is 0.81.
   After 100 seconds, recent_cpu is 161.70, load_avg is 0.81.
   After 102 seconds, recent_cpu is 162.96, load_avg is 0.82.
   After 104 seconds, recent_cpu is 164.18, load_avg is 0.83.
   After 106 seconds, recent_cpu is 165.35, load_avg is 0.83.
   After 108 seconds, recent_cpu is 166.49, load_avg is 0.84.
   After 110 seconds, recent_cpu is 167.59, load_avg is 0.84.
   After 112 seconds, recent_cpu is 168.66, load_avg is 0.85.
   After 114 seconds, recent_cpu is 169.69, load_avg is 0.85.
   After 116 seconds, recent_cpu is 170.69, load_avg is 0.86.
   After 118 seconds, recent_cpu is 171.65, load_avg is 0.86.
   After 120 seconds, recent_cpu is 172.58, load_avg is 0.87.
   After 122 seconds, recent_cpu is 173.49, load_avg is 0.87.
   After 124 seconds, recent_cpu is 174.36, load_avg is 0.88.
   After 126 seconds, recent_cpu is 175.20, load_avg is 0.88.
   After 128 seconds, recent_cpu is 176.02, load_avg is 0.88.
   After 130 seconds, recent_cpu is 176.81, load_avg is 0.89.
   After 132 seconds, recent_cpu is 177.57, load_avg is 0.89.
   After 134 seconds, recent_cpu is 178.31, load_avg is 0.89.
   After 136 seconds, recent_cpu is 179.02, load_avg is 0.90.
   After 138 seconds, recent_cpu is 179.72, load_avg is 0.90.
   After 140 seconds, recent_cpu is 180.38, load_avg is 0.90.
   After 142 seconds, recent_cpu is 181.03, load_avg is 0.91.
   After 144 seconds, recent_cpu is 181.65, load_avg is 0.91.
   After 146 seconds, recent_cpu is 182.26, load_avg is 0.91.
   After 148 seconds, recent_cpu is 182.84, load_avg is 0.92.
   After 150 seconds, recent_cpu is 183.41, load_avg is 0.92.
   After 152 seconds, recent_cpu is 183.96, load_avg is 0.92.
   After 154 seconds, recent_cpu is 184.49, load_avg is 0.92.
   After 156 seconds, recent_cpu is 185.00, load_avg is 0.93.
   After 158 seconds, recent_cpu is 185.49, load_avg is 0.93.
   After 160 seconds, recent_cpu is 185.97, load_avg is 0.93.
   After 162 seconds, recent_cpu is 186.43, load_avg is 0.93.
   After 164 seconds, recent_cpu is 186.88, load_avg is 0.94.
   After 166 seconds, recent_cpu is 187.31, load_avg is 0.94.
   After 168 seconds, recent_cpu is 187.73, load_avg is 0.94.
   After 170 seconds, recent_cpu is 188.14, load_avg is 0.94.
   After 172 seconds, recent_cpu is 188.53, load_avg is 0.94.
   After 174 seconds, recent_cpu is 188.91, load_avg is 0.95.
   After 176 seconds, recent_cpu is 189.27, load_avg is 0.95.
   After 178 seconds, recent_cpu is 189.63, load_avg is 0.95.
   After 180 seconds, recent_cpu is 189.97, load_avg is 0.95.
*/   

#include <stdio.h>
#include "tests/threads/tests.h"
#include "threads/init.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"
#include "devices/timer.h"

/* Sensitive to assumption that recent_cpu updates happen exactly
   when timer_ticks() % TIMER_FREQ == 0. */

void
test_mlfqs_recent_1 (void) 
{
  int64_t start_time;
  int last_elapsed = 0;
  
  ASSERT (thread_mlfqs);

  do 
    {
      msg ("Sleeping 10 seconds to allow recent_cpu to decay, please wait...");
      start_time = timer_ticks ();
      timer_sleep (DIV_ROUND_UP (start_time, TIMER_FREQ) - start_time
                   + 10 * TIMER_FREQ);
    }
  while (thread_get_recent_cpu () > 700);

  start_time = timer_ticks ();
  for (;;) 
    {
      int elapsed = timer_elapsed (start_time);
      if (elapsed % (TIMER_FREQ * 2) == 0 && elapsed > last_elapsed) 
        {
          int recent_cpu = thread_get_recent_cpu ();
          int load_avg = thread_get_load_avg ();
          int elapsed_seconds = elapsed / TIMER_FREQ;
          msg ("After %d seconds, recent_cpu is %d.%02d, load_avg is %d.%02d.",
               elapsed_seconds,
               recent_cpu / 100, recent_cpu % 100,
               load_avg / 100, load_avg % 100);
          if (elapsed_seconds >= 180)
            break;
        } 
      last_elapsed = elapsed;
    }
}
