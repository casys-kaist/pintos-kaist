### Paging
Implement paging for segments loaded from executables. All of these pages should be
loaded lazily, that is, only as the kernel intercepts page faults for them. Upon eviction,
pages modified since load (e.g. as indicated by the "dirty bit") should be written to swap.
Unmodified pages, including read-only pages, should never be written to swap because they
can always be read back from the executable.

Implement a global page replacement algorithm that approximates LRU. Your algorithm
should perform at least as well as the simple variant of the "second chance" or "clock"
algorithm.

Your design should allow for parallelism. If one page fault requires I/O, in the meantime
processes that do not fault should continue executing and other page faults that do not
require I/O should be able to complete. This will require some synchronization effort.

You'll need to modify the core of the program loader, which is the loop in `load_segment()` in '`userprog/process.c`'. Each time around the loop, `page_read_bytes` receives the number of bytes to read from the executable file and `page_zero_bytes` receives
the number of bytes to initialize to zero following the bytes read. The two always sum to
`PGSIZE` (4,096). The handling of a page depends on these variables' values:
- If `page_read_bytes` equals `PGSIZE`, the page should be demand paged from the underlying file on its first access.
- If `page_zero_bytes` equals `PGSIZE`, the page does not need to be read from disk at all
  because it is all zeroes. You should handle such pages by creating a new page consisting
of all zeroes at the first page fault.
- Otherwise, neither `page_read_bytes` nor `page_zero_bytes` equals `PGSIZE`. In this
  case, an initial part of the page is to be read from the underlying file and the remainder zeroed.
