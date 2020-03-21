#include "random.h"
#include <stdbool.h>
#include <stdint.h>
#include "debug.h"

/* RC4-based pseudo-random number generator (PRNG).

   RC4 is a stream cipher.  We're not using it here for its
   cryptographic properties, but because it is easy to implement
   and its output is plenty random for non-cryptographic
   purposes.

   See http://en.wikipedia.org/wiki/RC4_(cipher) for information
   on RC4.*/

/* RC4 state. */
static uint8_t s[256];          /* S[]. */
static uint8_t s_i, s_j;        /* i, j. */

/* Already initialized? */
static bool inited;     

/* Swaps the bytes pointed to by A and B. */
static inline void
swap_byte (uint8_t *a, uint8_t *b) {
	uint8_t t = *a;
	*a = *b;
	*b = t;
}

/* Initializes or reinitializes the PRNG with the given SEED. */
void
random_init (unsigned seed) {
	uint8_t *seedp = (uint8_t *) &seed;
	int i;
	uint8_t j;

	for (i = 0; i < 256; i++) 
		s[i] = i;
	for (i = j = 0; i < 256; i++) {
		j += s[i] + seedp[i % sizeof seed];
		swap_byte (s + i, s + j);
	}

	s_i = s_j = 0;
	inited = true;
}

/* Writes SIZE random bytes into BUF. */
void
random_bytes (void *buf_, size_t size) {
	uint8_t *buf;

	if (!inited)
		random_init (0);

	for (buf = buf_; size-- > 0; buf++) {
		uint8_t s_k;

		s_i++;
		s_j += s[s_i];
		swap_byte (s + s_i, s + s_j);

		s_k = s[s_i] + s[s_j];
		*buf = s[s_k];
	}
}

/* Returns a pseudo-random unsigned long.
   Use random_ulong() % n to obtain a random number in the range
   0...n (exclusive). */
unsigned long
random_ulong (void) {
	unsigned long ul;
	random_bytes (&ul, sizeof ul);
	return ul;
}
