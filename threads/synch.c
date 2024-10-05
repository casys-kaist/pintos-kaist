/* This file is derived from source code for the Nachos
   instructional operating system.  The Nachos copyright notice
   is reproduced in full below. */

/* Copyright (c) 1992-1996 The Regents of the University of California.
   All rights reserved.

   Permission to use, copy, modify, and distribute this software
   and its documentation for any purpose, without fee, and
   without written agreement is hereby granted, provided that the
   above copyright notice and the following two paragraphs appear
   in all copies of this software.

   IN NO EVENT SHALL THE UNIVERSITY OF CALIFORNIA BE LIABLE TO
   ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR
   CONSEQUENTIAL DAMAGES ARISING OUT OF THE USE OF THIS SOFTWARE
   AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITY OF CALIFORNIA
   HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

   THE UNIVERSITY OF CALIFORNIA SPECIFICALLY DISCLAIMS ANY
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
   PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS"
   BASIS, AND THE UNIVERSITY OF CALIFORNIA HAS NO OBLIGATION TO
   PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR
   MODIFICATIONS.
   */

#include "threads/synch.h"
#include <stdio.h>
#include <string.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

/* Initializes semaphore SEMA to VALUE.  A semaphore is a
   nonnegative integer along with two atomic operators for
   manipulating it:

   - down or "P": wait for the value to become positive, then
   decrement it.

   - up or "V": increment the value (and wake up one waiting
   thread, if any). */
void
sema_init (struct semaphore *sema, unsigned value) {
	ASSERT (sema != NULL);

	sema->value = value;
	list_init (&sema->waiters);
}

/* Down or "P" operation on a semaphore.  Waits for SEMA's value
   to become positive and then atomically decrements it.

   This function may sleep, so it must not be called within an
   interrupt handler.  This function may be called with
   interrupts disabled, but if it sleeps then the next scheduled
   thread will probably turn interrupts back on. This is
   sema_down function. */
void
sema_down (struct semaphore *sema) {
	enum intr_level old_level;

	ASSERT (sema != NULL);
	ASSERT (!intr_context ());

	old_level = intr_disable ();
	while (sema->value == 0) {
		// list_push_back (&sema->waiters, &thread_current ()->elem);
		list_insert_ordered(&sema->waiters, &thread_current ()->elem, &cmp_priority, NULL);
		thread_block ();
	}
	sema->value--;
	intr_set_level (old_level);
}

/* Down or "P" operation on a semaphore, but only if the
   semaphore is not already 0.  Returns true if the semaphore is
   decremented, false otherwise.

   This function may be called from an interrupt handler. */
bool
sema_try_down (struct semaphore *sema) {
	enum intr_level old_level;
	bool success;

	ASSERT (sema != NULL);

	old_level = intr_disable ();
	if (sema->value > 0)
	{
		sema->value--;
		success = true;
	}
	else
		success = false;
	intr_set_level (old_level);

	return success;
}

/* Up or "V" operation on a semaphore.  Increments SEMA's value
   and wakes up one thread of those waiting for SEMA, if any.

   This function may be called from an interrupt handler. */
void
sema_up (struct semaphore *sema) {
	enum intr_level old_level;

	ASSERT (sema != NULL);

	old_level = intr_disable ();
	if (!list_empty (&sema->waiters)){
		// list_sort(&sema->waiters, (list_less_func *) &cmp_priority, NULL); 여기에 문제가 있다....
      struct thread *t = list_entry (list_pop_front (&sema->waiters), struct thread, elem);
      if (t->status == THREAD_BLOCKED) { // assertion 막기 위해.. 필요한건지는 검토필요.
         thread_unblock (t);
      }
	}
	sema->value++;
   compare_and_yield();
	intr_set_level (old_level);
   
   
}

static void sema_test_helper (void *sema_);

/* Self-test for semaphores that makes control "ping-pong"
   between a pair of threads.  Insert calls to printf() to see
   what's going on. */
void
sema_self_test (void) {
	struct semaphore sema[2];
	int i;

	printf ("Testing semaphores...");
	sema_init (&sema[0], 0);
	sema_init (&sema[1], 0);
	thread_create ("sema-test", PRI_DEFAULT, sema_test_helper, &sema);
	for (i = 0; i < 10; i++)
	{
		sema_up (&sema[0]);
		sema_down (&sema[1]);
	}
	printf ("done.\n");
}

/* Thread function used by sema_self_test(). */
static void
sema_test_helper (void *sema_) {
	struct semaphore *sema = sema_;
	int i;

	for (i = 0; i < 10; i++)
	{
		sema_down (&sema[0]);
		sema_up (&sema[1]);
	}
}

/* Initializes LOCK.  A lock can be held by at most a single
   thread at any given time.  Our locks are not "recursive", that
   is, it is an error for the thread currently holding a lock to
   try to acquire that lock.

   A lock is a specialization of a semaphore with an initial
   value of 1.  The difference between a lock and such a
   semaphore is twofold.  First, a semaphore can have a value
   greater than 1, but a lock can only be owned by a single
   thread at a time.  Second, a semaphore does not have an owner,
   meaning that one thread can "down" the semaphore and then
   another one "up" it, but with a lock the same thread must both
   acquire and release it.  When these restrictions prove
   onerous, it's a good sign that a semaphore should be used,
   instead of a lock. */
