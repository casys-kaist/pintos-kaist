#include "devices/intq.h"
#include <debug.h>
#include "threads/thread.h"

static int next (int pos);
static void wait (struct intq *q, struct thread **waiter);
static void signal (struct intq *q, struct thread **waiter);

/* Initializes interrupt queue Q. */
void
intq_init (struct intq *q) {
	lock_init (&q->lock);
	q->not_full = q->not_empty = NULL;
	q->head = q->tail = 0;
}

/* Returns true if Q is empty, false otherwise. */
bool
intq_empty (const struct intq *q) {
	ASSERT (intr_get_level () == INTR_OFF);
	return q->head == q->tail;
}

/* Returns true if Q is full, false otherwise. */
bool
intq_full (const struct intq *q) {
	ASSERT (intr_get_level () == INTR_OFF);
	return next (q->head) == q->tail;
}

/* Removes a byte from Q and returns it.
   Q must not be empty if called from an interrupt handler.
   Otherwise, if Q is empty, first sleeps until a byte is
   added. */
uint8_t
intq_getc (struct intq *q) {
	uint8_t byte;

	ASSERT (intr_get_level () == INTR_OFF);
	while (intq_empty (q)) {
		ASSERT (!intr_context ());
		lock_acquire (&q->lock);
		wait (q, &q->not_empty);
		lock_release (&q->lock);
	}

	byte = q->buf[q->tail];
	q->tail = next (q->tail);
	signal (q, &q->not_full);
	return byte;
}

/* Adds BYTE to the end of Q.
   Q must not be full if called from an interrupt handler.
   Otherwise, if Q is full, first sleeps until a byte is
   removed. */
void
intq_putc (struct intq *q, uint8_t byte) {
	ASSERT (intr_get_level () == INTR_OFF);
	while (intq_full (q)) {
		ASSERT (!intr_context ());
		lock_acquire (&q->lock);
		wait (q, &q->not_full);
		lock_release (&q->lock);
	}

	q->buf[q->head] = byte;
	q->head = next (q->head);
	signal (q, &q->not_empty);
}

/* Returns the position after POS within an intq. */
static int
next (int pos) {
	return (pos + 1) % INTQ_BUFSIZE;
}

/* WAITER must be the address of Q's not_empty or not_full
   member.  Waits until the given condition is true. */
static void
wait (struct intq *q UNUSED, struct thread **waiter) {
	ASSERT (!intr_context ());
	ASSERT (intr_get_level () == INTR_OFF);
	ASSERT ((waiter == &q->not_empty && intq_empty (q))
			|| (waiter == &q->not_full && intq_full (q)));

	*waiter = thread_current ();
	thread_block ();
}

/* WAITER must be the address of Q's not_empty or not_full
   member, and the associated condition must be true.  If a
   thread is waiting for the condition, wakes it up and resets
   the waiting thread. */
static void
signal (struct intq *q UNUSED, struct thread **waiter) {
	ASSERT (intr_get_level () == INTR_OFF);
	ASSERT ((waiter == &q->not_empty && !intq_empty (q))
			|| (waiter == &q->not_full && !intq_full (q)));

	if (*waiter != NULL) {
		thread_unblock (*waiter);
		*waiter = NULL;
	}
}
