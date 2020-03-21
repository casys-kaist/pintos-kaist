#ifndef __LIB_ROUND_H
#define __LIB_ROUND_H

/* Yields X rounded up to the nearest multiple of STEP.
 * For X >= 0, STEP >= 1 only. */
#define ROUND_UP(X, STEP) (((X) + (STEP) - 1) / (STEP) * (STEP))

/* Yields X divided by STEP, rounded up.
 * For X >= 0, STEP >= 1 only. */
#define DIV_ROUND_UP(X, STEP) (((X) + (STEP) - 1) / (STEP))

/* Yields X rounded down to the nearest multiple of STEP.
 * For X >= 0, STEP >= 1 only. */
#define ROUND_DOWN(X, STEP) ((X) / (STEP) * (STEP))

/* There is no DIV_ROUND_DOWN.   It would be simply X / STEP. */

#endif /* lib/round.h */
