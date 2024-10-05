OUTPUT_FORMAT("elf64-x86-64")
OUTPUT_ARCH(i386:x86-64)
ENTRY(_start)
SECTIONS
{
 . = 0x8004000000 + 0x200000;
 PROVIDE(start = .);
 .text : AT(0x200000) {
  *(.entry)
  *(.text .text.* .stub .gnu.linkonce.t.*)
 } = 0x90
 .rodata : { *(.rodata .rodata.* .gnu.linkonce.r.*) }
 . = ALIGN(0x1000);
 PROVIDE(_end_kernel_text = .);
  .data : { *(.data) *(.data.*)}
  PROVIDE(_start_bss = .);
  .bss : { *(.bss) }
  PROVIDE(_end_bss = .);
  PROVIDE(_end = .);
 /DISCARD/ : {
  *(.eh_frame .note.GNU-stack .stab)
 }
}
