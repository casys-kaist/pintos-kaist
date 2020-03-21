#ifndef __LIB_STDLIB_H
#define __LIB_STDLIB_H

#include <stddef.h>

/* Standard functions. */
int atoi (const char *);
void qsort (void *array, size_t cnt, size_t size,
		int (*compare) (const void *, const void *));
void *bsearch (const void *key, const void *array, size_t cnt,
		size_t size, int (*compare) (const void *, const void *));

/* Nonstandard functions. */
void sort (void *array, size_t cnt, size_t size,
		int (*compare) (const void *, const void *, void *aux),
		void *aux);
void *binary_search (const void *key, const void *array, size_t cnt,
		size_t size,
		int (*compare) (const void *, const void *, void *aux),
		void *aux);

#endif /* lib/stdlib.h */