void
lock_init (struct lock *lock) {
	ASSERT (lock != NULL);

	lock->holder = NULL;
	sema_init (&lock->semaphore, 1);
}

/* Acquires LOCK, sleeping until it becomes available if
   necessary.  The lock must not already be held by the current
   thread.

   This function may sleep, so it must not be called within an
   interrupt handler.  This function may be called with
   interrupts disabled, but interrupts will be turned back on if
   we need to sleep. */
void
lock_acquire (struct lock *lock) {
	ASSERT (lock != NULL);
	ASSERT (!intr_context ());
	ASSERT (!lock_held_by_current_thread (lock));

	struct thread *cur = thread_current();

   // mlfqs scheduler이면 바로
   if (thread_mlfqs) {
      sema_down(&lock->semaphore);
      lock->holder = cur;
      return;
   }

    if (lock->holder != NULL) {
      enum intr_level old_level = intr_disable();
      if (lock->holder->priority < cur->priority) {
         donate_priority(lock->holder, cur->priority, true);  // donation
      }
      cur->lock_waiting = lock; 
      sema_down(&lock->semaphore);  
      cur->lock_waiting = NULL;  // 대기 상태 해제
      intr_set_level(old_level);
    } else {
        sema_down(&lock->semaphore);  // 락을 소유 중인 스레드가 없으면 바로 획득
    }

   enum intr_level old_level = intr_disable();
    lock->holder = cur;  // 락을 소유한 스레드로 현재 스레드 설정
    list_push_back(&cur->lock_list, &lock->elem);  // 현재 스레드의 락 리스트에 추가 ㄴㄴ
    // lock_list에 priority 순으로 추가
    list_sort(&cur->lock_list, (list_less_func *) &cmp_priority_lock, NULL); // sorting  해놔서 앞에꺼 바로바로 꺼내쓰게
    intr_set_level(old_level);

}

/* Tries to acquires LOCK and returns true if successful or false
   on failure.  The lock must not already be held by the current
   thread.

   This function will not sleep, so it may be called within an
   interrupt handler. */
bool
lock_try_acquire (struct lock *lock) {
	bool success;

	ASSERT (lock != NULL);
	ASSERT (!lock_held_by_current_thread (lock));

	success = sema_try_down (&lock->semaphore);
	if (success){
      enum intr_level old_level = intr_disable();
      struct thread* cur = thread_current();
      lock->holder = cur;  // 락을 소유한 스레드로 현재 스레드 설정
      list_push_back(&cur->lock_list, &lock->elem);  // 현재 스레드의 락 리스트에 추가 ㄴㄴ
      // lock_list에 priority 순으로 추가
      list_sort(&cur->lock_list, (list_less_func *) &cmp_priority_lock, NULL); // sorting  해놔서 앞에꺼 바로바로 꺼내쓰게
      intr_set_level(old_level);
   }
		
	return success;
}

/* Releases LOCK, which must be owned by the current thread.
   This is lock_release function.

   An interrupt handler cannot acquire a lock, so it does not
   make sense to try to release a lock within an interrupt
   handler. */
void
lock_release (struct lock *lock) {
	ASSERT (lock != NULL);
	ASSERT (lock_held_by_current_thread (lock));


   struct thread *cur = thread_current();
   // mlfqs scheduler이면 바로
   if (thread_mlfqs) {
      lock->holder = NULL;
      sema_up(&lock->semaphore);
      return;
   }

   enum intr_level old_level = intr_disable();
   list_remove(&lock->elem);  // 락 리스트에서 제거

   // 대기 중인 스레드가 있을 경우 donation 복원
   //  multi 왜 안되는지 모르겠음... acquire가 문젠가
   if (!list_empty(&cur->lock_list)) {
      list_sort(&cur->lock_list, (list_less_func *) &cmp_priority_lock, NULL); // 일단 정렬 한 번 더..

      int max_priority;
      struct lock *la = list_entry(list_begin(&cur->lock_list), struct lock, elem);
	   if (!list_empty(&la->semaphore.waiters)) {
		   max_priority = list_entry(list_begin(&la->semaphore.waiters), struct thread, elem)->priority;
	   } else { max_priority = PRI_MIN; }

      if (max_priority > cur->original_priority) { cur->priority = max_priority; } 
      else { cur->priority = cur->original_priority; }
      sort_all(cur);
   } else if (cur->priority != cur->original_priority) {
      cur->priority = cur->original_priority; // 지워졌을 때 원래 priority로
      sort_all(cur);
   }

   lock->holder = NULL;
   intr_set_level(old_level);
	sema_up (&lock->semaphore);
   //compare_and_yield(); 

}

