#include "threads/loader.h"
#define LONG_MODE (1 << 29)
#define CR0_PE 0x00000001
#define CR0_PG (1 << 31)
#define CR4_PAE 0x20
#define PTE_P 0x1
#define PTE_W 0x2
#define EFER_MSR 0xC0000080
#define EFER_LME (1 << 8)
#define EFER_SCE (1 << 0)
#define RELOC(x) (x - LOADER_KERN_BASE)
.section .entry

.globl _start
_start = RELOC(bootstrap)

.globl bootstrap
.func bootstrap
.code32
#### bootstrap to the 64bit code.
bootstrap:
	pushf
	pop %eax
	mov %ecx, %eax
	xor $0x200000, %eax
	push %eax
	popf
	cmp %eax, %ebx
	jz no_long_mode # Check cpuid instruction exist.
	xor %eax, %eax
	cpuid           # query cpuid 1.
	cmp $1, %eax
	jb no_long_mode
	test $LONG_MODE, %edx
#### Enable Physical Address Extension
	movl %cr4, %eax
	orl $CR4_PAE, %eax
	movl %eax, %cr4


#### Create page directory and page table and
#### set page directory base register (cr3).
setup_page_table:
# 1. fill boot_pml4e with zeros
  lea (RELOC(boot_pml4e)), %edi
	xor %eax, %eax
	mov $0x400, %ecx
	rep stosl (%edi)

# 2. set pdpts
  lea (RELOC(boot_pml4e)), %edi
	lea (RELOC(boot_pdpt1)), %ebx
	orl $(PTE_P | PTE_W), %ebx
	mov %ebx, (%edi) # pdpt1
	lea (RELOC(boot_pdpt2)), %ebx
	orl $(PTE_P | PTE_W), %ebx
	mov %ebx, 8(%edi) # pdpt2

# 3. set pdpes
  lea (RELOC(boot_pdpt1)), %edi
	lea (RELOC(boot_pde1)), %ebx
	orl $(PTE_P | PTE_W), %ebx
	mov %ebx, (%edi)

  lea (RELOC(boot_pdpt2)), %edi
	lea (RELOC(boot_pde2)), %ebx
	orl $(PTE_P | PTE_W), %ebx
	mov %ebx, (%edi)

# 4. setup pdes
  mov $128, %ecx
	lea (RELOC(boot_pde1)), %ebx
	lea (RELOC(boot_pde2)), %edx
	add $256, %edx
	mov $(PTE_P | PTE_W | 0x180), %eax

fill_pdes:
	mov %eax, (%ebx)
	mov %eax, (%edx)
	add $8, %ebx
	add $8, %edx
	add $0x200000, %eax
	dec %ecx
	cmp $0, %ecx
	jne fill_pdes

# 5. Load page directory base register (cr3).
	lea (RELOC(boot_pml4e)), %eax
	mov %eax, %cr3

#### Enable the long mode using MSR (Model Specific Register)
#### Enable syscall (EFER_SCE)
	mov $EFER_MSR, %ecx
	rdmsr
	orl $(EFER_LME | EFER_SCE), %eax
	wrmsr

#### Enable paging
	mov %cr0, %eax
	or $(CR0_PE|CR0_PG), %eax
	mov %eax, %cr0

#### Jump to the long mode
	lea (RELOC(gdt_desc64)), %eax
	lgdt (%eax)
	mov $(entry_64 - LOADER_KERN_BASE), %eax
	push $SEL_KCSEG
	push %eax
	lret
.endfunc

no_long_mode:
	jmp no_long_mode

.p2align 2
gdt64:
  .quad 0                   # NULL SEGMENT
  .quad 0x00af9a000000ffff  # CODE SEGMENT64
  .quad 0x00af92000000ffff  # DATA SEGMENT64
gdt_desc64:
  .word 0x17
  .quad RELOC(gdt64)

.p2align 12
.globl boot_pml4e
.globl boot_pdpt1
.globl boot_pdpt2
.globl boot_pde1
.globl boot_pde2

boot_pml4e:
  .space  0x1000
boot_pdpt1:
  .space  0x1000
boot_pdpt2:
  .space  0x1000
boot_pde1:
  .space  0x1000
boot_pde2:
  .space  0x1000

.section .text
.code64
.globl entry_64
.func entry_64
entry_64:
	#### We will use 0 ~ 0x1000 as boot stack.
	xor %rbp, %rbp
	movabs $(LOADER_KERN_BASE + 0x1000), %rsp
	movabs $main, %rax
	call *%rax
.endfunc
