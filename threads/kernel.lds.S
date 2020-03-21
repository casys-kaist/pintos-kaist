#include "threads/loader.h"

OUTPUT_FORMAT("elf64-x86-64")
OUTPUT_ARCH(i386:x86-64)
ENTRY(_start)			/* Kernel starts at "start" symbol. */

SECTIONS
{
  /* Specifies the virtual address for the kernel base. */
	. = LOADER_KERN_BASE + LOADER_PHYS_BASE;

	PROVIDE(start = .);
  /* Kernel starts with code, followed by read-only data and writable data. */
	.text : AT(LOADER_PHYS_BASE) {
		*(.entry)
		*(.text .text.* .stub .gnu.linkonce.t.*)
	} = 0x90
	.rodata         : { *(.rodata .rodata.* .gnu.linkonce.r.*) }

	. = ALIGN(0x1000);
	PROVIDE(_end_kernel_text = .);

  .data : { *(.data) *(.data.*)}

  /* BSS (zero-initialized data) is after everything else. */
  PROVIDE(_start_bss = .);
  .bss : { *(.bss) }
  PROVIDE(_end_bss = .);

  PROVIDE(_end = .);

	/DISCARD/ : {
		*(.eh_frame .note.GNU-stack .stab)
	}
}
