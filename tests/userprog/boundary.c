/* Utility function for tests that try to break system calls by
   passing them data that crosses from one virtual page to
   another. */

#include <inttypes.h>
#include <round.h>
#include <string.h>
#include "tests/userprog/boundary.h"

static char dst[8192];

/* Returns the beginning of a page.  There are at least 2048
   modifiable bytes on either side of the pointer returned. */
void *
get_boundary_area (void) 
{
  char *p = (char *) ROUND_UP ((uintptr_t) dst, 4096);
  if (p - dst < 2048)
    p += 4096;
  return p;
}

/* Returns a copy of SRC split across the boundary between two
   pages. */
char *
copy_string_across_boundary (const char *src) 
{
  char *p = get_boundary_area ();
  p -= strlen (src) < 4096 ? strlen (src) / 2 : 4096;
  strlcpy (p, src, 4096);
  return p;
}

