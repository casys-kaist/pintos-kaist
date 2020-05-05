# Page Table
The code in `threads/mmu.c` is an abstract interface to the 80x86 hardware page table. The page 
table in Pintos (which is the one you are going to use in the project)
called `pml4` for Page-Map-Level-4 by Intel processor documentation because the table has 
4 levels. The page table interface uses a `uint64_t *` to 
represent a page table because this is convenient for accessing their internal
structure. The sections below describe the page table interface and internals.


## Creation, Destruction, and Activation
These functions create, destroy, and activate page tables. The base Pintos code already
calls these functions where necessary, so it should not be necessary to call them yourself.

-----
```C
uint64_t * pml4_create (void);
```
> Creates and returns a new page table. The new page table contains Pintos’s normal
kernel virtual page mappings, but no user virtual mappings.
Returns a null pointer if memory cannot be obtained.

-----
```C
void pml4_destroy (uint64_t *pml4);
```
> Frees all of the resources held by pml4, including the page table itself and the frames
that it maps. It *recursively* calls `pdpe_destroy`, `pgdir_destory`, and `pt_destroy` to 
free all resources at all levels of the page table. 

-----
```C
void pml4_activate (uint64 t *pml4)
```
> Activates pml4. The active page table is the one used by the CPU to translate memory
references.



## Inspection and Updates
These functions examine or update the mappings from pages to frames encapsulated by a
page table. They work on both active and inactive page tables (that is, those for running
and suspended processes), flushing the TLB as necessary.

-----
```C
bool pml4_set_page (uint64_t *pml4, void *upage, void *kpage, bool rw);
```
> Adds to pd a mapping from user page upage to the frame identified by kernel virtual
address kpage. If rw is true, the page is mapped read/write; otherwise, it is
mapped read-only. User page upage must not already be mapped in pml4.
Kernel page kpage should be a kernel virtual address obtained from the user pool
with `palloc_get_page(PAL_USER)`. Returns true if successful, false on failure. 
Failure will occur if additional memory
required for the page table cannot be obtained.

-----
```C
void * pml4_get_page (uint64_t *pml4, const void *uaddr); 
```
> Looks up the frame mapped to uaddr in pml4. Returns the kernel virtual address for
that frame, if uaddr is mapped, or a null pointer if it is not.

-----
```C
void pml4_clear_page (uint64_t *pml4, void *upage);
```
> Marks page “not present” in pml4. Later accesses to the page will fault.
Other bits in the page table for page are preserved, permitting the accessed and dirty
bits (see the next section) to be checked. This function has no effect if page is not mapped.



## Accessed and Dirty Bits
80x86 hardware provides some assistance for implementing page replacement algorithms,
through a pair of bits in the page table entry (PTE) for each page. On any read or write to
a page, the CPU sets the accessed bit to 1 in the page’s PTE, and on any write, the CPU
sets the dirty bit to 1. The CPU never resets these bits to 0, but the OS may do so.
Proper interpretation of these bits requires understanding of *aliases*, that is, two (or
more) pages that refer to the same frame. When an aliased frame is accessed, the accessed
and dirty bits are updated in only one page table entry (the one for the page used for
access). The accessed and dirty bits for the other aliases are not updated.

-----
```C
bool pml4_is_dirty (uint64_t *pml4, const void *vpage);
bool pml4_is_accessed (uint64_t *pml4, const void *vpage);
```
> Returns true if pml4 contains a page table entry for vpage that is marked
dirty (or accessed). Otherwise, returns false.

-----
```C
void pml4_set_dirty (uint64_t *pml4, const void *vpage, bool dirty);
void pml4_set_accessed (uint64_t *pml4, const void *vpage, bool accessed);
```
> If pml4 has a page table entry for page, then its dirty (or accessed) bit
is set to value given.
