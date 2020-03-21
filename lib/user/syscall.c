#include <syscall.h>
#include <stdint.h>
#include "../syscall-nr.h"

__attribute__((always_inline))
	static __inline int64_t syscall(int num, uint64_t a1, uint64_t a2,
			uint64_t a3, uint64_t a4, uint64_t a5) {
		int64_t ret;
		__asm __volatile("syscall\n" : "=a" (ret) : "a" (num),
				"d" (a1), "c" (a2), "b" (a3), "D" (a4),
				"S" (a5) : "cc", "memory");
		return ret;
	}

/* Invokes syscall NUMBER, passing no arguments, and returns the
   return value as an `int'. */
#define syscall0(NUMBER) (syscall((NUMBER), 0, 0, 0, 0, 0))

/* Invokes syscall NUMBER, passing argument ARG0, and returns the
   return value as an `int'. */
#define syscall1(NUMBER, ARG0) (syscall((NUMBER), (ARG0), 0, 0, 0, 0))
/* Invokes syscall NUMBER, passing arguments ARG0 and ARG1, and
   returns the return value as an `int'. */
#define syscall2(NUMBER, ARG0, ARG1) (syscall((NUMBER), (ARG0), (ARG1), 0, 0, 0))
#define syscall3(NUMBER, ARG0, ARG1, ARG2) (syscall((NUMBER), (ARG0), (ARG1), (ARG2), 0, 0))

void
halt (void) {
	syscall0 (SYS_HALT);
	NOT_REACHED ();
}

void
exit (int status) {
	syscall1 (SYS_EXIT, status);
	NOT_REACHED ();
}

pid_t
fork (void) {
	return (pid_t) syscall0 (SYS_FORK);
}

int
exec (const char *file) {
	return (pid_t) syscall1 (SYS_EXEC, file);
}

int
wait (pid_t pid) {
	return syscall1 (SYS_WAIT, pid);
}

bool
create (const char *file, unsigned initial_size) {
	return syscall2 (SYS_CREATE, file, initial_size);
}

bool
remove (const char *file) {
	return syscall1 (SYS_REMOVE, file);
}

int
open (const char *file) {
	return syscall1 (SYS_OPEN, file);
}

int
filesize (int fd) {
	return syscall1 (SYS_FILESIZE, fd);
}

int
read (int fd, void *buffer, unsigned size) {
	return syscall3 (SYS_READ, fd, buffer, size);
}

int
write (int fd, const void *buffer, unsigned size) {
	return syscall3 (SYS_WRITE, fd, buffer, size);
}

void
seek (int fd, unsigned position) {
	syscall2 (SYS_SEEK, fd, position);
}

unsigned
tell (int fd) {
	return syscall1 (SYS_TELL, fd);
}

void
close (int fd) {
	syscall1 (SYS_CLOSE, fd);
}

mapid_t
mmap (int fd, void *addr) {
	return syscall2 (SYS_MMAP, fd, addr);
}

void
munmap (mapid_t mapid) {
	syscall1 (SYS_MUNMAP, mapid);
}

bool
chdir (const char *dir) {
	return syscall1 (SYS_CHDIR, dir);
}

bool
mkdir (const char *dir) {
	return syscall1 (SYS_MKDIR, dir);
}

bool
readdir (int fd, char name[READDIR_MAX_LEN + 1]) {
	return syscall2 (SYS_READDIR, fd, name);
}

bool
isdir (int fd) {
	return syscall1 (SYS_ISDIR, fd);
}

int
inumber (int fd) {
	return syscall1 (SYS_INUMBER, fd);
}
