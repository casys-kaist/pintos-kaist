## Mount (Not Graded)

**This part will not be graded. You do not have to implement this for your Pintos project.**

When you are working on your computer, you often have to access files stored in
the storage. Before you can access these files, the file system must be mounted.
To mount a file system means to attach it to a directory so that the user can
access. In Linux, you can use the `mount` system call to mount file systems or
removable devices (e.g. flash drive) at a particular directory (which we call
the mount point) in your system.

You could manually mount the device using
`sudo mount /dev/usb /home/usb_mount_point` command where
`/home/usb_mount_point` is the directory you want to mount and access the drive.
You can undo this operation with command `unmount /home/usb_mount_point`.
To unmount means to invalidate all user access to files and directories from the
mount point. When your computer shuts down, all mounted storages are
automatically unmounted. mount and unmount commands internally invokes `mount`
and `unmount` system call respectively.

To support mounting, the operating system needs to access the storage device,
understand its format, process the structure and metadata,
and register them in the virtual file system. When this is all done,
the user can access files and directories from the mount point.

In this part, you will need to implement mount/unmount
functionality in your Pintos. For the simplicity, assume that mount only accepts
device that has default file system of Pintos. You should consider the
synchronization and journaling issues (if you implemented) for mounted file
system. Also, note that single device can be mounted to multiple mount points.

-----
```C
int mount (const char *path, int chan_no, int dev_no);
```
> Mounts the disk (chan_no:dev_no) to path. See disk/disk.c for the meaning of
> chan_no and dev_no. On success, zero is returned. On error, -1 is returned.

-----
```C
int umount (const char *path);
```
> Unmount the disk that mounted to path. On success, zero is returned. On error,
> -1 is returned.

As same as Copy-On-Write, we only provide basic test cases for mount. You should
consider all the possible cases. The grading of this extra project will be done
with the hidden test cases as well.
