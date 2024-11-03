#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H
#include <stdbool.h>
#include <stdint.h>
#include <threads/thread.h>

#define STDIN 1
#define STDOUT 2

void syscall_init (void);
void check_address (const uint64_t *addr);
void halt (void);
void exit (int status);
tid_t fork (const char *thread_name, struct intr_frame *f);
int exec (const char *cmd_line);
int wait (tid_t pid);
bool create (const char *file, unsigned initial_size);
bool remove (const char *file);

int put_file (struct file *file);
static struct file *find_with_limits (int fd);
void delete_file (int fd);
int open (const char *file);
int filesize (int fd);
int read (int fd, void *buffer, unsigned size);
int write (int fd, const void *buffer, unsigned size);
void seek (int fd, unsigned position);
unsigned tell (int fd);
void close (int fd);
int dup2 (int oldfd, int newfd);

#endif /* userprog/syscall.h */