/* Returns true if the current thread holds LOCK, false
   otherwise.  (Note that testing whether some other thread holds
   a lock would be racy.) */
bool
lock_held_by_current_thread (const struct lock *lock) {
	ASSERT (lock != NULL);

	return lock->holder == thread_current ();
}

/* One semaphore in a list. */
struct semaphore_elem {
	struct list_elem elem;              /* List element. */
	struct semaphore semaphore;         /* This semaphore. */
};

/* Initializes condition variable COND.  A condition variable
   allows one piece of code to signal a condition and cooperating
   code to receive the signal and act upon it. */
void
cond_init (struct condition *cond) {
	ASSERT (cond != NULL);

	list_init (&cond->waiters);
	
}

/* Atomically releases LOCK and waits for COND to be signaled by
   some other piece of code.  After COND is signaled, LOCK is
   reacquired before returning.  LOCK must be held before calling
   this function.

   The monitor implemented by this function is "Mesa" style, not
   "Hoare" style, that is, sending and receiving a signal are not
   an atomic operation.  Thus, typically the caller must recheck
   the condition after the wait completes and, if necessary, wait
   again.

   A given condition variable is associated with only a single
   lock, but one lock may be associated with any number of
   condition variables.  That is, there is a one-to-many mapping
   from locks to condition variables.

   This function may sleep, so it must not be called within an
   interrupt handler.  This function may be called with
   interrupts disabled, but interrupts will be turned back on if
   we need to sleep. */
void
cond_wait (struct condition *cond, struct lock *lock) {
	struct semaphore_elem waiter;

	ASSERT (cond != NULL);
	ASSERT (lock != NULL);
	ASSERT (!intr_context ());
	ASSERT (lock_held_by_current_thread (lock));

	sema_init (&waiter.semaphore, 0);
	// list_push_back (&cond->waiters, &waiter.elem);
	list_insert_ordered (&cond->waiters, &waiter.elem, sema_cmp_priority, 0);
	lock_release (lock);
	sema_down (&waiter.semaphore);
	lock_acquire (lock);
}

/* If any threads are waiting on COND (protected by LOCK), then
   this function signals one of them to wake up from its wait.
   LOCK must be held before calling this function.

   An interrupt handler cannot acquire a lock, so it does not
   make sense to try to signal a condition variable within an
   interrupt handler. */
void
cond_signal (struct condition *cond, struct lock *lock UNUSED) {
	ASSERT (cond != NULL);
	ASSERT (lock != NULL);
	ASSERT (!intr_context ());
	ASSERT (lock_held_by_current_thread (lock));

	if (!list_empty (&cond->waiters)){
		list_sort(&cond->waiters, sema_cmp_priority, NULL);
		sema_up (&list_entry (list_pop_front (&cond->waiters), struct semaphore_elem, elem)->semaphore);
	}

}

/* Wakes up all threads, if any, waiting on COND (protected by
   LOCK).  LOCK must be held before calling this function.

   An interrupt handler cannot acquire a lock, so it does not
   make sense to try to signal a condition variable within an
   interrupt handler. */
void
cond_broadcast (struct condition *cond, struct lock *lock) {
	ASSERT (cond != NULL);
	ASSERT (lock != NULL);

	while (!list_empty (&cond->waiters))
		cond_signal (cond, lock);
}


// Helper function 
bool 
sema_cmp_priority (const struct list_elem *l, const struct list_elem *s, void *aux UNUSED)
{
	struct semaphore_elem *l_sema = list_entry (l, struct semaphore_elem, elem);
	struct semaphore_elem *s_sema = list_entry (s, struct semaphore_elem, elem);

	return cmp_priority(list_begin(&l_sema->semaphore.waiters), list_begin(&s_sema->semaphore.waiters));

}

void donate_priority(struct thread *t, int new_priority, bool sort) {
    // t가 donation된 우선순위보다 낮으면 donation
    if (t->priority < new_priority) {
        t->priority = new_priority;
        // donation 받은 thread가 다른 lock을 기다리는건 재귀로 처리
        if (t->lock_waiting != NULL) {
            donate_priority(t->lock_waiting->holder, new_priority, false);
        }
        if (sort) { sort_all(t); }
    }
}

void sort_all(struct thread *t) {

   // t의 priority가 바뀌었을 때, 이와 관련된 모든 sort를 책임지는 함수

   // 1. t가 갖고 있는 lock들의 list를 sort
   list_sort(&t->lock_list, (list_less_func *) &cmp_priority_lock, NULL);
   
   // 2. t->elem가 list의 element이면, 그 list를 sort
   if (t->elem.list_containing != NULL) {
      list_sort(t->elem.list_containing, (list_less_func *) &cmp_priority, NULL);
   }
   
   // 3. t가 lock에 의해 막혀 있다면, 그 lock의 holder도 priority가 바뀔 수 있음
   if (t->lock_waiting != NULL) {
      ASSERT(t->lock_waiting->holder != NULL);
      sort_all(t->lock_waiting->holder);
   }
   
   
}
