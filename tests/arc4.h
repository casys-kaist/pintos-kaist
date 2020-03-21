#ifndef TESTS_ARC4_H
#define TESTS_ARC4_H

#include <stddef.h>
#include <stdint.h>

/* Alleged RC4 algorithm encryption state. */
struct arc4
  {
    uint8_t s[256];
    uint8_t i, j;
  };

void arc4_init (struct arc4 *, const void *, size_t);
void arc4_crypt (struct arc4 *, void *, size_t);

#endif /* tests/arc4.h */
