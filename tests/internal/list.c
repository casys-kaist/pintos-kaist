/* Test program for lib/kernel/list.c.

   Attempts to test the list functionality that is not
   sufficiently tested elsewhere in Pintos.

   This is not a test we will run on your submitted projects.
   It is here for completeness.
*/

#undef NDEBUG
#include <debug.h>
#include <list.h>
#include <random.h>
#include <stdio.h>
#include "threads/test.h"

/* Maximum number of elements in a linked list that we will
   test. */
#define MAX_SIZE 64

/* A linked list element. */
struct value 
  {
    struct list_elem elem;      /* List element. */
    int value;                  /* Item value. */
  };

static void shuffle (struct value[], size_t);
static bool value_less (const struct list_elem *, const struct list_elem *,
                        void *);
static void verify_list_fwd (struct list *, int size);
static void verify_list_bkwd (struct list *, int size);

/* Test the linked list implementation. */
void
test (void) 
{
  int size;

  printf ("testing various size lists:");
  for (size = 0; size < MAX_SIZE; size++) 
    {
      int repeat;

      printf (" %d", size);
      for (repeat = 0; repeat < 10; repeat++) 
        {
          static struct value values[MAX_SIZE * 4];
          struct list list;
          struct list_elem *e;
          int i, ofs;

          /* Put values 0...SIZE in random order in VALUES. */
          for (i = 0; i < size; i++)
            values[i].value = i;
          shuffle (values, size);
  
          /* Assemble list. */
          list_init (&list);
          for (i = 0; i < size; i++)
            list_push_back (&list, &values[i].elem);

          /* Verify correct minimum and maximum elements. */
          e = list_min (&list, value_less, NULL);
          ASSERT (size ? list_entry (e, struct value, elem)->value == 0
                  : e == list_begin (&list));
          e = list_max (&list, value_less, NULL);
          ASSERT (size ? list_entry (e, struct value, elem)->value == size - 1
                  : e == list_begin (&list));

          /* Sort and verify list. */
          list_sort (&list, value_less, NULL);
          verify_list_fwd (&list, size);

          /* Reverse and verify list. */
          list_reverse (&list);
          verify_list_bkwd (&list, size);

          /* Shuffle, insert using list_insert_ordered(),
             and verify ordering. */
          shuffle (values, size);
          list_init (&list);
          for (i = 0; i < size; i++)
            list_insert_ordered (&list, &values[i].elem,
                                 value_less, NULL);
          verify_list_fwd (&list, size);

          /* Duplicate some items, uniquify, and verify. */
          ofs = size;
          for (e = list_begin (&list); e != list_end (&list);
               e = list_next (e))
            {
              struct value *v = list_entry (e, struct value, elem);
              int copies = random_ulong () % 4;
              while (copies-- > 0) 
                {
                  values[ofs].value = v->value;
                  list_insert (e, &values[ofs++].elem);
                }
            }
          ASSERT ((size_t) ofs < sizeof values / sizeof *values);
          list_unique (&list, NULL, value_less, NULL);
          verify_list_fwd (&list, size);
        }
    }
  
  printf (" done\n");
  printf ("list: PASS\n");
}

/* Shuffles the CNT elements in ARRAY into random order. */
static void
shuffle (struct value *array, size_t cnt) 
{
  size_t i;

  for (i = 0; i < cnt; i++)
    {
      size_t j = i + random_ulong () % (cnt - i);
      struct value t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
}

/* Returns true if value A is less than value B, false
   otherwise. */
static bool
value_less (const struct list_elem *a_, const struct list_elem *b_,
            void *aux UNUSED) 
{
  const struct value *a = list_entry (a_, struct value, elem);
  const struct value *b = list_entry (b_, struct value, elem);
  
  return a->value < b->value;
}

/* Verifies that LIST contains the values 0...SIZE when traversed
   in forward order. */
static void
verify_list_fwd (struct list *list, int size) 
{
  struct list_elem *e;
  int i;
  
  for (i = 0, e = list_begin (list);
       i < size && e != list_end (list);
       i++, e = list_next (e)) 
    {
      struct value *v = list_entry (e, struct value, elem);
      ASSERT (i == v->value);
    }
  ASSERT (i == size);
  ASSERT (e == list_end (list));
}

/* Verifies that LIST contains the values 0...SIZE when traversed
   in reverse order. */
static void
verify_list_bkwd (struct list *list, int size) 
{
  struct list_elem *e;
  int i;

  for (i = 0, e = list_rbegin (list);
       i < size && e != list_rend (list);
       i++, e = list_prev (e)) 
    {
      struct value *v = list_entry (e, struct value, elem);
      ASSERT (i == v->value);
    }
  ASSERT (i == size);
  ASSERT (e == list_rend (list));
}
