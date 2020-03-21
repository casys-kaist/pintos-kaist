/* Test program for printf() in lib/stdio.c.

   Attempts to test printf() functionality that is not
   sufficiently tested elsewhere in Pintos.

   This is not a test we will run on your submitted projects.
   It is here for completeness.
*/

#undef NDEBUG
#include <limits.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "threads/test.h"

/* Number of failures so far. */
static int failure_cnt;

static void
checkf (const char *expect, const char *format, ...) 
{
  char output[128];
  va_list args;

  printf ("\"%s\" -> \"%s\": ", format, expect);
  
  va_start (args, format);
  vsnprintf (output, sizeof output, format, args);
  va_end (args);

  if (strcmp (expect, output)) 
    {
      printf ("\nFAIL: actual output \"%s\"\n", output);
      failure_cnt++;
    }
  else
    printf ("okay\n");
}

/* Test printf() implementation. */
void
test (void) 
{
  printf ("Testing formats:");

  /* Check that commas show up in the right places, for positive
     numbers. */
  checkf ("1", "%'d", 1);
  checkf ("12", "%'d", 12);
  checkf ("123", "%'d", 123);
  checkf ("1,234", "%'d", 1234);
  checkf ("12,345", "%'d", 12345);
  checkf ("123,456", "%'ld", 123456L);
  checkf ("1,234,567", "%'ld", 1234567L);
  checkf ("12,345,678", "%'ld", 12345678L);
  checkf ("123,456,789", "%'ld", 123456789L);
  checkf ("1,234,567,890", "%'ld", 1234567890L);
  checkf ("12,345,678,901", "%'lld", 12345678901LL);
  checkf ("123,456,789,012", "%'lld", 123456789012LL);
  checkf ("1,234,567,890,123", "%'lld", 1234567890123LL);
  checkf ("12,345,678,901,234", "%'lld", 12345678901234LL);
  checkf ("123,456,789,012,345", "%'lld", 123456789012345LL);
  checkf ("1,234,567,890,123,456", "%'lld", 1234567890123456LL);
  checkf ("12,345,678,901,234,567", "%'lld", 12345678901234567LL);
  checkf ("123,456,789,012,345,678", "%'lld", 123456789012345678LL);
  checkf ("1,234,567,890,123,456,789", "%'lld", 1234567890123456789LL);

  /* Check that commas show up in the right places, for positive
     numbers. */
  checkf ("-1", "%'d", -1);
  checkf ("-12", "%'d", -12);
  checkf ("-123", "%'d", -123);
  checkf ("-1,234", "%'d", -1234);
  checkf ("-12,345", "%'d", -12345);
  checkf ("-123,456", "%'ld", -123456L);
  checkf ("-1,234,567", "%'ld", -1234567L);
  checkf ("-12,345,678", "%'ld", -12345678L);
  checkf ("-123,456,789", "%'ld", -123456789L);
  checkf ("-1,234,567,890", "%'ld", -1234567890L);
  checkf ("-12,345,678,901", "%'lld", -12345678901LL);
  checkf ("-123,456,789,012", "%'lld", -123456789012LL);
  checkf ("-1,234,567,890,123", "%'lld", -1234567890123LL);
  checkf ("-12,345,678,901,234", "%'lld", -12345678901234LL);
  checkf ("-123,456,789,012,345", "%'lld", -123456789012345LL);
  checkf ("-1,234,567,890,123,456", "%'lld", -1234567890123456LL);
  checkf ("-12,345,678,901,234,567", "%'lld", -12345678901234567LL);
  checkf ("-123,456,789,012,345,678", "%'lld", -123456789012345678LL);
  checkf ("-1,234,567,890,123,456,789", "%'lld", -1234567890123456789LL);
  
  /* Check signed integer conversions. */
  checkf ("    0", "%5d", 0);
  checkf ("0    ", "%-5d", 0);
  checkf ("   +0", "%+5d", 0);
  checkf ("+0   ", "%+-5d", 0);
  checkf ("    0", "% 5d", 0);
  checkf ("00000", "%05d", 0);
  checkf ("     ", "%5.0d", 0);
  checkf ("   00", "%5.2d", 0);
  checkf ("0", "%d", 0);

  checkf ("    1", "%5d", 1);
  checkf ("1    ", "%-5d", 1);
  checkf ("   +1", "%+5d", 1);
  checkf ("+1   ", "%+-5d", 1);
  checkf ("    1", "% 5d", 1);
  checkf ("00001", "%05d", 1);
  checkf ("    1", "%5.0d", 1);
  checkf ("   01", "%5.2d", 1);
  checkf ("1", "%d", 1);

  checkf ("   -1", "%5d", -1);
  checkf ("-1   ", "%-5d", -1);
  checkf ("   -1", "%+5d", -1);
  checkf ("-1   ", "%+-5d", -1);
  checkf ("   -1", "% 5d", -1);
  checkf ("-0001", "%05d", -1);
  checkf ("   -1", "%5.0d", -1);
  checkf ("  -01", "%5.2d", -1);
  checkf ("-1", "%d", -1);

  checkf ("12345", "%5d", 12345);
  checkf ("12345", "%-5d", 12345);
  checkf ("+12345", "%+5d", 12345);
  checkf ("+12345", "%+-5d", 12345);
  checkf (" 12345", "% 5d", 12345);
  checkf ("12345", "%05d", 12345);
  checkf ("12345", "%5.0d", 12345);
  checkf ("12345", "%5.2d", 12345);
  checkf ("12345", "%d", 12345);

  checkf ("123456", "%5d", 123456);
  checkf ("123456", "%-5d", 123456);
  checkf ("+123456", "%+5d", 123456);
  checkf ("+123456", "%+-5d", 123456);
  checkf (" 123456", "% 5d", 123456);
  checkf ("123456", "%05d", 123456);
  checkf ("123456", "%5.0d", 123456);
  checkf ("123456", "%5.2d", 123456);
  checkf ("123456", "%d", 123456);

  /* Check unsigned integer conversions. */
  checkf ("    0", "%5u", 0);
  checkf ("    0", "%5o", 0);
  checkf ("    0", "%5x", 0);
  checkf ("    0", "%5X", 0);
  checkf ("    0", "%#5o", 0);
  checkf ("    0", "%#5x", 0);
  checkf ("    0", "%#5X", 0);
  checkf ("  00000000", "%#10.8x", 0);
  
  checkf ("    1", "%5u", 1);
  checkf ("    1", "%5o", 1);
  checkf ("    1", "%5x", 1);
  checkf ("    1", "%5X", 1);
  checkf ("   01", "%#5o", 1);
  checkf ("  0x1", "%#5x", 1);
  checkf ("  0X1", "%#5X", 1);
  checkf ("0x00000001", "%#10.8x", 1);

  checkf ("123456", "%5u", 123456);
  checkf ("361100", "%5o", 123456);
  checkf ("1e240", "%5x", 123456);
  checkf ("1E240", "%5X", 123456);
  checkf ("0361100", "%#5o", 123456);
  checkf ("0x1e240", "%#5x", 123456);
  checkf ("0X1E240", "%#5X", 123456);
  checkf ("0x0001e240", "%#10.8x", 123456);

  /* Character and string conversions. */
  checkf ("foobar", "%c%c%c%c%c%c", 'f', 'o', 'o', 'b', 'a', 'r');
  checkf ("  left-right  ", "%6s%s%-7s", "left", "-", "right");
  checkf ("trim", "%.4s", "trimoff");
  checkf ("%%", "%%%%");

  /* From Cristian Cadar's automatic test case generator. */
  checkf (" abcdefgh", "%9s", "abcdefgh");
  checkf ("36657730000", "%- o", (unsigned) 036657730000);
  checkf ("4139757568", "%- u", (unsigned) 4139757568UL);
  checkf ("f6bfb000", "%- x", (unsigned) 0xf6bfb000);
  checkf ("36657730000", "%-to", (ptrdiff_t) 036657730000);
  checkf ("4139757568", "%-tu", (ptrdiff_t) 4139757568UL);
  checkf ("-155209728", "%-zi", (size_t) -155209728);
  checkf ("-155209728", "%-zd", (size_t) -155209728);
  checkf ("036657730000", "%+#o", (unsigned) 036657730000);
  checkf ("0xf6bfb000", "%+#x", (unsigned) 0xf6bfb000);
  checkf ("-155209728", "% zi", (size_t) -155209728);
  checkf ("-155209728", "% zd", (size_t) -155209728);
  checkf ("4139757568", "% tu", (ptrdiff_t) 4139757568UL);
  checkf ("036657730000", "% #o", (unsigned) 036657730000);
  checkf ("0xf6bfb000", "% #x", (unsigned) 0xf6bfb000);
  checkf ("0xf6bfb000", "%# x", (unsigned) 0xf6bfb000);
  checkf ("-155209728", "%#zd", (size_t) -155209728);
  checkf ("-155209728", "%0zi", (size_t) -155209728);
  checkf ("4,139,757,568", "%'tu", (ptrdiff_t) 4139757568UL);
  checkf ("-155,209,728", "%-'d", -155209728);
  checkf ("-155209728", "%.zi", (size_t) -155209728);
  checkf ("-155209728", "%zi", (size_t) -155209728);
  checkf ("-155209728", "%zd", (size_t) -155209728);
  checkf ("-155209728", "%+zi", (size_t) -155209728);

  if (failure_cnt == 0)
    printf ("\nstdio: PASS\n");
  else
    printf ("\nstdio: FAIL: %d tests failed\n", failure_cnt);
}                                                                  
