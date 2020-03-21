#ifndef DEVICES_INTQ_H
#define DEVICES_INTQ_H

#include "threads/interrupt.h"
#include "threads/synch.h"

/* An "interrupt queue", a circular buffer shared between
   kernel threads and external interrupt handlers.

   Interrupt queue functions can be called from kernel threads or
   from external interrupt handlers.  Except for intq_init(),
   interrupts must be off in either case.

   The interrupt queue has the structure of a "monitor".  Locks
   and condition variables from threads/synch.h cannot be used in
   this case, as they normally would, because they can only
   protect kernel threads from one another, not from interrupt
   handlers. */

/* Queue buffer size, in bytes. */
#define INTQ_BUFSIZE 64

/* A circular queue of bytes. */
struct intq {
	/* Waiting threads. */
	struct lock lock;           /* Only one thread may wait at once. */
	struct thread *not_full;    /* Thread waiting for not-full condition. */
	struct thread *not_empty;   /* Thread waiting for not-empty condition. */

	/* Queue. */
	uint8_t buf[INTQ_BUFSIZE];  /* Buffer. */
	int head;                   /* New data is written here. */
	int tail;                   /* Old data is read here. */
};

void intq_init (struct intq *);
bool intq_empty (const struct intq *);
bool intq_full (const struct intq *);
uint8_t intq_getc (struct intq *);
void intq_putc (struct intq *, uint8_t);

#endif /* devices/intq.h */
