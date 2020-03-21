#include <ctype.h>
#include <debug.h>
#include <random.h>
#include <stdlib.h>
#include <stdbool.h>

/* Converts a string representation of a signed decimal integer
   in S into an `int', which is returned. */
int
atoi (const char *s) 
{
  bool negative;
  int value;

  ASSERT (s != NULL);

  /* Skip white space. */
  while (isspace ((unsigned char) *s))
    s++;

  /* Parse sign. */
  negative = false;
  if (*s == '+')
    s++;
  else if (*s == '-')
    {
      negative = true;
      s++;
    }

  /* Parse digits.  We always initially parse the value as
     negative, and then make it positive later, because the
     negative range of an int is bigger than the positive range
     on a 2's complement system. */
  for (value = 0; isdigit (*s); s++)
    value = value * 10 - (*s - '0');
  if (!negative)
    value = -value;

  return value;
}

/* Compares A and B by calling the AUX function. */
static int
compare_thunk (const void *a, const void *b, void *aux) 
{
  int (**compare) (const void *, const void *) = aux;
  return (*compare) (a, b);
}

/* Sorts ARRAY, which contains CNT elements of SIZE bytes each,
   using COMPARE.  When COMPARE is passed a pair of elements A
   and B, respectively, it must return a strcmp()-type result,
   i.e. less than zero if A < B, zero if A == B, greater than
   zero if A > B.  Runs in O(n lg n) time and O(1) space in
   CNT. */
void
qsort (void *array, size_t cnt, size_t size,
       int (*compare) (const void *, const void *)) 
{
  sort (array, cnt, size, compare_thunk, &compare);
}

/* Swaps elements with 1-based indexes A_IDX and B_IDX in ARRAY
   with elements of SIZE bytes each. */
static void
do_swap (unsigned char *array, size_t a_idx, size_t b_idx, size_t size)
{
  unsigned char *a = array + (a_idx - 1) * size;
  unsigned char *b = array + (b_idx - 1) * size;
  size_t i;

  for (i = 0; i < size; i++)
    {
      unsigned char t = a[i];
      a[i] = b[i];
      b[i] = t;
    }
}

/* Compares elements with 1-based indexes A_IDX and B_IDX in
   ARRAY with elements of SIZE bytes each, using COMPARE to
   compare elements, passing AUX as auxiliary data, and returns a
   strcmp()-type result. */
static int
do_compare (unsigned char *array, size_t a_idx, size_t b_idx, size_t size,
            int (*compare) (const void *, const void *, void *aux),
            void *aux) 
{
  return compare (array + (a_idx - 1) * size, array + (b_idx - 1) * size, aux);
}

/* "Float down" the element with 1-based index I in ARRAY of CNT
   elements of SIZE bytes each, using COMPARE to compare
   elements, passing AUX as auxiliary data. */
static void
heapify (unsigned char *array, size_t i, size_t cnt, size_t size,
         int (*compare) (const void *, const void *, void *aux),
         void *aux) 
{
  for (;;) 
    {
      /* Set `max' to the index of the largest element among I
         and its children (if any). */
      size_t left = 2 * i;
      size_t right = 2 * i + 1;
      size_t max = i;
      if (left <= cnt && do_compare (array, left, max, size, compare, aux) > 0)
        max = left;
      if (right <= cnt
          && do_compare (array, right, max, size, compare, aux) > 0) 
        max = right;

      /* If the maximum value is already in element I, we're
         done. */
      if (max == i)
        break;

      /* Swap and continue down the heap. */
      do_swap (array, i, max, size);
      i = max;
    }
}

/* Sorts ARRAY, which contains CNT elements of SIZE bytes each,
   using COMPARE to compare elements, passing AUX as auxiliary
   data.  When COMPARE is passed a pair of elements A and B,
   respectively, it must return a strcmp()-type result, i.e. less
   than zero if A < B, zero if A == B, greater than zero if A >
   B.  Runs in O(n lg n) time and O(1) space in CNT. */
void
sort (void *array, size_t cnt, size_t size,
      int (*compare) (const void *, const void *, void *aux),
      void *aux) 
{
  size_t i;

  ASSERT (array != NULL || cnt == 0);
  ASSERT (compare != NULL);
  ASSERT (size > 0);

  /* Build a heap. */
  for (i = cnt / 2; i > 0; i--)
    heapify (array, i, cnt, size, compare, aux);

  /* Sort the heap. */
  for (i = cnt; i > 1; i--) 
    {
      do_swap (array, 1, i, size);
      heapify (array, 1, i - 1, size, compare, aux); 
    }
}

/* Searches ARRAY, which contains CNT elements of SIZE bytes
   each, for the given KEY.  Returns a match is found, otherwise
   a null pointer.  If there are multiple matches, returns an
   arbitrary one of them.

   ARRAY must be sorted in order according to COMPARE.

   Uses COMPARE to compare elements.  When COMPARE is passed a
   pair of elements A and B, respectively, it must return a
   strcmp()-type result, i.e. less than zero if A < B, zero if A
   == B, greater than zero if A > B. */
void *
bsearch (const void *key, const void *array, size_t cnt,
         size_t size, int (*compare) (const void *, const void *)) 
{
  return binary_search (key, array, cnt, size, compare_thunk, &compare);
}

/* Searches ARRAY, which contains CNT elements of SIZE bytes
   each, for the given KEY.  Returns a match is found, otherwise
   a null pointer.  If there are multiple matches, returns an
   arbitrary one of them.

   ARRAY must be sorted in order according to COMPARE.

   Uses COMPARE to compare elements, passing AUX as auxiliary
   data.  When COMPARE is passed a pair of elements A and B,
   respectively, it must return a strcmp()-type result, i.e. less
   than zero if A < B, zero if A == B, greater than zero if A >
   B. */
void *
binary_search (const void *key, const void *array, size_t cnt, size_t size,
               int (*compare) (const void *, const void *, void *aux),
               void *aux) 
{
  const unsigned char *first = array;
  const unsigned char *last = array + size * cnt;

  while (first < last) 
    {
      size_t range = (last - first) / size;
      const unsigned char *middle = first + (range / 2) * size;
      int cmp = compare (key, middle, aux);

      if (cmp < 0) 
        last = middle;
      else if (cmp > 0) 
        first = middle + size;
      else
        return (void *) middle;
    }
  
  return NULL;
}

