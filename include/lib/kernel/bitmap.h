#ifndef __LIB_KERNEL_BITMAP_H
#define __LIB_KERNEL_BITMAP_H

#include <stdbool.h>
#include <stddef.h>
#include <inttypes.h>

/* Bitmap abstract data type. */

/* Creation and destruction. */
struct bitmap *bitmap_create (size_t bit_cnt);
struct bitmap *bitmap_create_in_buf (size_t bit_cnt, void *, size_t byte_cnt);
size_t bitmap_buf_size (size_t bit_cnt);
void bitmap_destroy (struct bitmap *);

/* Bitmap size. */
size_t bitmap_size (const struct bitmap *);

/* Setting and testing single bits. */
void bitmap_set (struct bitmap *, size_t idx, bool);
void bitmap_mark (struct bitmap *, size_t idx);
void bitmap_reset (struct bitmap *, size_t idx);
void bitmap_flip (struct bitmap *, size_t idx);
bool bitmap_test (const struct bitmap *, size_t idx);

/* Setting and testing multiple bits. */
void bitmap_set_all (struct bitmap *, bool);
void bitmap_set_multiple (struct bitmap *, size_t start, size_t cnt, bool);
size_t bitmap_count (const struct bitmap *, size_t start, size_t cnt, bool);
bool bitmap_contains (const struct bitmap *, size_t start, size_t cnt, bool);
bool bitmap_any (const struct bitmap *, size_t start, size_t cnt);
bool bitmap_none (const struct bitmap *, size_t start, size_t cnt);
bool bitmap_all (const struct bitmap *, size_t start, size_t cnt);

/* Finding set or unset bits. */
#define BITMAP_ERROR SIZE_MAX
size_t bitmap_scan (const struct bitmap *, size_t start, size_t cnt, bool);
size_t bitmap_scan_and_flip (struct bitmap *, size_t start, size_t cnt, bool);

/* File input and output. */
#ifdef FILESYS
struct file;
size_t bitmap_file_size (const struct bitmap *);
bool bitmap_read (struct bitmap *, struct file *);
bool bitmap_write (const struct bitmap *, struct file *);
#endif

/* Debugging. */
void bitmap_dump (const struct bitmap *);

#endif /* lib/kernel/bitmap.h */
