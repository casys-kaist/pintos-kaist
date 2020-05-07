/* Child process of page-parallel.
   Encrypts 1 MB of zeros, then decrypts it, and ensures that
   the zeros are back. */

#include <string.h>
#include "tests/arc4.h"
#include "tests/lib.h"
#include "tests/main.h"

const char *test_name = "child-linear";

#define SIZE (1024 * 1024)
static char buf[SIZE];

int
main (int argc, char *argv[])
{
  const char *key = argv[argc - 1];
  struct arc4 arc4;
  size_t i;

  /* Encrypt zeros. */
  arc4_init (&arc4, key, strlen (key));
  arc4_crypt (&arc4, buf, SIZE);

  /* Decrypt back to zeros. */
  arc4_init (&arc4, key, strlen (key));
  arc4_crypt (&arc4, buf, SIZE);

  /* Check that it's all zeros. */
  for (i = 0; i < SIZE; i++)
    if (buf[i] != '\0')
      fail ("byte %zu != 0", i);

  return 0x42;
}
