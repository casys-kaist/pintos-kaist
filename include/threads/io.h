/* This file is derived from source code used in MIT's 6.828
   course. The original copyright notice is reproduced in full
   below. */

/*
 * Copyright (C) 1997 Massachusetts Institute of Technology
 *
 * This software is being provided by the copyright holders under the
 * following license. By obtaining, using and/or copying this software,
 * you agree that you have read, understood, and will comply with the
 * following terms and conditions:
 *
 * Permission to use, copy, modify, distribute, and sell this software
 * and its documentation for any purpose and without fee or royalty is
 * hereby granted, provided that the full text of this NOTICE appears on
 * ALL copies of the software and documentation or portions thereof,
 * including modifications, that you make.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS," AND COPYRIGHT HOLDERS MAKE NO
 * REPRESENTATIONS OR WARRANTIES, EXPRESS OR IMPLIED. BY WAY OF EXAMPLE,
 * BUT NOT LIMITATION, COPYRIGHT HOLDERS MAKE NO REPRESENTATIONS OR
 * WARRANTIES OF MERCHANTABILITY OR FITNESS FOR ANY PARTICULAR PURPOSE OR
 * THAT THE USE OF THE SOFTWARE OR DOCUMENTATION WILL NOT INFRINGE ANY
 * THIRD PARTY PATENTS, COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS. COPYRIGHT
 * HOLDERS WILL BEAR NO LIABILITY FOR ANY USE OF THIS SOFTWARE OR
 * DOCUMENTATION.
 *
 * The name and trademarks of copyright holders may NOT be used in
 * advertising or publicity pertaining to the software without specific,
 * written prior permission. Title to copyright in this software and any
 * associated documentation will at all times remain with copyright
 * holders. See the file AUTHORS which should have accompanied this software
 * for a list of all copyright holders.
 *
 * This file may be derived from previously copyrighted software. This
 * copyright applies only to those changes made by the copyright
 * holders listed in the AUTHORS file. The rest of this file is covered by
 * the copyright notices, if any, listed below.
 */

#ifndef THREADS_IO_H
#define THREADS_IO_H

#include <stddef.h>
#include <stdint.h>

/* Reads and returns a byte from PORT. */
static inline uint8_t
inb (uint16_t port) {
	/* See [IA32-v2a] "IN". */
	uint8_t data;
	asm volatile ("inb %w1,%0" : "=a" (data) : "d" (port));
	return data;
}

/* Reads CNT bytes from PORT, one after another, and stores them
   into the buffer starting at ADDR. */
static inline void
insb (uint16_t port, void *addr, size_t cnt) {
	/* See [IA32-v2a] "INS". */
	asm volatile ("cld; repne; insb"
			: "=D" (addr), "=c" (cnt)
			: "d" (port), "0" (addr), "1" (cnt)
			: "memory", "cc");
}

/* Reads and returns 16 bits from PORT. */
static inline uint16_t
inw (uint16_t port) {
	uint16_t data;
	/* See [IA32-v2a] "IN". */
	asm volatile ("inw %w1,%0" : "=a" (data) : "d" (port));
	return data;
}

/* Reads CNT 16-bit (halfword) units from PORT, one after
   another, and stores them into the buffer starting at ADDR. */
static inline void
insw (uint16_t port, void *addr, size_t cnt) {
	/* See [IA32-v2a] "INS". */
	asm volatile ("cld; repne; insw"
			: "=D" (addr), "=c" (cnt)
			: "d" (port), "0" (addr), "1" (cnt)
			: "memory", "cc");
}

/* Reads and returns 32 bits from PORT. */
static inline uint32_t
inl (uint16_t port) {
	/* See [IA32-v2a] "IN". */
	uint32_t data;
	asm volatile ("inl %w1,%0" : "=a" (data) : "d" (port));
	return data;
}

/* Reads CNT 32-bit (word) units from PORT, one after another,
   and stores them into the buffer starting at ADDR. */
static inline void
insl (uint16_t port, void *addr, size_t cnt) {
	/* See [IA32-v2a] "INS". */
	asm volatile ("cld; repne; insl"
			: "=D" (addr), "=c" (cnt)
			: "d" (port), "0" (addr), "1" (cnt)
			: "memory", "cc");
}

/* Writes byte DATA to PORT. */
static inline void
outb (uint16_t port, uint8_t data) {
	/* See [IA32-v2b] "OUT". */
	asm volatile ("outb %0,%w1" : : "a" (data), "d" (port));
}

/* Writes to PORT each byte of data in the CNT-byte buffer
   starting at ADDR. */
static inline void
outsb (uint16_t port, const void *addr, size_t cnt) {
	/* See [IA32-v2b] "OUTS". */
	asm volatile ("cld; repne; outsb"
			: "=S" (addr), "=c" (cnt)
			: "d" (port), "0" (addr), "1" (cnt)
			: "cc");
}

/* Writes the 16-bit DATA to PORT. */
static inline void
outw (uint16_t port, uint16_t data) {
	/* See [IA32-v2b] "OUT". */
	asm volatile ("outw %0,%w1" : : "a" (data), "d" (port));
}

/* Writes to PORT each 16-bit unit (halfword) of data in the
   CNT-halfword buffer starting at ADDR. */
static inline void
outsw (uint16_t port, const void *addr, size_t cnt) {
	/* See [IA32-v2b] "OUTS". */
	asm volatile ("cld; repne; outsw"
			: "=S" (addr), "=c" (cnt)
			: "d" (port), "0" (addr), "1" (cnt)
			: "cc");
}

/* Writes the 32-bit DATA to PORT. */
static inline void
outl (uint16_t port, uint32_t data) {
	/* See [IA32-v2b] "OUT". */
	asm volatile ("outl %0,%w1" : : "a" (data), "d" (port));
}

/* Writes to PORT each 32-bit unit (word) of data in the CNT-word
   buffer starting at ADDR. */
static inline void
outsl (uint16_t port, const void *addr, size_t cnt) {
	/* See [IA32-v2b] "OUTS". */
	asm volatile ("cld; repne; outsl"
			: "=S" (addr), "=c" (cnt)
			: "d" (port), "0" (addr), "1" (cnt)
			: "cc");
}

#endif /* threads/io.h */
