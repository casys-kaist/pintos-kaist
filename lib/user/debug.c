#include <debug.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <syscall.h>

/* Aborts the user program, printing the source file name, line
   number, and function name, plus a user-specific message. */
void
debug_panic (const char *file, int line, const char *function,
		const char *message, ...) {
	va_list args;

	printf ("User process ABORT at %s:%d in %s(): ", file, line, function);

	va_start (args, message);
	vprintf (message, args);
	printf ("\n");
	va_end (args);

	debug_backtrace ();

	exit (1);
}
