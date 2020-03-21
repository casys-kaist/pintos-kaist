#include <debug.h>
#include <console.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "threads/init.h"
#include "threads/interrupt.h"
#include "devices/serial.h"

/* Halts the OS, printing the source file name, line number, and
   function name, plus a user-specific message. */
void
debug_panic (const char *file, int line, const char *function,
		const char *message, ...) {
	static int level;
	va_list args;

	intr_disable ();
	console_panic ();

	level++;
	if (level == 1) {
		printf ("Kernel PANIC at %s:%d in %s(): ", file, line, function);

		va_start (args, message);
		vprintf (message, args);
		printf ("\n");
		va_end (args);

		debug_backtrace ();
	} else if (level == 2)
		printf ("Kernel PANIC recursion at %s:%d in %s().\n",
				file, line, function);
	else {
		/* Don't print anything: that's probably why we recursed. */
	}

	serial_flush ();
	if (power_off_when_done)
		power_off ();
	for (;;);
}
