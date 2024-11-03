#ifndef USERPROG_PROCESS_H
#define USERPROG_PROCESS_H

#include "threads/thread.h"

tid_t process_create_initd (const char *file_name);
tid_t process_fork (const char *name, struct intr_frame *if_);
int process_exec (void *f_name);
int process_wait (tid_t);
void process_exit (void);
void process_activate (struct thread *next);
void push_arguments (char **argv, int argc, struct intr_frame *if_);
struct thread *get_child (int child_tid);
struct lock filesys_lock;
#endif /* userprog/process.h */
