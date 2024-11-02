#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/loader.h"
#include "userprog/gdt.h"
#include "threads/flags.h"
#include "intrinsic.h"

#include "filesys/filesys.h"
#include "filesys/file.h"
#include <list.h>
#include "threads/palloc.h"
#include "threads/vaddr.h"
#include "userprog/process.h"

void syscall_entry (void);
void syscall_handler (struct intr_frame *);

void check_address (const uint64_t *addr);

void halt (void);
void exit (int status);
tid_t fork (const char *thread_name);
int exec (const char *cmd_line);
int wait (tid_t pid);
bool create (const char *file, unsigned initial_size);
bool remove (const char *file);
int open (const char *file);
int filesize (int fd);
int read (int fd, void *buffer, unsigned size);
int write (int fd, const void *buffer, unsigned size);
void seek (int fd, unsigned position);
unsigned tell (int fd);
void close (int fd);


int put_file (struct file *file);
static struct file *find_with_limits (int fd);

int dup2(int oldfd, int newfd);
const int STDIN=1;
const int STDOUT=2;
/* System call.
 *
 * Previously system call services was handled by the interrupt handler
 * (e.g. int 0x80 in linux). However, in x86-64, the manufacturer supplies
 * efficient path for requesting the system call, the `syscall` instruction.
 *
 * The syscall instruction works by reading the values from the the Model
 * Specific Register (MSR). For the details, see the manual. */

#define MSR_STAR 0xc0000081         /* Segment selector msr */
#define MSR_LSTAR 0xc0000082        /* Long mode SYSCALL target */
#define MSR_SYSCALL_MASK 0xc0000084 /* Mask for the eflags */

void
syscall_init (void) {
	write_msr(MSR_STAR, ((uint64_t)SEL_UCSEG - 0x10) << 48  |
			((uint64_t)SEL_KCSEG) << 32);
	write_msr(MSR_LSTAR, (uint64_t) syscall_entry);

	/* The interrupt service rountine should not serve any interrupts
	 * until the syscall_entry swaps the userland stack to the kernel
	 * mode stack. Therefore, we masked the FLAG_FL. */
	write_msr(MSR_SYSCALL_MASK,
			FLAG_IF | FLAG_TF | FLAG_DF | FLAG_IOPL | FLAG_AC | FLAG_NT);
}

/* The main system call interface */
void
syscall_handler (struct intr_frame *f UNUSED) {
	switch (f->R.rax) {
		case SYS_HALT:
			halt ();
			break;
		case SYS_EXIT:
			exit (f->R.rdi);
			break;
		case SYS_FORK:
			f->R.rax = fork (f->R.rdi);
			break;
		case SYS_EXEC:
			f->R.rax = exec (f->R.rdi);
			break;
		case SYS_WAIT:
			f->R.rax = wait (f->R.rdi);
			break;
		case SYS_CREATE:
			f->R.rax = create (f->R.rdi, f->R.rsi);
			break;
		case SYS_REMOVE:
			f->R.rax = remove (f->R.rdi);
			break;
		case SYS_OPEN:
			f->R.rax = open (f->R.rdi);
			break;
		case SYS_FILESIZE:
			f->R.rax = filesize (f->R.rdi);
			break;
		case SYS_READ:
			f->R.rax = read (f->R.rdi, f->R.rsi, f->R.rdx);
			break;
		case SYS_WRITE:
			f->R.rax = write (f->R.rdi, f->R.rsi, f->R.rdx);
			break;
		case SYS_SEEK:
			seek (f->R.rdi, f->R.rsi);
			break;
		case SYS_TELL:
			f->R.rax = tell (f->R.rdi);
			break;
		case SYS_CLOSE:
			close (f->R.rdi);
		case SYS_DUP2:
			f->R.rax = dup2 (f->R.rdi, f->R.rsi);
			break;
		default:
			exit(-1);
	}
	printf ("system call!\n");
	thread_exit ();
}

void
check_address (const uint64_t *addr) {
	if (addr == NULL || is_kernel_vaddr (addr) || pml4_get_page (thread_current()->pml4, addr) == NULL) {
		exit(-1);
	}
}

void
halt (void) {
	power_off ();
}

void
exit (int status) {
	struct thread *curr = thread_current ();
	curr->exit_status = status;
	/* Print process termination message */
	printf("%s: exit(%d)\n", curr->name, status);
	thread_exit ();
}

tid_t
fork (const char *thread_name) {
	check_address (thread_name);

	return process_fork (thread_name, NULL);
}

