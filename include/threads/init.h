#ifndef THREADS_INIT_H
#define THREADS_INIT_H

#include <debug.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* Physical memory size, in 4 kB pages. */
extern size_t ram_pages;

/* Page map level 4 with kernel mappings only. */
extern uint64_t *base_pml4;

/* -q: Power off when kernel tasks complete? */
extern bool power_off_when_done;

void power_off (void) NO_RETURN;

#endif /* threads/init.h */
