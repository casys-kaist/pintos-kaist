#include <stdint.h>
#include "tests/arc4.h"

/* Swap bytes. */
static inline void
swap_byte (uint8_t *a, uint8_t *b)
{
  uint8_t t = *a;
  *a = *b;
  *b = t;
}

void
arc4_init (struct arc4 *arc4, const void *key_, size_t size)
{
  const uint8_t *key = key_;
  size_t key_idx;
  uint8_t *s;
  int i, j;

  s = arc4->s;
  arc4->i = arc4->j = 0;
  for (i = 0; i < 256; i++)
    s[i] = i;
  for (key_idx = 0, i = j = 0; i < 256; i++)
    {
      j = (j + s[i] + key[key_idx]) & 255;
      swap_byte (s + i, s + j);
      if (++key_idx >= size)
        key_idx = 0;
    }
}

void
arc4_crypt (struct arc4 *arc4, void *buf_, size_t size)
{
  uint8_t *buf = buf_;
  uint8_t *s;
  uint8_t i, j;

  s = arc4->s;
  i = arc4->i;
  j = arc4->j;
  while (size-- > 0)
    {
      i += 1;
      j += s[i];
      swap_byte (s + i, s + j);
      *buf++ ^= s[(s[i] + s[j]) & 255];
    }
  arc4->i = i;
  arc4->j = j;
}