int
exec (const char *cmd_line) {
	check_address (cmd_line);

	char *cmd_copy = palloc_get_page (PAL_ZERO);

	if (cmd_copy == NULL) {
		return -1;
	}

	strlcpy (cmd_copy, cmd_line, strlen (cmd_line) + 1);

	if (process_exec (cmd_copy) == -1) {
		return -1;
	}
}

int
wait (tid_t pid) {
	return process_wait (pid);
}

bool
create (const char *file, unsigned initial_size) {
	check_address (file);

	return filesys_create (file, initial_size);
}

bool
remove (const char *file) {
	check_address (file);

	return filesys_remove (file);
}

int
put_file (struct file *file) {
	struct thread *curr = thread_current ();
	struct file **fdt = curr->fd_table;
	
	while (curr->fd_idx < FD_LIMIT && fdt[curr->fd_idx]) {
		curr->fd_idx++;
	}

	if (curr->fd_idx >= FD_LIMIT) {
		return -1;
	}

	fdt[curr->fd_idx] = file;
	return curr->fd_idx;
}

static struct file
*find_with_limits (int fd) {
	struct thread *curr = thread_current ();
	if (fd >= 0 && fd < FD_LIMIT) {
		return curr->fd_table[fd];
	}
	else {
		return NULL;
	}
}


int
open (const char* file) {
	check_address (file);
	struct file *opened_file = filesys_open (file);

	if (opened_file == NULL) {
		return -1;
	}
	
	int fd = put_file (opened_file);

	if (fd == -1) {
		file_close (opened_file);
	}
	return fd;
}

int
filesize (int fd) {
	struct file *current_file = find_with_limits (fd);
	if (current_file == NULL) {
		return -1;
	}
	return file_length (current_file);
}

int
read (int fd, void *buffer, unsigned length) {
	check_address (buffer);

	struct thread *curr = thread_current ();
	struct file *current_file = find_with_limits (fd);
	
	if (current_file == NULL) {
		return -1;
	}

	if (current_file == STDIN) {
		if (curr->stdin_count == 0) {
			NOT_REACHED ();
			curr->fd_table[fd] = NULL;
			return -1;
		}
		else {
			int i;
			unsigned char *buf = buffer;
			for(i = 0; i < length; i++) {
				char c = input_getc ();
				*buf++=c;
				if (c == '\0') {
					break;
				}
			}
			return i;
		}
	}
	else if (current_file == 2) {
		return -1;
	}
	else {
		lock_acquire (&filesys_lock);
		int ret = file_read (current_file, buffer, length);
		lock_release (&filesys_lock);
		return ret;
	}
}

int
write (int fd, const void *buffer, unsigned length) {
	check_address (buffer);
	struct file *current_file = find_with_limits (fd);

	if (current_file == NULL) {
		return -1;
	}

	struct thread *curr = thread_current ();

	if (current_file == 2) {
		if (curr->stdin_count == 0) {
			NOT_REACHED ();
			curr->fd_table[fd] = NULL;
			return -1;
		}
		else {
			putbuf (buffer, length);
			return length;
		}
	}
	else if (current_file == 1) {
		return -1;
	}
	else {
		lock_acquire (&filesys_lock);
		int ret = file_write (current_file, buffer, length);
		lock_release (&filesys_lock);
		return ret;
	}
}

void
seek (int fd, unsigned position){
	struct file *current_file = find_with_limits (fd);
	if (current_file <= 2) {
		return;
	}
	file_seek (current_file, position);
}

unsigned
tell (int fd) {
	struct file *current_file = find_with_limits (fd);
	check_address (current_file);

	if (current_file <= 2){
		return;
	}

	return file_tell (current_file);
}

void
close (int fd) {
	struct thread *curr = thread_current ();
	struct file *current_file = curr->fd_table[fd];
	if (current_file == NULL) {
		return;
	}

	if (fd == 0 || current_file == 1) {
		curr->stdin_count--;
	}
	else if (fd == 1 || current_file == 2) {
		curr->stdout_count--;
	}

	curr->fd_table[fd] = NULL;

	if (fd <= 1 || current_file <= 2) {
		return;
	}

	if (current_file->dup_count == 0) {
		file_close (current_file);
	}
	else {
		current_file->dup_count--;
	}
}

int
dup2 (int oldfd, int newfd) {
	struct file *current_file = find_with_limits (oldfd);
	if (current_file == NULL) {
		return -1;
	}

	if (oldfd == newfd) {
		return newfd;
	}

	struct thread *curr = thread_current();
	struct file **current_fd_table = curr->fd_table;
	
	if (current_file == STDIN) {
		curr->stdin_count++;
	}
	else if (current_file == STDOUT) {
		curr->stdout_count++;
	}
	else {
		current_file->dup_count++;
	}
	
	close (newfd);
	current_fd_table[newfd] = current_file;
	return newfd;
}