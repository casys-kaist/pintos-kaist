#### Accessing User Memory
You will need to adapt your code to access user memory (see Section [Accessing User Memory](../project2/introduction.md) while handling a system call. Just as user processes may access pages
whose content is currently in a file or in swap space, so can they pass addresses that refer
to such non-resident pages to system calls. Moreover, unless your kernel takes measures to prevent this, a page may be evicted from its frame even while it is being accessed by kernel
code. If kernel code accesses such non-resident user pages, a page fault will result.

While accessing user memory, your kernel must either be prepared to handle such page
faults, or it must prevent them from occurring. The kernel must prevent such page faults
while it is holding resources it would need to acquire to handle these faults. In Pintos, such
resources include locks acquired by the device driver(s) that control the device(s) containing
the file system and swap space. As a concrete example, you must not allow page faults to
occur while a device driver accesses a user buffer passed to `file_read`, because you would
not be able to invoke the driver while handling such faults.

Preventing such page faults requires cooperation between the code within which the
access occurs and your page eviction code. For instance, you could extend your frame table
to record when a page contained in a frame must not be evicted. (This is also referred to
as “pinning” or “locking” the page in its frame.) Pinning restricts your page replacement
algorithm’s choices when looking for pages to evict, so be sure to pin pages no longer than
necessary, and avoid pinning pages when it is not necessary.
