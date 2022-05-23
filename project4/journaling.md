### File System Journaling (Not Graded)

**This part will not be graded. You do not have to implement this for your Pintos project.**

> Warning: we strongly recommend you to start this part of extra credit once you have fully
> understood File System Journaling, which will be the last content of this course.

<!-- **Implement Journaling in your file system to support crash consistency.** -->

As a user, you can create, move, remove or modify data in the file system with
the functions you implemented. Each of these operations require multiple changes
in the file system. For example, when you create a file, the operating system needs
to 1) allocate an inode and mark it as being used, 2) write the new file on the new
inode, and 3) add metadata of the new file in its parent directory. All those things
must be done atomically in order to be consist. Until now, proper usage of synchronization
primitives (e.g. lock) was enough to ensure consistency.

However, as data in File System are persistent (i.e. keep alive after machine reboot;
unlike DRAM whose data would be fully erased after reboot), Operating system needs to take another
dimension into consideration. Imagine a situation in which your laptop loses power while
you were creating a new file, say `vm.c` under `pintos/vm` directory. Your operating system
successfully allocated an inode for `vm.c` and marked it as being used, but could not write
metadata on the new inode nor add it in `pintos/vm` directory due to the power failure.
In this case, after reboot, you cannot access and even reclaim the inode, because it was
just written as *being used*, but indeed nobody takes care of it (i.e. cannot remove
somewhat file to reclaim the inode). As a result, you will lose the available storage
capacity as time goes by.

Therefore, in order to avoid such unhappy situation, maintaining crash consistency
is an important role of the file system. There are several ways to keep the consistency.
One can try to scan entire disk and find out inconsistent states (e.g. ghost inodes).
However, it will take too long to wait for it every boot time. Moreover, there are some cases
it cannot find out and recover (think yourself!). Thus, Os requires more promising solution.

File System Journaling is one of the most promising and successful solution to ensure
crash consistency. It guarantees all-or-nothing consistency.
Simply saying, files systems with Journaling feature write some metadata so-called "journal"
that contains what operations it would try before modifying the actual files. They do the
actual operation if and only if the journal is fully committed on special designated region
in a disk. Once os have written the journal on the disk, os can recover whatever you have
tried to do on the disk even though the machine crashes during the first trial.
For instance, as long as os have a journal that says
*"user tried to create `vm.c` under `pintos/vm` with inode at 0xBEEF!"*, os can do it again.
If the machine experienced crash or power failure before the journal has been fully written,
os can just safely ignore it without losing consistency. User might feel unhappy with losing
the file, but it is much better than losing not only the file but also consistency, isn't it?

In the first part of extra credit, you will need to implement journaling file
system for your Pintos. As same as CoW, we only provide basic test cases for
journalling. You should consider all the possible cases. The grading of this
extra project will be done with the hidden test cases as well.

<!-- **DISCLAIMER: This part of extra project is take-or-all-nothing.** -->
