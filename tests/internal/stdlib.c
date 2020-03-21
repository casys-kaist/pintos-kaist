/* Test program for sorting and searching in lib/stdlib.c.

   Attempts to test the sorting and searching functionality that
   is not sufficiently tested elsewhere in Pintos.

   This is not a test we will run on your submitted projects.
   It is here for completeness.
*/

#undef NDEBUG
#include <debug.h>
#include <limits.h>
#include <random.h>
#include <stdlib.h>
#include <stdio.h>
#include "threads/test.h"

/* Maximum number of elements in an array that we will test. */
#define MAX_CNT 4096

static void shuffle (int[], size_t);
static int compare_ints (const void *, const void *);
static void verify_order (const int[], size_t);
static void verify_bsearch (const int[], size_t);

/* Test sorting and searching implementations. */
void
test (void) 
{
  int cnt;

  printf ("testing various size arrays:");
  for (cnt = 0; cnt < MAX_CNT; cnt = cnt * 4 / 3 + 1)
    {
      int repeat;

      printf (" %zu", cnt);
      for (repeat = 0; repeat < 10; repeat++) 
        {
          static int values[MAX_CNT];
          int i;

          /* Put values 0...CNT in random order in VALUES. */
          for (i = 0; i < cnt; i++)
            values[i] = i;
          shuffle (values, cnt);
  
          /* Sort VALUES, then verify ordering. */
          qsort (values, cnt, sizeof *values, compare_ints);
          verify_order (values, cnt);
          verify_bsearch (values, cnt);
        }
    }
  
  printf (" done\n");
  printf ("stdlib: PASS\n");
}

/* Shuffles the CNT elements in ARRAY into random order. */
static void
shuffle (int *array, size_t cnt) 
{
  size_t i;

  for (i = 0; i < cnt; i++)
    {
      size_t j = i + random_ulong () % (cnt - i);
      int t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
}

/* Returns 1 if *A is greater than *B,
   0 if *A equals *B,
   -1 if *A is less than *B. */
static int
compare_ints (const void *a_, const void *b_) 
{
  const int *a = a_;
  const int *b = b_;

  return *a < *b ? -1 : *a > *b;
}

/* Verifies that ARRAY contains the CNT ints 0...CNT-1. */
static void
verify_order (const int *array, size_t cnt) 
{
  int i;

  for (i = 0; (size_t) i < cnt; i++) 
    ASSERT (array[i] == i);
}

/* Checks that bsearch() works properly in ARRAY.  ARRAY must
   contain the values 0...CNT-1. */
static void
verify_bsearch (const int *array, size_t cnt) 
{
  int not_in_array[] = {0, -1, INT_MAX, MAX_CNT, MAX_CNT + 1, MAX_CNT * 2};
  int i;

  /* Check that all the values in the array are found properly. */
  for (i = 0; (size_t) i < cnt; i++) 
    ASSERT (bsearch (&i, array, cnt, sizeof *array, compare_ints)
            == array + i);

  /* Check that some values not in the array are not found. */
  not_in_array[0] = cnt;
  for (i = 0; (size_t) i < sizeof not_in_array / sizeof *not_in_array; i++) 
    ASSERT (bsearch (&not_in_array[i], array, cnt, sizeof *array, compare_ints)
            == NULL);
}
