/* Verifies that a single busy thread raises the load average to
   0.5 in 38 to 45 seconds.  The expected time is 42 seconds, as
   you can verify:
   perl -e '$i++,$a=(59*$a+1)/60while$a<=.5;print "$i\n"'

   Then, verifies that 10 seconds of inactivity drop the load
   average back below 0.5 again. */

#include <stdio.h>
#include "tests/threads/tests.h"
#include "threads/init.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"
#include "devices/timer.h"

void
test_mlfqs_load_1 (void) 
{
  int64_t start_time;
  int elapsed;
  int load_avg;
  
  ASSERT (thread_mlfqs);

  msg ("spinning for up to 45 seconds, please wait...");

  start_time = timer_ticks ();
  for (;;) 
    {
      load_avg = thread_get_load_avg ();
      ASSERT (load_avg >= 0);
      elapsed = timer_elapsed (start_time) / TIMER_FREQ;
      if (load_avg > 100)
        fail ("load average is %d.%02d "
              "but should be between 0 and 1 (after %d seconds)",
              load_avg / 100, load_avg % 100, elapsed);
      else if (load_avg > 50)
        break;
      else if (elapsed > 45)
        fail ("load average stayed below 0.5 for more than 45 seconds");
    }

  if (elapsed < 38)
    fail ("load average took only %d seconds to rise above 0.5", elapsed);
  msg ("load average rose to 0.5 after %d seconds", elapsed);

  msg ("sleeping for another 10 seconds, please wait...");
  timer_sleep (TIMER_FREQ * 10);

  load_avg = thread_get_load_avg ();
  if (load_avg < 0)
    fail ("load average fell below 0");
  if (load_avg > 50)
    fail ("load average stayed above 0.5 for more than 10 seconds");
  msg ("load average fell back below 0.5 (to %d.%02d)",
       load_avg / 100, load_avg % 100);

  pass ();
}
