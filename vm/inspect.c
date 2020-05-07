/* inspect.c: Testing utility for VM. */
/* DO NOT MODIFY THIS FILE. */

#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/mmu.h"
#include "vm/inspect.h"

static void
inspect (struct intr_frame *f) {
	const void *va = (const void *) f->R.rax;
	f->R.rax = PTE_ADDR (pml4_get_page (thread_current ()->pml4, va));
}

/* Tool for testing vm component. Calling this function via int 0x42.
 * Input:
 *   @RAX - Virtual address to inspect
 * Output:
 *   @RAX - Physical address that mmaped to input. */
void
register_inspect_intr (void) {
	intr_register_int (0x42, 3, INTR_OFF, inspect, "Inspect Virtual Memory");
}
